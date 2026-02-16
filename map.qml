import QtQuick
import QtLocation
import QtPositioning
import QtQuick.Effects

Item {
    id: root
    width: 600; height: 400

    // --- CORRECTION ---
    // J'ai SUPPRIMÉ la ligne "property string mapboxApiKey..."
    // Le code va maintenant utiliser directement la valeur envoyée par votre C++

    // --- PROPRIÉTÉS ---
    property double carLat: 48.2715
    property double carLon: 4.0645
    property double carZoom: 17
    property double carHeading: 0
    property double carSpeed: 0
    property bool autoFollow: true

    // Zoom Intelligent
    property bool enableSpeedZoom: true
    property bool internalZoomChange: false

    // NAVIGATION
    property string nextInstruction: ""
    property string distanceToNextTurn: ""
    property int nextManeuverDirection: 0

    // GUIDAGE AVANCÉ
    property var routeSteps: []
    property int currentStepIndex: 0
    property double lastDistToStep: 999999
    signal routeReadyForSimulation(var pathObj)

    // STATISTIQUES
    property string remainingDistString: "-- km"
    property string remainingTimeString: "-- min"
    property string arrivalTimeString: "--:--"
    property real realRouteSpeed: 13.8

    // TRACÉ
    property var routePoints: []
    property var finalDestination: null
    property bool isRecalculating: false

    property int speedLimit: -1
    property double manualBearing: 0

    property var routeSpeedLimits: []

    signal routeInfoUpdated(string distance, string duration)
    signal suggestionsUpdated(string suggestions)


    // --- 1. PLUGIN STANDARD (OSM + CartoDB Dark) ---
    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://a.basemaps.cartocdn.com/dark_all/%z/%x/%y.png"
        }
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: true }
        PluginParameter { name: "osm.useragent"; value: "GPSInterface/1.0" }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin

        center: QtPositioning.coordinate(carLat, carLon)
        zoomLevel: carZoom
        copyrightsVisible: false
        bearing: autoFollow ? carHeading : manualBearing
        tilt: autoFollow ? 45 : 0

        // Animations fluides
        Behavior on center { enabled: !root.autoFollow && !mapDragHandler.active; CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad } }
        Behavior on zoomLevel { NumberAnimation { duration: 500; easing.type: Easing.InOutQuad } }
        Behavior on bearing {
            RotationAnimation {
                direction: RotationAnimation.Shortest
                duration: 600
            }
        }
        Behavior on tilt { NumberAnimation { duration: 600 } }

        DragHandler {
            id: mapDragHandler
            target: null
            onCentroidChanged: {
                if (!active) return
                if (root.autoFollow) root.autoFollow = false
                if (centroid.pressedPosition) map.pan(-(centroid.position.x - centroid.pressedPosition.x), -(centroid.position.y - centroid.pressedPosition.y))
            }
        }

        WheelHandler {
            onWheel: (event) => {
                var step = event.angleDelta.y > 0 ? 1 : -1;
                root.carZoom = Math.max(2, Math.min(20, root.carZoom + step))
            }
        }

        MapPolyline {
            id: visualRouteLine
            line.width: 8
            line.color: "#33ccff"
            opacity: 0.9
        }

        MapQuickItem {
            id: carMarker
            coordinate: QtPositioning.coordinate(carLat, carLon)
            anchorPoint.x: carVisual.width / 2; anchorPoint.y: carVisual.height / 2
            sourceItem: Item {
                id: carVisual
                enabled: false
                width: 64; height: 64
                Rectangle { anchors.centerIn: parent; width: 50; height: 50; color: "#00a8ff"; opacity: 0.3; radius: 25 }
                Rectangle {
                    anchors.centerIn: parent; width: 24; height: 32; color: "white"; radius: 6; border.width: 2; border.color: "#171a21"
                    Rectangle { width: 24; height: 24; color: "white"; rotation: 45; y: -10; anchors.horizontalCenter: parent.horizontalCenter; border.width: 2; border.color: "#171a21" }
                }
            }
        }
    }

    // --- REQUÊTES API (Utilise mapboxApiKey du C++) ---
    function requestRouteWithTraffic(startCoord, endCoord) {
        // Vérification de sécurité
        if (typeof mapboxApiKey === "undefined" || mapboxApiKey === "") {
            console.log("ERREUR CRITIQUE: mapboxApiKey n'est pas définie depuis le C++ !");
            return;
        }

        var url = "https://api.mapbox.com/directions/v5/mapbox/driving-traffic/" +
                  startCoord.longitude + "," + startCoord.latitude + ";" +
                  endCoord.longitude + "," + endCoord.latitude +
                  "?geometries=geojson&steps=true&overview=full&language=fr&annotations=maxspeed&access_token=" + mapboxApiKey;

        var http = new XMLHttpRequest()
        http.open("GET", url, true);
        http.onreadystatechange = function() {
            if (http.readyState == 4) {
                if (http.status == 200) {
                    try {
                        var json = JSON.parse(http.responseText);
                        if (json.routes && json.routes.length > 0) {
                            var route = json.routes[0];
                            var durationSec = route.duration;
                            var distMeters = route.distance;

                            if (durationSec > 0) realRouteSpeed = distMeters / durationSec;
                            else realRouteSpeed = 13.8;

                            routeInfoUpdated((distMeters / 1000).toFixed(1) + " km", Math.round(durationSec / 60) + " min");
                            updateStatsFromDuration(durationSec, distMeters);

                            // Points
                            var coords = route.geometry.coordinates;
                            var newPoints = [];
                            for (var i = 0; i < coords.length; i++) {
                                newPoints.push(QtPositioning.coordinate(coords[i][1], coords[i][0]));
                            }
                            var simplePath = [];
                            for (var j = 0; j < coords.length; j++) {
                                simplePath.push({"lat": coords[j][1], "lon": coords[j][0]});
                            }
                            routeReadyForSimulation(simplePath);
                            routePoints = newPoints;
                            visualRouteLine.path = routePoints;

                            // Vitesses
                            if (route.legs && route.legs[0] && route.legs[0].annotation && route.legs[0].annotation.maxspeed) {
                                routeSpeedLimits = route.legs[0].annotation.maxspeed;
                            } else {
                                routeSpeedLimits = [];
                            }

                            if (route.legs && route.legs.length > 0) {
                                routeSteps = route.legs[0].steps;
                                currentStepIndex = 0;
                                lastDistToStep = 999999;
                                updateGuidance();
                            }
                            isRecalculating = false;
                        }
                    } catch(e) { console.log("Erreur JSON: " + e) }
                } else {
                    console.log("Erreur HTTP Mapbox (" + http.status + "): " + http.responseText);
                }
            }
        }
        http.send();
    }

    // --- FONCTIONS VISUELLES ---
    function updateRouteVisuals() {
        if (routePoints.length === 0) {
            visualRouteLine.path = [];
            speedLimit = -1;
            return;
        }

        var carPos = QtPositioning.coordinate(carLat, carLon);
        var searchLimit = Math.min(routePoints.length, 50);
        var closestIndex = -1;
        var minDistance = 100000;

        for (var i = 0; i < searchLimit; i++) {
            var d = carPos.distanceTo(routePoints[i]);
            if (d < minDistance) {
                minDistance = d;
                closestIndex = i;
            }
        }

        if (closestIndex > 0) {
            routePoints.splice(0, closestIndex);
            if (routeSpeedLimits.length >= closestIndex) {
                routeSpeedLimits.splice(0, closestIndex);
            }
        }

        if (routePoints.length > 0 && carPos.distanceTo(routePoints[0]) < 12) {
            routePoints.splice(0, 1);
            if (routeSpeedLimits.length > 0) routeSpeedLimits.splice(0, 1);
        }

        if (routeSpeedLimits.length > 0) {
            var limitData = routeSpeedLimits[0];
            if (limitData && limitData.speed !== undefined) {
                 speedLimit = limitData.speed;
            } else if (typeof limitData === 'number') {
                 speedLimit = limitData;
            }
        }

        if (routePoints.length > 0) {
            var drawPath = [carPos];
            var limit = Math.min(routePoints.length, 3000);
            for (var k = 0; k < limit; k++) drawPath.push(routePoints[k]);
            visualRouteLine.path = drawPath;
        } else {
            visualRouteLine.path = [];
        }
    }

    function formatWazeDistance(meters) {
        if (meters < 20) return "0 m";
        if (meters < 300) return (Math.round(meters / 10) * 10) + " m";
        if (meters < 1000) return (Math.round(meters / 50) * 50) + " m";
        return (Math.round(meters / 100) / 10).toFixed(1) + " km";
    }

    function updateGuidance() {
        if (!routeSteps || routeSteps.length === 0 || currentStepIndex >= routeSteps.length) {
            if (routePoints.length > 0 && routePoints.length < 15) {
                 nextInstruction = "Vous êtes arrivé";
                 distanceToNextTurn = "0 m";
                 nextManeuverDirection = 0;
            }
            return;
        }

        var step = routeSteps[currentStepIndex];
        var maneuverLoc = QtPositioning.coordinate(step.maneuver.location[1], step.maneuver.location[0]);
        var carPos = QtPositioning.coordinate(carLat, carLon);
        var dist = carPos.distanceTo(maneuverLoc);

        if (dist < 35 && dist > lastDistToStep && currentStepIndex < routeSteps.length - 1) {
            currentStepIndex++;
            lastDistToStep = 999999;
            updateGuidance();
            return;
        }
        lastDistToStep = dist;

        distanceToNextTurn = formatWazeDistance(dist);
        nextInstruction = step.maneuver.instruction;
        nextManeuverDirection = mapboxModifierToDirection(step.maneuver.type, step.maneuver.modifier);
    }

    function mapboxModifierToDirection(type, modifier) {
        if (type === "arrive") return 0;
        if (type === "roundabout" || type === "rotary") return 100;
        if (!modifier) return 1;
        if (modifier.indexOf("slight right") !== -1) return 3;
        if (modifier.indexOf("sharp right") !== -1) return 5;
        if (modifier.indexOf("right") !== -1) return 4;
        if (modifier.indexOf("slight left") !== -1) return 10;
        if (modifier.indexOf("sharp left") !== -1) return 8;
        if (modifier.indexOf("left") !== -1) return 9;
        if (modifier.indexOf("uturn") !== -1) return 6;
        return 1;
    }

    function updateTripStats() {
        if (routePoints.length === 0) return;
        var carPos = QtPositioning.coordinate(carLat, carLon);
        var distRemaining = 0;
        distRemaining += carPos.distanceTo(routePoints[0]);
        for (var i = 0; i < routePoints.length - 1; i++) {
            distRemaining += routePoints[i].distanceTo(routePoints[i+1]);
        }
        remainingDistString = formatWazeDistance(distRemaining);
        var timeSeconds = distRemaining / realRouteSpeed;
        updateStatsFromDuration(timeSeconds, distRemaining);
    }

    function updateStatsFromDuration(durationSec, distMeters) {
        var h = Math.floor(durationSec / 3600);
        var m = Math.floor((durationSec % 3600) / 60);
        if (h > 0) remainingTimeString = h + " h " + (m < 10 ? "0"+m : m);
        else remainingTimeString = m + " min";
        var arrivalDate = new Date(Date.now() + durationSec * 1000);
        var ah = arrivalDate.getHours();
        var am = arrivalDate.getMinutes();
        arrivalTimeString = ah + ":" + (am < 10 ? "0"+am : am);
    }

    function checkIfOffRoute() {
        if (routePoints.length === 0 || isRecalculating) return;
        var carPos = QtPositioning.coordinate(carLat, carLon);
        var minDistance = 100000;
        var searchLimit = Math.min(routePoints.length, 100);
        for (var i = 0; i < searchLimit; i++) {
            var d = carPos.distanceTo(routePoints[i]);
            if (d < minDistance) minDistance = d;
        }
        if (minDistance > 100) recalculateRoute();
    }

    function searchDestination(address) {
        if (typeof mapboxApiKey === "undefined" || mapboxApiKey === "") return;
        var queryUrl = "https://api.mapbox.com/geocoding/v5/mapbox.places/" + encodeURIComponent(address) + ".json?access_token=" + mapboxApiKey + "&limit=1&language=fr";
        var http = new XMLHttpRequest();
        http.open("GET", queryUrl, true);
        http.onreadystatechange = function() {
            if (http.readyState == 4 && http.status == 200) {
                try {
                    var json = JSON.parse(http.responseText);
                    if (json.features && json.features.length > 0) {
                        var c = json.features[0].center;
                        finalDestination = QtPositioning.coordinate(c[1], c[0]);
                        isRecalculating = true;
                        nextInstruction = "Calcul...";
                        requestRouteWithTraffic(QtPositioning.coordinate(carLat, carLon), finalDestination);
                        autoFollow = true;
                    }
                } catch(e) {}
            }
        }
        http.send();
    }

    function requestSuggestions(query) {
        if (!query || query.length < 3 || typeof mapboxApiKey === "undefined" || mapboxApiKey === "") return;
        var http = new XMLHttpRequest();
        var url = "https://api.mapbox.com/geocoding/v5/mapbox.places/" + encodeURIComponent(query) + ".json?access_token=" + mapboxApiKey + "&autocomplete=true&limit=5&language=fr";
        http.open("GET", url, true);
        http.onreadystatechange = function() {
            if (http.readyState == 4 && http.status == 200) {
                try {
                    var json = JSON.parse(http.responseText);
                    var results = [];
                    if (json.features) for (var i=0; i<json.features.length; i++) results.push(json.features[i].place_name);
                    root.suggestionsUpdated(JSON.stringify(results));
                } catch(e) {}
            }
        }
        http.send();
    }

    function recalculateRoute() {
        if (!finalDestination || isRecalculating) return;
        isRecalculating = true;
        requestRouteWithTraffic(QtPositioning.coordinate(carLat, carLon), finalDestination);
    }

    function recenterMap() {
        autoFollow = true;
        enableSpeedZoom = true;
        map.center = QtPositioning.coordinate(carLat, carLon);
    }

    function getDirectionIconPath(direction) {
        var path = "qrc:/icons/";
        if (direction === 0) return path + "dir_arrival.svg";
        switch(direction) {
            case 1: return path + "dir_straight.svg";
            case 3: return path + "dir_slight_right.svg";
            case 4: return path + "dir_right.svg";
            case 5: return path + "dir_right.svg";
            case 6: return path + "dir_uturn.svg";
            case 8: return path + "dir_left.svg";
            case 9: return path + "dir_left.svg";
            case 10: return path + "dir_slight_left.svg";
            case 100: return path + "rond_point.svg";
            default: return path + "dir_straight.svg";
        }
    }

    // --- ANIMATIONS & LOGIQUE ---
    onCarLatChanged: {
        if (autoFollow) {
            map.center = QtPositioning.coordinate(carLat, carLon);
            if (enableSpeedZoom) {
                var targetZoom = 18;
                if (carSpeed > 100) targetZoom = 15;
                else if (carSpeed > 70) targetZoom = 16;
                else if (carSpeed > 40) targetZoom = 17;
                else targetZoom = 18;

                if (Math.abs(carZoom - targetZoom) > 0.5) {
                    internalZoomChange = true;
                    carZoom = targetZoom;
                    internalZoomChange = false;
                }
            }
            map.tilt = (carSpeed > 30) ? 45 : 0;
        }

        if (!isRecalculating) {
            updateRouteVisuals();
            checkIfOffRoute();
            updateTripStats();
            updateGuidance();
        }
    }

    onCarLonChanged: { if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon); }

    onCarZoomChanged: {
        if (!internalZoomChange) {
            enableSpeedZoom = false;
        }
        if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon);
    }

    // --- INTERFACE UTILISATEUR ---
    Rectangle {
        id: navPanel
        visible: (routePoints.length > 0 || isRecalculating) && nextInstruction.length > 0
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.topMargin: 15
        width: Math.min(parent.width * 0.9, 500); height: 70; radius: 35
        color: "#CC1C1C1E"; border.color: isRecalculating ? "#FF9800" : "#33FFFFFF"; border.width: 2
        layer.enabled: true
        layer.effect: MultiEffect { shadowEnabled: true; shadowColor: "#80000000"; shadowBlur: 10; shadowVerticalOffset: 4 }
        Row {
            anchors.fill: parent; anchors.leftMargin: 20; anchors.rightMargin: 20; spacing: 15
            Image {
                anchors.verticalCenter: parent.verticalCenter; width: 40; height: 40
                source: getDirectionIconPath(nextManeuverDirection); sourceSize.width: 40; sourceSize.height: 40; fillMode: Image.PreserveAspectFit; mipmap: true
            }
            Column {
                anchors.verticalCenter: parent.verticalCenter; width: parent.width - 65; spacing: 2
                Text { text: distanceToNextTurn; color: isRecalculating ? "#FF9800" : "white"; font.pixelSize: 22; font.bold: true }
                Text { text: nextInstruction; color: "#D0D0D0"; font.pixelSize: 14; elide: Text.ElideRight; width: parent.width; maximumLineCount: 1 }
            }
        }
    }

    Rectangle {
        id: bottomInfoPanel
        visible: routePoints.length > 0 && !isRecalculating
        anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottomMargin: 20
        width: Math.min(parent.width * 0.5, 250); height: 50; radius: 25
        color: "#CC1C1C1E"; border.color: "#33FFFFFF"; border.width: 1
        Row {
            anchors.centerIn: parent; spacing: 15
            Text { text: remainingTimeString; color: "#4CAF50"; font.bold: true; font.pixelSize: 18 }
            Text { text: "•"; color: "#808080"; font.pixelSize: 18 }
            Text { text: remainingDistString; color: "#E0E0E0"; font.pixelSize: 18 }
            Text { text: "(" + arrivalTimeString + ")"; color: "#808080"; font.pixelSize: 18; anchors.verticalCenter: parent.verticalCenter }
        }
    }

    Rectangle {
        id: speedSign
        width: 60; height: 60; radius: 30
        color: "white"; border.color: "red"; border.width: 6
        anchors { bottom: parent.bottom; left: parent.left; margins: 20 }
        z: 20
        visible: speedLimit > 0
        Rectangle {
            anchors.fill: parent; radius: 30; color: "red"; visible: speedLimit > 0 && carSpeed > speedLimit; opacity: 0.6
            SequentialAnimation on opacity {
                running: speedLimit > 0 && carSpeed > speedLimit; loops: Animation.Infinite
                NumberAnimation { from: 0.2; to: 0.8; duration: 500 }
                NumberAnimation { from: 0.8; to: 0.2; duration: 500 }
            }
        }
        Text {
            anchors.centerIn: parent
            text: speedLimit < 0 ? "-" : speedLimit
            font.pixelSize: 24
            font.bold: true
            color: "black"
        }
    }
}

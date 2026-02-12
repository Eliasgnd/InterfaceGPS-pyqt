import QtQuick
import QtLocation
import QtPositioning

Item {
    id: root
    width: 600; height: 400

    // --- PROPRIÉTÉS ---
    property double carLat: 48.2715
    property double carLon: 4.0645
    property double carZoom: 17
    property double carHeading: 0
    property double carSpeed: 0
    property bool autoFollow: true
    property string nextInstruction: ""
    property int speedLimit: -1
    property double manualBearing: 0

    // Optimisation API Vitesse
    property double lastApiCallTime: 0
    property var lastApiCallPos: QtPositioning.coordinate(0, 0)

    signal routeInfoUpdated(string distance, string duration)
    signal suggestionsUpdated(string suggestions)

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://api.mapbox.com/styles/v1/mapbox/dark-v11/tiles/256/%z/%x/%y?access_token="
                   + mapboxApiKey
        }
        PluginParameter { name: "osm.useragent"; value: "Mozilla/5.0 (Qt6)" }
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: true }
    }

    RouteQuery { id: routeQuery }

    RouteModel {
        id: routeModel
        plugin: mapPlugin
        query: routeQuery
        autoUpdate: false
        onStatusChanged: {
            if (status === RouteModel.Ready && count > 0) {
                var route = get(0)
                routeInfoUpdated((route.distance / 1000).toFixed(1) + " km", Math.round(route.travelTime / 60) + " min")
                if (route.segments && route.segments.length > 0 && route.segments[0].maneuver) {
                    nextInstruction = route.segments[0].maneuver.instructionText
                }
            }
        }
    }

    // Gestion limitation vitesse (Overpass)
    function parseMaxspeedValue(raw) {
        if (!raw) return 0
        raw = ("" + raw).trim()
        if (raw.indexOf("FR:urban") === 0) return 50
        if (raw.indexOf("FR:rural") === 0) return 80
        if (raw.indexOf("FR:motorway") === 0) return 130
        var m = raw.match(/(\d+(\.\d+)?)/)
        if (!m) return 0
        var v = parseFloat(m[1])
        if (isNaN(v)) return 0
        if (raw.toLowerCase().indexOf("mph") !== -1) v = v * 1.60934
        return Math.round(v)
    }

    function updateRealSpeedLimit(lat, lon) {
        var http = new XMLHttpRequest()
        var radius = 80
        var query = '[out:json][timeout:25];(way(around:' + radius + ',' + lat + ',' + lon + ')["highway"]["maxspeed"];);out tags center;'
        var url = "https://overpass-api.de/api/interpreter"

        http.open("POST", url, true)
        http.setRequestHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8")
        http.onreadystatechange = function() {
            if (http.readyState !== 4) return
            if (http.status !== 200) return
            try {
                var json = JSON.parse(http.responseText)
                if (!json.elements) return
                var bestLimit = 0
                var bestDist = 1e18
                var carPos = QtPositioning.coordinate(lat, lon)

                for (var i = 0; i < json.elements.length; i++) {
                    var el = json.elements[i]
                    if (!el.tags || !el.tags.maxspeed || !el.center) continue
                    var limit = parseMaxspeedValue(el.tags.maxspeed)
                    if (limit <= 0) continue
                    var p = QtPositioning.coordinate(el.center.lat, el.center.lon)
                    var d = carPos.distanceTo(p)
                    if (d < bestDist) {
                        bestDist = d
                        bestLimit = limit
                    }
                }
                if (bestLimit > 0) root.speedLimit = bestLimit
            } catch(e) {}
        }
        http.send("data=" + encodeURIComponent(query))
    }

    // UI Carte
    Rectangle {
        id: instructionBanner
        anchors { top: parent.top; horizontalCenter: parent.horizontalCenter; topMargin: 12 }
        width: parent.width * 0.8; height: 52; radius: 12
        color: "#dd171a21"; border.color: "#33ffffff"; border.width: 1
        visible: routeModel.status === RouteModel.Ready && nextInstruction.length > 0
        z: 10
        Text {
            anchors.fill: parent; anchors.margins: 12
            text: nextInstruction; color: "white"; font { pixelSize: 18; bold: true }
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap; elide: Text.ElideRight
        }
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

        Behavior on center {
            enabled: !root.autoFollow && !mapDragHandler.active
            CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad }
        }
        Behavior on zoomLevel { NumberAnimation { duration: 500; easing.type: Easing.InOutQuad } }
        Behavior on bearing { NumberAnimation { duration: 600 } }
        Behavior on tilt { NumberAnimation { duration: 600 } }

        DragHandler {
            id: mapDragHandler
            target: null
            onCentroidChanged: {
                if (!active) return
                if (root.autoFollow) root.autoFollow = false
                map.pan(-(centroid.position.x - mapDragHandler.centroid.pressedPosition.x),
                        -(centroid.position.y - mapDragHandler.centroid.pressedPosition.y))
            }
        }

        WheelHandler {
            onWheel: (event) => {
                var step = event.angleDelta.y > 0 ? 1 : -1
                root.carZoom = Math.max(2, Math.min(20, root.carZoom + step))
            }
        }

        MapItemView {
            model: routeModel
            delegate: MapRoute { route: routeData; line.color: "#1db7ff"; line.width: 10; opacity: 0.8; smooth: true }
        }

        MapQuickItem {
            id: carMarker
            coordinate: QtPositioning.coordinate(carLat, carLon)
            anchorPoint.x: carVisual.width / 2; anchorPoint.y: carVisual.height / 2
            sourceItem: Item {
                id: carVisual
                enabled: false
                width: 64; height: 64
                Rectangle { anchors.centerIn: parent; width: 50; height: 50; color: "#00a8ff"; opacity: 0.2; radius: 25 }
                Rectangle {
                    anchors.centerIn: parent; width: 24; height: 32; color: "white"; radius: 6; border.width: 2; border.color: "#171a21"
                    Rectangle { width: 24; height: 24; color: "white"; rotation: 45; y: -10; anchors.horizontalCenter: parent.horizontalCenter; border.width: 2; border.color: "#171a21" }
                }
            }
        }
    }

    // Panneau Limitation
    Rectangle {
        id: speedSign
        width: 60; height: 60; radius: 30
        color: "white"; border.color: "red"; border.width: 6
        anchors { bottom: parent.bottom; left: parent.left; margins: 20 }
        z: 20
        Rectangle {
            anchors.fill: parent; radius: 30
            color: "red"; visible: speedLimit > 0 && carSpeed > speedLimit; opacity: 0.6
            SequentialAnimation on opacity {
                running: speedLimit > 0 && carSpeed > speedLimit
                loops: Animation.Infinite
                NumberAnimation { from: 0.2; to: 0.8; duration: 500 }
                NumberAnimation { from: 0.8; to: 0.2; duration: 500 }
            }
        }
        Text {
            anchors.centerIn: parent
            text: speedLimit < 0 ? "-" : speedLimit; font { pixelSize: 24; bold: true }
            color: "black"
        }
    }

    // Logique
    onCarLatChanged: {
        if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon)
        var now = Date.now()
        var currentPos = QtPositioning.coordinate(carLat, carLon)
        var distanceSinceLast = lastApiCallPos.distanceTo(currentPos)
        if ( (now - lastApiCallTime > 15000) && (distanceSinceLast > 50) ) {
            updateRealSpeedLimit(carLat, carLon)
            lastApiCallTime = now
            lastApiCallPos = currentPos
        }
    }
    onCarLonChanged: { if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon) }
    onCarZoomChanged: { if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon) }

    function searchDestination(address) {
        var http = new XMLHttpRequest()
        var url = "https://api.mapbox.com/geocoding/v5/mapbox.places/" + encodeURIComponent(address) + ".json?access_token=" + mapboxApiKey + "&limit=1"
        http.open("GET", url, true);
        http.onreadystatechange = function() {
            if (http.readyState == 4 && http.status == 200) {
                try {
                    var json = JSON.parse(http.responseText)
                    if (json.features && json.features.length > 0) {
                        var c = json.features[0].center
                        routeQuery.clearWaypoints()
                        routeQuery.addWaypoint(QtPositioning.coordinate(carLat, carLon))
                        routeQuery.addWaypoint(QtPositioning.coordinate(c[1], c[0]))
                        routeModel.update()
                        autoFollow = true
                        updateRealSpeedLimit(carLat, carLon)
                    }
                } catch(e) {}
            }
        }
        http.send();
    }

    function requestSuggestions(query) {
        if (!query || query.length < 3) return
        var http = new XMLHttpRequest()
        var url = "https://api.mapbox.com/geocoding/v5/mapbox.places/" + encodeURIComponent(query) + ".json?access_token=" + mapboxApiKey + "&autocomplete=true&limit=5"
        http.open("GET", url, true);
        http.onreadystatechange = function() {
            if (http.readyState == 4 && http.status == 200) {
                try {
                    var json = JSON.parse(http.responseText)
                    var results = []
                    if (json.features) for (var i=0; i<json.features.length; i++) results.push(json.features[i].place_name)
                    root.suggestionsUpdated(JSON.stringify(results))
                } catch(e) {}
            }
        }
        http.send();
    }

    function recenterMap() {
        autoFollow = true
        map.center = QtPositioning.coordinate(carLat, carLon)
        carZoom = 17
    }
}

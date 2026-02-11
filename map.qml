import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

Item {
    id: root
    width: 600; height: 400

    property double carLat: 48.2715
    property double carLon: 4.0645
    property double carZoom: 17
    property double carHeading: 0
    property bool autoFollow: true

    signal routeInfoUpdated(string distance, string duration)
    signal suggestionsUpdated(string suggestions)

    // --- LOGS DE DÉMARRAGE ---
    Component.onCompleted: {
        console.log("=== QML: Initialisation de la carte ===")
        console.log("QML: Clé API présente : " + (mapboxApiKey.length > 0 ? "OUI (" + mapboxApiKey.substring(0,5) + "...)" : "NON"))
        console.log("QML: Position de départ : " + carLat + ", " + carLon)

        // Test de connexion immédiat vers Mapbox
        testHttpConnexion()
    }

    function testHttpConnexion() {
        var testUrl = "https://api.mapbox.com/geocoding/v5/mapbox.places/Paris.json?access_token=" + mapboxApiKey + "&limit=1"
        console.log("QML: Lancement du test de connexion SSL/HTTPS vers Mapbox...")
        var http = new XMLHttpRequest()
        http.open("GET", testUrl, true)
        http.onreadystatechange = function() {
            if (http.readyState === 4) {
                if (http.status === 200) {
                    console.log(">>> [SUCCESS] Test réseau : Mapbox répond correctement (HTTP 200)")
                } else {
                    console.log(">>> [ERREUR] Test réseau : Code " + http.status)
                    console.log(">>> Réponse serveur : " + http.responseText)
                    if (http.status === 0) console.log(">>> CONSEIL: Un code 0 indique souvent un problème SSL (libssl manquante) ou un blocage Firewall.")
                }
            }
        }
        http.send()
    }

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.custom.host"
            // On passe de 512 à 256 et on enlève le @2x
            value: "https://api.mapbox.com/styles/v1/mapbox/streets-v12/tiles/256/%z/%x/%y?access_token=" + mapboxApiKey
        }
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: true }
        PluginParameter { name: "osm.routing.host"; value: "https://routing.openstreetmap.de/routed-car/route/v1/driving/" }
        PluginParameter { name: "osm.routing.apiversion"; value: "v5" }
        PluginParameter { name: "osm.useragent"; value: "InterfaceGPS_Student/1.0" }
    }

    RouteQuery { id: routeQuery }

    RouteModel {
        id: routeModel
        plugin: mapPlugin
        query: routeQuery
        autoUpdate: false

        onStatusChanged: {
            if (status === RouteModel.Ready) {
                console.log("QML: [ROUTE] Succès ! Itinéraires trouvés : " + count)
                if (count > 0) {
                    var route = get(0)
                    var d = (route.distance / 1000).toFixed(1) + " km"
                    var t = Math.round(route.travelTime / 60) + " min"
                    console.log("QML: [ROUTE] Détails : " + d + " / " + t)
                    routeInfoUpdated(d, t)
                }
            } else if (status === RouteModel.Loading) {
                console.log("QML: [ROUTE] Calcul en cours sur le serveur...")
            } else if (status === RouteModel.Error) {
                console.log("!!! QML: [ROUTE] ERREUR : " + errorString)
            }
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(carLat, carLon)
        zoomLevel: carZoom
        copyrightsVisible: false

        MapItemView {
            model: routeModel
            delegate: MapRoute { route: routeData; line.color: "#1db7ff"; line.width: 12; opacity: 0.9 }
        }

        MapQuickItem {
            id: carMarker
            coordinate: QtPositioning.coordinate(carLat, carLon)
            anchorPoint.x: carVisual.width / 2
            anchorPoint.y: carVisual.height / 2
            sourceItem: Item {
                id: carVisual
                width: 60; height: 60
                Rectangle { anchors.centerIn: parent; width: 44; height: 44; color: "#00a8ff"; opacity: 0.2; radius: 22 }
                Rectangle {
                    anchors.centerIn: parent; width: 22; height: 30; color: "white"; radius: 4; border.width: 2; border.color: "#171a21"
                    Rectangle { width: 22; height: 22; color: "white"; rotation: 45; y: -8; anchors.horizontalCenter: parent.horizontalCenter; border.width: 2; border.color: "#171a21" }
                }
                transform: Rotation { origin.x: 30; origin.y: 30; angle: carHeading }
            }
        }
    }

    // --- RECHERCHE AVEC LOGS DÉTAILLÉS ---
    function searchDestination(address) {
        console.log("--- QML: [GEOCODING] Début de recherche pour : " + address + " ---")
        var http = new XMLHttpRequest()
        var url = "https://api.mapbox.com/geocoding/v5/mapbox.places/" + encodeURIComponent(address) + ".json?access_token=" + mapboxApiKey + "&limit=1"

        console.log("QML: [GEOCODING] URL appelée : " + url)

        http.open("GET", url, true)
        http.onreadystatechange = function() {
            console.log("QML: [GEOCODING] Changement d'état HTTP : " + http.readyState)
            if (http.readyState == 4) {
                console.log("QML: [GEOCODING] Réponse reçue. Status HTTP : " + http.status)

                if (http.status == 200) {
                    try {
                        var json = JSON.parse(http.responseText)
                        if (json.features && json.features.length > 0) {
                            var destLon = json.features[0].center[0]
                            var destLat = json.features[0].center[1]
                            console.log("QML: [GEOCODING] Coordonnées trouvées : " + destLat + ", " + destLon)

                            routeQuery.clearWaypoints()
                            routeQuery.addWaypoint(QtPositioning.coordinate(carLat, carLon))
                            routeQuery.addWaypoint(QtPositioning.coordinate(destLat, destLon))
                            console.log("QML: [GEOCODING] Lancement de la requête de route...")
                            routeModel.update()
                        } else {
                            console.log("QML: [GEOCODING] Aucun résultat pour cette adresse.")
                        }
                    } catch (e) {
                        console.log("!!! QML: [GEOCODING] Erreur lors du parsing JSON : " + e)
                    }
                } else {
                    console.log("!!! QML: [GEOCODING] Erreur HTTP : " + http.status + " / " + http.responseText)
                }
            }
        }
        http.send()
    }

    // --- SUGGESTIONS AVEC LOGS DÉTAILLÉS ---
    function requestSuggestions(query) {
        console.log("QML: [SUGGESTIONS] Requête pour : " + query)
        var http = new XMLHttpRequest()
        var url = "https://api.mapbox.com/geocoding/v5/mapbox.places/" + encodeURIComponent(query) + ".json?access_token=" + mapboxApiKey + "&autocomplete=true&fuzzyMatch=true&language=fr&limit=5"

        http.open("GET", url, true)
        http.onreadystatechange = function() {
            if (http.readyState == 4) {
                if (http.status == 200) {
                    try {
                        var json = JSON.parse(http.responseText)
                        var results = []
                        if (json.features) {
                            for (var i = 0; i < json.features.length; i++) {
                                results.push(json.features[i].place_name)
                            }
                        }
                        console.log("QML: [SUGGESTIONS] " + results.length + " résultats envoyés au C++")
                        root.suggestionsUpdated(JSON.stringify(results))
                    } catch (e) {
                        console.log("!!! QML: [SUGGESTIONS] Erreur JSON : " + e)
                    }
                } else {
                    console.log("!!! QML: [SUGGESTIONS] Erreur HTTP " + http.status)
                }
            }
        }
        http.send()
    }

    onCarLatChanged: { if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon) }
    onCarLonChanged: { if (autoFollow) map.center = QtPositioning.coordinate(carLat, carLon) }
    function recenterMap() {
        console.log("QML: Recentrage manuel demandé")
        autoFollow = true;
        map.center = QtPositioning.coordinate(carLat, carLon);
        map.zoomLevel = 17;
    }
}

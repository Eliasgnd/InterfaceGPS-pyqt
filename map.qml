import QtQuick
import QtLocation
import QtPositioning

Item {
    width: 600; height: 400

    property double carLat: 48.8566
    property double carLon: 2.3522
    property double carZoom: 16
    property double carHeading: 0

    Plugin {
        id: mapPlugin
        name: "osm"
        // On retire les PluginParameter pour l'instant car ils causent l'erreur
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin

        center: QtPositioning.coordinate(carLat, carLon)
        zoomLevel: carZoom
        tilt: 45      // On garde l'inclinaison pour le style 3D
        bearing: 0

        // Animation fluide
        Behavior on center { CoordinateAnimation { duration: 1000; easing.type: Easing.Linear } }
        Behavior on zoomLevel { NumberAnimation { duration: 500 } }
        Behavior on bearing { NumberAnimation { duration: 500 } }

        // Le véhicule (Flèche bleue)
        MapQuickItem {
            id: carMarker
            coordinate: QtPositioning.coordinate(carLat, carLon)
            anchorPoint.x: carVisual.width / 2
            anchorPoint.y: carVisual.height / 2

            sourceItem: Item {
                id: carVisual
                width: 40; height: 40

                Rectangle {
                    anchors.centerIn: parent
                    width: 20; height: 30
                    color: "#00a8ff"
                    radius: 4
                    antialiasing: true
                    border.color: "white"
                    border.width: 2

                    // Triangle directionnel
                    Rectangle {
                        width: 20; height: 20
                        color: "#00a8ff"
                        rotation: 45
                        y: -10
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                transform: Rotation {
                    origin.x: 20; origin.y: 20
                    angle: carHeading
                }
            }
        }
    }
}

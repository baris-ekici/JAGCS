import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "Overlays"

Map {
    id: root

    property var lineModel
    property var pointModel
    property var vehicleModel

    property var mouseCoordinate: QtPositioning.coordinate()

    signal saveMapViewport()
    signal picked(var coordinate)

    plugin: Plugin { name: "osm" }
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    activeMapType: supportedMapTypes[5] // TerrainMapType
    copyrightsVisible: false

    Behavior on center {
        CoordinateAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }

    MissionLineMapOverlayView {
        model: lineModel
    }

    RadiusMapOverlayView {
        model: pointModel
    }

    AcceptanceRadiusMapOverlayView {
        model: pointModel
    }

    MissionPointMapOverlayView {
        model: pointModel
    }

    VehicleMapOverlayView {
        model: vehicleModel
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onExited: mouseCoordinate = QtPositioning.coordinate()
        onPositionChanged: mouseCoordinate = map.toCoordinate(Qt.point(mouseX, mouseY))
        onClicked: map.picked(mouseCoordinate)
    }

    onCenterChanged: {
        if (!mouseArea.containsMouse) return;

        mouseCoordinate = map.toCoordinate(Qt.point(mouseArea.mouseX, mouseArea.mouseY))
    }

    Component.onDestruction: saveMapViewport()

    function setGesturesEnabled(enabled) {
        gesture.acceptedGestures = enabled ?
                    (MapGestureArea.PinchGesture |
                     MapGestureArea.PanGesture |
                     MapGestureArea.FlickGesture) :
                    MapGestureArea.PinchGesture
    }
}

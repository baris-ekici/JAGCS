import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../Map"

Pane {
    id: root

    property alias missions: missionsBox.model
    property alias vehicles: vehiclesBox.model
    property string selectedMission
    property string assignedVehicle
    property int progress: progressBar.value
    property int sequence: -1

    signal selectMission(string name)
    signal addMission()
    signal removeMission()
    signal renameMission(string name)
    signal assignVehicle(string name)
    signal uploadMission()
    signal downloadMission()

    onSelectedMissionChanged: {
        edit.checked = false;
        if (missionsBox.currentText != selectedMission)
        {
            missionsBox.currentIndex = missionsBox.model.indexOf(selectedMission);
        }
    }
    onAssignedVehicleChanged: {
        if (vehiclesBox.currentText != assignedVehicle)
        {
            vehiclesBox.currentIndex = vehiclesBox.model.indexOf(assignedVehicle);
        }
    }

    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        GridLayout {
            columns: 5
            Layout.margins: palette.margins

            Label {
                text: qsTr("Mission")
            }

            ComboBox {
                id: missionsBox
                visible: !edit.checked
                onCurrentTextChanged: {
                    selectedMission = currentText;
                    selectMission(currentText);
                }
            }

            TextField {
                id: nameEdit
                visible: edit.checked
            }

            Button {
                id: edit
                iconSource: "qrc:/icons/edit.svg"
                checkable: true
                enabled: selectedMission.length > 0
                onCheckedChanged: {
                    if (checked) nameEdit.text = selectedMission;
                    else renameMission(nameEdit.text);
                }
            }

            Button {
                iconSource: "qrc:/icons/add.svg"
                onClicked: addMission()
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                enabled: selectedMission.length > 0
                onClicked: removeMission()
            }

            Label {
                text: qsTr("Vehicle")
            }

            ComboBox {
                id: vehiclesBox
                enabled: selectedMission.length > 0
                Layout.columnSpan: 2
                onCurrentTextChanged: {
                    assignedVehicle = currentText;
                    assignVehicle(currentText);
                }
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
                enabled: selectedMission.length > 0
                onClicked: downloadMission()
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
                enabled: selectedMission.length > 0
                onClicked: uploadMission()
            }

            ProgressBar {
                id: progressBar
                to: 100
                Layout.columnSpan: 5
                Layout.fillWidth: true
            }
        }

        RowLayout {
            Label {
                text: qsTr("Item")
                Layout.fillWidth: true
            }

            Button {
                iconSource: "qrc:/icons/left.svg"
            }

            Label {
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: palette.controlBaseSize
                horizontalAlignment: Qt.AlignHCenter
                text: sequence > -1 ? sequence : "-"
            }

            Button {
                iconSource: "qrc:/icons/right.svg"
            }
        }

        MissionItemView {
            objectName: "missionItem"
        }
    }

    MapView {
        id: map
        objectName: "map"
        anchors.left: column.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}

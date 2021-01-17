import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
Window {
    visible: true
//    width: 1080
//    height: 960
    width: 676
    height: 624
    minimumHeight: 411
    minimumWidth: 295
    title: qsTr("Accumulate")
    GridLayout
    {
        anchors.fill: parent
        columns: 2
        DataBaseModel
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }
}

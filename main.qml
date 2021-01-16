import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 676
    height: 624
    minimumHeight: 411
    minimumWidth: 295
    title: qsTr("Accumulate")
    DataBaseModel
    {
        anchors.fill: parent
    }
}

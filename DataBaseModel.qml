import QtQuick 2.13
import QtQuick.Controls 1.4
import Header.Coding.Company 1.0
Item {
    id:rootItem
    NumbersDB{id:models}
    property var myModel:models.model;
    Column
    {
        id:column
        anchors.fill: parent
        spacing: 20
        Row
        {
            id:row
            height: parent.height*0.1;
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50
            Button
            {
                text:qsTr("start")
                onClicked:models.startAdding();
            }
            Text {
                id: lblSum
                text: qsTr("Sum of numbers: ")
                color: "gray"
            }
            Text {
                id: sumNumber
                text: "myModel"
                color: (sumNumber.text.toInt<1000?"green":"red")
            }
            Button
            {
                text:qsTr("stop")
                onClicked: models.stopAdding();
            }

        }

        TableView
        {
            id:tableView
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height*0.9
            width: parent.width
            model:myModel
            TableViewColumn { role: "value"; title: "value"; width: 150 }
            TableViewColumn { role: "date"; title: "date"; width: 150 }
            TableViewColumn { role: "time"; title: "time"; width: 150 }
        }

    }
}

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
        Row
        {
            id:row
            height: parent.height*0.1;
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50
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

        }

        TableView
        {
            id:listView
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height*0.9
            width: parent.width
            TableViewColumn { role: "value"; title: "value"; width: 100 }
            TableViewColumn { role: "date"; title: "date"; width: 100 }
            TableViewColumn { role: "time"; title: "time"; width: 100 }
        }
    }
    Component.onCompleted:
    {

        listView.model=myModel;
    }
}

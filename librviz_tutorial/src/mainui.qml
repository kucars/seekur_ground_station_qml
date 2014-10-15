import QtQuick 1.1



TabWidget {
    id: tabs
    //the size for the tabs
    width: 1000; height: 650

    //each Rectangle defines a tab
    Rectangle {
        property string title: "config"
        anchors.fill: parent
        //coloer for outer Rectangle
        color: "#e3e3e3"

//the second Rectangle is the inner Rectangle the colored one i guess i can remove it
        Rectangle {
            anchors.fill: parent; anchors.margins: 20
            //color: "#ff7f7f" //assigns the color for this Rectangle
            //defines text within Rectangle
            Text {
                width: parent.width - 20
                anchors.centerIn: parent; horizontalAlignment: Qt.AlignHCenter
              //  text: "Roses are red"
                font.pixelSize: 20
                wrapMode: Text.WordWrap
            }
        }
    }

    Rectangle {
        property string title: "Green"
        anchors.fill: parent
        color: "#e3e3e3"

        Rectangle {
            anchors.fill: parent; anchors.margins: 20
        //    color: "#7fff7f"
            Text {
                width: parent.width - 20
                anchors.centerIn: parent; horizontalAlignment: Qt.AlignHCenter
              //  text: "Flower stems are green"
                font.pixelSize: 20
                wrapMode: Text.WordWrap
            }
        }
    }

    Rectangle {
        property string title: "Blue"
        anchors.fill: parent; color: "#e3e3e3"

        Rectangle {
            anchors.fill: parent; anchors.margins: 20
         //   color: "#7f7fff"
            Text {
                width: parent.width - 20
                anchors.centerIn: parent; horizontalAlignment: Qt.AlignHCenter
               // text: "Violets are blue"
                font.pixelSize: 20
                wrapMode: Text.WordWrap
            }
        }
    }
}

import QtQuick 1.1
import WidgetTrial 1.0

Rectangle {
    id: layout
    width:1000
    height: 650





    Rectangle {
        width: 360
        height: 360
        widgetTrial {
           x:100; y:100
        }
    }

Rectangle {
     id:simplebutton
     color: "grey"
     width: 150; height: 75
     gradient: Gradient {
          // UbuntuTouch-like background
                 GradientStop { position: 0.0; color: "#c05c7c"; }
                 GradientStop { position: 0.5; color: "#d56a59"; }
             }




     Text{
         id: buttonLabel
         anchors.centerIn: parent
         text: "button label"
     }
     Loader { id: pageLoader }
     MouseArea{
         id: buttonMouseArea

         anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                 //onClicked handles valid mouse button clicks
         //onClicked: console.log(buttonLabel.text + " clicked" )
         onClicked: pageLoader.source = "mainui.qml"
     }
 }
}

/*
Rectangle {
    width: 360
    height: 360
    Text {
        anchors.centerIn: parent
        text: "Hello World"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
*/

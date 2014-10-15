import QtQuick 1.1
//import "QWidgets" 1.0
import Qt 4.7
import widgetTrial 1.0
//import OpenGl 1.0



Rectangle{
    width: 500
    height: 500

//opacity: 0.3

WidgetTrial{
    id:m
  //  opacity: 7

}
}
//Rectangle {
//    id: layout
//    width:1000
//    height: 650



////    Rectangle {
////        width: 334
////        height: 299

////        WidgetTrial{
////            id:m
////            MouseArea {
////                     anchors.fill: parent
////                     onClicked: console.log("clicked")
////                 }
////          //  m.showing();

////                }
////        } //{rviz: "" }



////Rectangle {
////     id:simplebutton
////     color: "grey"
////     width: 150; height: 75
////     gradient: Gradient {
////          // UbuntuTouch-like background
////                 GradientStop { position: 0.0; color: "#c05c7c"; }
////                 GradientStop { position: 0.5; color: "#d56a59"; }
////             }
////     Text{
////         id: buttonLabel
////         anchors.centerIn: parent
////         text: "button label"
////     }
////     Loader { id: pageLoader }
////     MouseArea{
////         id: buttonMouseArea

////         anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
////                 //onClicked handles valid mouse button clicks
////         //onClicked: console.log(buttonLabel.text + " clicked" )
////         onClicked: pageLoader.source = "mainui.qml"
////     }
//// }
//}

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

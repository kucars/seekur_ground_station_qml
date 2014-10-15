
import QtQuick 1.1

Item {
     id: tabWidget

     // Setting the default property to stack.children means any child items
     // of the TabWidget are actually added to the 'stack' item's children.
     // See the "Property Binding"
     // documentation for details on default properties.

     //aliasing property hold refrence to another property defined in the same scope
     //here stack is an item defined below we are binding the content property to the child
     default property alias content: stack.children

     property int current: 0

     onCurrentChanged: setOpacities()
     Component.onCompleted: setOpacities()

     function setOpacities() {
         for (var i = 0; i < stack.children.length; ++i) {
             stack.children[i].opacity = (i == current ? 1 : 0)
         }
     }

     Row {
         id: header

         Repeater {
             model: stack.children.length
             //the upper tabs
             delegate: Rectangle {
                 width: tabWidget.width / stack.children.length; height: 36

                 Rectangle {
                     width: parent.width; height: 1
                     anchors { bottom: parent.bottom; bottomMargin: 1 }
                     color: "#acb2c2"
                 }
//                 BorderImage {
//                     anchors { fill: parent; leftMargin: 2; topMargin: 5; rightMargin: 1 }
//                     border { left: 7; right: 7 }
//                     //image behinde tab name
//                     source: "icon.png"
//                     visible: tabWidget.current == index
//                 }
                 //text in each tab
                 Text {
                     horizontalAlignment: Qt.AlignHCenter; verticalAlignment: Qt.AlignVCenter
                     anchors.fill: parent
                     text: stack.children[index].title
                     elide: Text.ElideRight
                     font.bold: tabWidget.current == index
                 }
                 //to click each tab
                 MouseArea {
                     anchors.fill: parent
                     onClicked: tabWidget.current = index
                 }
             }
         }
     }

     Item {
         id: stack
         width: tabWidget.width
         anchors.top: header.bottom; anchors.bottom: tabWidget.bottom
     }
 }

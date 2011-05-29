import QtQuick 1.0

 Rectangle {
     id: button;
     signal clicked
     property string text : "";

     width: 180; height: 70
     border.width: 1
     radius: 5
     smooth: true
     color: "gray"

     Text {
         id: textItem
         text: parent.text
         anchors.centerIn: parent
         font.pointSize: 20
         color: "black"
     }

     MouseArea {
       id: mouseArea
       enabled: parent.enabled
       anchors.fill: parent
       onClicked: parent.clicked()
     }

     states: [
       State {
         name: ""
         PropertyChanges { target: button; opacity: 1}
       },
       State {
         name: "pressed"
         when: mouseArea.pressed
         PropertyChanges { target: button; opacity: 1}
         PropertyChanges { target: button; color: "blue" }
       },
       State {
         name: "disabled"
         PropertyChanges { target: button; opacity: 0.4}
         PropertyChanges { target: mouseArea; enabled: false}
       }
     ]
}

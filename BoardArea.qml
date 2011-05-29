import QtQuick 1.0
import "boardarea.js" as BoardAreaMethods

Rectangle {
  id: area
  property int note;
  property bool shown;

  Image {
    id: circle
    anchors.centerIn: parent;
  }

  MouseArea {
    anchors.fill: parent;
    onClicked: { main.guess(note); }
  }

  Component.onCompleted: {
    main.stateChanged.connect(BoardAreaMethods.mainStateChanged);
  }
}

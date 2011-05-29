import QtQuick 1.0
import "guitarboard.js" as GuitarBoardMethods
Rectangle {
  id: guitarboard
  width: 760
  height: 6*28

  signal clearGuesses

  Component.onCompleted: GuitarBoardMethods.setupBoard();
}

import QtQuick 1.0
import "guitarboard.js" as GuitarBoardMethods
Rectangle {
  id: guitarboard
  signal clearGuesses
  Component.onCompleted: GuitarBoardMethods.setupBoard();
}

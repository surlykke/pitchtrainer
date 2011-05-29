import QtQuick 1.0
import "main.js" as MainMethods



Rectangle {
    width: 800
    height: 360
    id: main

    property int note1
    property int note2
    property int guessedNote

    signal guess(int note)
    signal play(int note)
    signal playInterval(int note1, int note2)

    onPlay: {console.log("Play: " + note); }
    onPlayInterval: {console.log("PlayInterval: " + note1 + ", " + note2);}

    onGuess: MainMethods.guess(note);

    GuitarBoard {
      x : 25
      y : 10
    }

    Text {
      id: text
      x: 10
      y: 180
      text: "Click 'New interval' to start an excercise..."
      font.pointSize: 20
    }

    Row {
        x: 10
        y: 240
        spacing: 20
        Button {
          id: newInterval;
          text: "New interval";
          onClicked: MainMethods.newInterval()
        }
        Button {
          id: repeat;
          text: "Repeat";
          state: "disabled"
          onClicked: MainMethods.repeat()
        }
        Button {
          id: giveUp;
          text: "Give up";
          state: "disabled"
          onClicked: MainMethods.giveUp()
        }
        Button {
          id: settings;
          text: "Settings...";
          onClicked: MainMethods.settings() }
    }

    states: [
      State {
        name: ""
        PropertyChanges { target: repeat; state: "disabled" }
        PropertyChanges { target: giveUp; state: "disabled" }
      },
      State {
        name: "excerciseGiven"
        PropertyChanges { target: repeat; state: "" }
        PropertyChanges { target: giveUp; state: "" }
        PropertyChanges { target: text; text: "Identify the interval"}
      },
      State {
        name: "guessWrong"
        PropertyChanges { target: repeat; state: "" }
        PropertyChanges { target: giveUp; state: "" }
        PropertyChanges { target: text; text: "Wrong!" }
      },
      State {
        name: "guessRight"
        PropertyChanges { target: repeat; state: "" }
        PropertyChanges { target: giveUp; state: "disabled" }
        PropertyChanges {
          target: text;
          text: "Correct! "  + MainMethods.noteName(note1) + " -> " + MainMethods.noteName(note2) + " - " + MainMethods.intervalName(note1, note2)}
      },
      State {
        name: "givenUp"
        PropertyChanges { target: repeat; state: "" }
        PropertyChanges { target: giveUp; state: "disabled" }
        PropertyChanges {
          target: text;
          text: "It was: " + MainMethods.noteName(note1) + " -> " + MainMethods.noteName(note2) + " - " + MainMethods.intervalName(note1, note2)
        }
      }
    ]
    onStateChanged: console.log("State changed to: " + state);
}

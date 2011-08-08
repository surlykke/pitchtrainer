/*
  Copyright 2010, 2011 Christian Surlykke

  This file is part of PitchTrainer.

  PitchTrainer is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, version 3

  PitchTrainer is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PitchTrainer.  If not, see <http://www.gnu.org/licenses/>.
*/
import QtQuick 1.1
import com.nokia.meego 1.0
import "main.js" as MainMethods

Window {
    id: main
    signal guess(int note)
    signal play(int note)
    signal playInterval(int note1, int note2)
    onGuess: MainMethods.guess(note);

    //width: 800
    //height: 360

    property int note1
    property int note2
    property int guessedNote

    Column {
        GuitarBoard {
            id: guitarboard1
            width: 800
            height: 168 // 6*28
        }

        Text {
            id: text
            color: "white"
            text: "Click 'New interval' to start an excercise..."
            font.pointSize: 20
            height: 45
        }

        ButtonRow {
            width: 800;
            exclusive: false;
            Button {
                id: newInterval;
                text: "New interval";
                onClicked: MainMethods.newInterval()
            }
            Button {
                id: repeat;
                text: "Repeat";
                enabled: false;
                onClicked: playInterval(note1, note2)
            }
            Button {
                id: giveUp;
                text: "Give up";
                enabled: false;
                onClicked: main.state = "givenUp"
            }
            Button {
                id: settings;
                text: "Settings...";
                onClicked: { pageStack.push(pitchTrainerSettings)}
            }
        }
    }

    states: [
        State {
            name: ""
        },
        State {
            name: "excerciseGiven"
            PropertyChanges { target: repeat; enabled: true }
            PropertyChanges { target: giveUp; enabled: true }
            PropertyChanges { target: text; text: "Identify the interval"}
        },
        State {
            name: "guessWrong"
            PropertyChanges { target: repeat; enabled: true }
            PropertyChanges { target: giveUp; enabled: true }
            PropertyChanges { target: text; text: "Wrong!" }
        },
        State {
            name: "guessRight"
            PropertyChanges { target: repeat; enabled: true }
            PropertyChanges {
                target: text;
                text: "Correct! "  + MainMethods.noteName(note1) + " -> " + MainMethods.noteName(note2) + " - " + MainMethods.intervalName(note1, note2)}
        },
        State {
            name: "givenUp"
            PropertyChanges { target: repeat; enabled: true }
            PropertyChanges {
                target: text;
                text: "It was: " + MainMethods.noteName(note1) + " -> " + MainMethods.noteName(note2) + " - " + MainMethods.intervalName(note1, note2)
            }
        }
    ]
    onStateChanged: console.log("State changed to: " + state);
}

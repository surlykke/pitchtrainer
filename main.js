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
const noteNames = [ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
const intervalNames = [
        "Perfect Unison",
        "Minor second",
        "Major second",
        "Minor third",
        "Major third",
        "Perfect fourth",
        "Diminished fifth",
        "Perfect fifth",
        "Minor sixth",
        "Major sixth",
        "Minor seventh",
        "Major seventh",
        "Perfect octave"];


function newInterval() {
  console.log("instrument: " + applicationSettings.instrument());
  console.log("intervals: " + applicationSettings.intervals());
  var oldState = state;
  var availableIntervals = [1,2]; //FIXME
  var descending = false; // FIXME
  var index = Math.floor(Math.random()*availableIntervals.length);
  var interval = availableIntervals[index];
  var min = 52; // FIXME
  var max = 88; // FIXME
  var span = (max - min) - 20 + 1;
  note1 = min + 10 + Math.floor(Math.random()*span);
  note2 = descending ? note1 -  interval: note1 + interval;
  state = "excerciseGiven";
  if (oldState == state) stateChanged(state);
  playInterval(note1, note2);
  newInterval.responsive = false;
}

function guess(note) {
  console.log("Ind i guess");
  var oldState = state;
  switch (state) {
    case "":
    case "guessRight":
    case "givenUp": break;
    default:
      console.log("... default ...");
      guessedNote = note;
      state =  (note == note2 ? "guessRight" : "guessWrong") ;
  }
  console.log("oldState: " + oldState + ", state: " + state);
  if (oldState == state) stateChanged(state);
  play(note);
}

function noteName(note) {
  var noteNumber = (((note - 60) % 12)  + 12) % 12;
  var octaveNumber = 4 + Math.floor((note - 60)/ 12);
  return noteNames[noteNumber] + octaveNumber;
}

function intervalName(n1, n2) {
  var diff = n2 >= n1 ? n2 - n1 : n1 - n2;
  return diff > 12 ? "?" : intervalNames[diff];
}


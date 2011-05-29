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

function repeat() {
  playInterval(note1, note2);
}

function giveUp() {
  state = "givenUp"
}

function settings() {
  console.settings();
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
  console
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


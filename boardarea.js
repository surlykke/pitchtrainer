const greenImg = "qrc:images/green_circle.png";
const greenImgSml = "qrc:images/green_circle_smiley.png"
const redImg = "qrc:images/red_circle.png";
const noImg = "";

function mainStateChanged(newState) {
  circle.z = 122;
  if (note == main.guessedNote) {
    switch (newState) {
      case "guessRight": circle.source = greenImgSml; break;
      case "guessWrong": circle.source = redImg; break;
      default: circle.source = noImg;
    }
  }
  else if (note == main.note1) {
    circle.source = greenImg;
  }
  else {
    circle.source = noImg;
  }
}


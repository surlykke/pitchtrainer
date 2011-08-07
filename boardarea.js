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


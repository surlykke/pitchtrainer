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
const twelftRootOf2 = 1.0594630943593;
const looseNote =  [76, 71, 67, 62, 57, 52];
var firstStringY;
var firstBandX;
var stringLength;
var stringSeparation;

const whiteImg = "qrc:images/white_circle.png";
var dummy;

function setupBoard() {
        console.log("width: " + width);
  firstStringY = height/12;
  firstBandX = 0.05*width;
  stringLength = 2*0.925*width;
  stringSeparation = height/6;
  var stringComponent = Qt.createComponent("string.qml");
  var bandComponent = Qt.createComponent("band.qml");
  var boardAreaComponent = Qt.createComponent("BoardArea.qml");
  var circleComponent = Qt.createComponent("circle.qml");

  var boardPos;
  // Place boardAreas
  for (var str = 0; str < 6; str++) {

    var bandX = firstBandX;
    var bandSeparationF = (1 - 1/twelftRootOf2)*stringLength;
    for (var band = 0; band < 13; band++) {
      var bandSeparation = Math.floor(bandSeparationF);
      var boardArea = boardAreaComponent.createObject(guitarboard);
      boardArea.x = (band == 0 ? 0 : bandX - bandSeparation);
      boardArea.y = str*stringSeparation;
      boardArea.width = (band == 0 ? firstBandX : bandSeparation);
      boardArea.height = stringSeparation;
      boardArea.note = looseNote[str] + band;

      bandX = bandX + bandSeparation;
      bandSeparationF = bandSeparationF/twelftRootOf2;
    }
  }

  // Paint strings
  for (var i = 0; i < 6; i++) {
    var string = stringComponent.createObject(guitarboard);
    string.x = 0;
    string.y = firstStringY + i*stringSeparation;
  }

  // Paint bands and circles
  var bandX = firstBandX;
  var bandSeparationF = (1 - 1/twelftRootOf2)*stringLength;
  for (var i = 0; i < 13; i ++) {
    band = bandComponent.createObject(guitarboard);
    band.y = firstStringY;
    band.x = bandX;

    if (i == 2 || i == 4 || i == 6 || i == 8) {
      var circle = circleComponent.createObject(guitarboard);
      circle.x = Math.floor(band.x + bandSeparationF/2 - 12);
      circle.y = Math.floor(firstStringY + 2.5*stringSeparation - 12);
      circle.source = whiteImg;
    }
    else  if (i == 11) {
      var circle1 = circleComponent.createObject(guitarboard);
      circle1.x = Math.floor(band.x + bandSeparationF/2 - 12);
      circle1.y = Math.floor(firstStringY + 1.5*stringSeparation - 12);
      circle1.source = whiteImg;

      var circle2 = circleComponent.createObject(guitarboard);
      circle2.x = Math.floor(band.x + bandSeparationF/2 - 12);
      circle2.y = Math.floor(firstStringY + 3.5*stringSeparation - 12);
      circle2.source = whiteImg;
    }

    bandX = bandX + Math.floor(bandSeparationF);
    bandSeparationF = bandSeparationF/twelftRootOf2;
  }

}

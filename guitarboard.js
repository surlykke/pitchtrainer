const twelftRootOf2 = 1.0594630943593;
const firstStringY = 14;
const firstBandX = 25;
const stringLength = 1400;
const stringSeparation = 28;
const looseNote =  [76, 71, 67, 62, 57, 52];

function setupBoard() {
  var stringComponent = Qt.createComponent("string.qml");
  var bandComponent = Qt.createComponent("band.qml");
  var boardAreaComponent = Qt.createComponent("BoardArea.qml");

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

  // Paint bands
  var bandX = firstBandX;
  var bandSeparationF = (1 - 1/twelftRootOf2)*stringLength;
  for (var i = 0; i < 13; i ++) {
    band = bandComponent.createObject(guitarboard);
    band.y = firstStringY;
    band.x = bandX;
    bandX = bandX + Math.floor(bandSeparationF);
    bandSeparationF = bandSeparationF/twelftRootOf2;
  }
}

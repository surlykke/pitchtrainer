#include "guitarboard.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <Qt>

GuitarBoard::GuitarBoard(QObject *parent): QGraphicsScene(parent)
{
	// Paint a guitar board
	// Strings
	for (int i = 0; i < 6; i++)  addLine(-20, stringPosY(i), strLength/2, stringPosY(i));
	// Bands
	for (int i = 0; i < 12; i++) addLine(bandPosition(i), 10, bandPosition(i), 140);

	// Circlemarks between band 2 and 3, betweein 4 and 5, between 6 and 7 and also between 8 and 9.
	int circlebands[] = {3, 5, 7, 9};
	for (int i = 0; i < 4; i++) {
		double centerX = (bandPosition(circlebands[i]) + bandPosition(circlebands[i] - 1))/2;
		addCircleAt(centerX, 75, Qt::white);
	}

	// Two circlemarks between band 11 and 12
	double centX = (bandPosition(12) + bandPosition(11))/2;
	double centY = (stringPosY(2) + stringPosY(1))/2;
	addCircleAt(centX, centY, Qt::white);
	centY = (stringPosY(4) + stringPosY(3))/2;
	addCircleAt(centX, centY, Qt::white);
	currentNoteCircle = 0;
	std::cout << "mouseGrabber: " << mouseGrabberItem() << std::endl;
	connect(&timer, SIGNAL(timeout()), SLOT(guessShown()));
}

Note GuitarBoard::min() {
	return looseStringNote(5);
}

Note GuitarBoard::max() {
	return looseStringNote(0) + 12;
}


void GuitarBoard::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	int band = currentBand = pos2Band(event->lastScenePos());
	int string = currentString = pos2String(event->lastScenePos());
	if (currentNoteCircle != 0) {
		removeItem(currentNoteCircle);
		delete currentNoteCircle;
		currentNoteCircle = 0;
	}
	currentNoteCircle = addCircleOnString(band, string, Qt::darkRed);
}

void GuitarBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	int band = pos2Band(event->lastScenePos());
	int string = pos2String(event->lastScenePos());
	if (band == currentBand && string == currentString) {
		timer.start(1000);
		emit guess(note(band, string));
	}
	else {
		guessShown();
	}
}

void GuitarBoard::guessShown() {
	removeGuessCircle();
}

void GuitarBoard::removeGuessCircle() {
	if (currentNoteCircle != 0) {
		removeItem(currentNoteCircle);
		delete currentNoteCircle;
		currentNoteCircle = 0;
	}
}

void GuitarBoard::noteGiven(Note note) {
	while (tmpCircles.size() > 0) {
		QGraphicsItem *circle = tmpCircles.at(tmpCircles.size() - 1);
		tmpCircles.pop_back();
		removeItem(circle);
		delete circle;
	}

	for (int string = 0; string < 6; string++) {
		int band = note - looseStringNote(string);
		if (0 <= band && band < 13) {
			tmpCircles.push_back(addCircleOnString(band, string, Qt::darkGreen));
		}
	}
}

QGraphicsItem* GuitarBoard::addCircleAt(double centX, double centY, QColor color) {
	QGraphicsEllipseItem* result = new QGraphicsEllipseItem(centX - circleRadius, centY - circleRadius, 2*circleRadius, 2*circleRadius);
	QBrush brush(Qt::SolidPattern);
	brush.setColor(color);
	result->setBrush(brush);
	addItem(result);
	return result;
}

QGraphicsItem* GuitarBoard::addCircleOnString(int band, int string, QColor color) {
	double x;
	if (band <= 0) {
		x = - circleRadius - 3;
	}
	else {
		if (band > 12) {
			band = 12;
		}
		x = (bandPosition(band) + bandPosition(band - 1))/2; - circleRadius;
	}
	double y = stringPosY(string);
	return addCircleAt(x, y, color);
}

double GuitarBoard::stringPosY(int n) {
	return 10 + (boardWidth - 20)*n/5;
}

double GuitarBoard::bandPosition(int n) {
		return strLength*(1 -  1/pow(twelftRootOf2, n));
}

int GuitarBoard::pos2Band(QPointF scenePos) {
	int band;
	for ( band = 0; band <= 12; band++)  if (bandPosition(band) >= scenePos.x()) break;
	return band;
}

int GuitarBoard::pos2String(QPointF pos) {
	double y = pos.y();
	if (y < spaceBesideStrings) y = spaceBesideStrings;
	if (y > boardWidth - spaceBesideStrings) y = boardWidth - spaceBesideStrings;

	return round((y - spaceBesideStrings)/spaceBetweenStrings);
}

int GuitarBoard::looseStringNote(int string) {
	static Note lsn[] = {76, 71, 67, 62, 57, 52};
	return lsn[string];
}

Note GuitarBoard::note(int band, int string) {
	return looseStringNote(string) + band;
}

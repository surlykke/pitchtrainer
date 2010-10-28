#include "guitarboard.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <Qt>

GuitarBoard::GuitarBoard(QObject *parent): QGraphicsScene(parent)
{
	// Paint a guitar board
	// Strings
	for (int i = 0; i < 6; i++)  addLine(0, stringPosY(i), strLength/2, stringPosY(i));
	// Bands
	for (int i = 0; i < 12; i++) addLine(bandPosition(i), 10, bandPosition(i), 140);

	// Circlemarks between band 2 and 3, 4 and 5, 6 and 7 and also 8 and 9.
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
}

void GuitarBoard::show(Note note, bool isAnswer)
{
	for (int string = 0; string < 6; string++)
	{
		for (int band = 0; band < 13; band++)
		{
			Note n = this->note(band, string);
			if (n == note)
			{
				QColor color = isAnswer ? Qt::darkRed : Qt::darkGreen;
				tmpCircles.push_back(addCircleOnString(band, string, color));
			}
		}
	}
}

void GuitarBoard::unshowNotes()
{
	while (tmpCircles.size() > 0)
	{
		QGraphicsItem *circle = tmpCircles.at(tmpCircles.size() - 1);
		tmpCircles.pop_back();
		removeItem(circle);
		delete circle;
	}
}

Note GuitarBoard::min()
{
	return looseStringNote(5);
}

Note GuitarBoard::max()
{
	return looseStringNote(0) + 12;
}


void GuitarBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	int band = currentBand = pos2Band(event->lastScenePos());
	int string = currentString = pos2String(event->lastScenePos());
	if (currentNoteCircle != 0) {
		removeItem(currentNoteCircle);
		delete currentNoteCircle;
		currentNoteCircle = 0;
	}
	currentNoteCircle = addCircleOnString(band, string, Qt::darkRed);
}

void GuitarBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	int band = pos2Band(event->lastScenePos());
	int string = pos2String(event->lastScenePos());
	if (band == currentBand && string == currentString) {
		Note n = note(band, string);
		n.play();
		emit guess(n);
	}
	if (currentNoteCircle != 0)
	{
		removeItem(currentNoteCircle);
		delete currentNoteCircle;
		currentNoteCircle = 0;
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

QGraphicsItem* GuitarBoard::addCircleOnString(int band, int string, QColor color)
{
	double x;
	if (band <= 0)
	{
		x = - circleRadius - 3;
	}
	else
	{
		if (band > 12) band = 12;
		x = (bandPosition(band) + bandPosition(band - 1))/2; - circleRadius;
	}
	double y = stringPosY(string);
	return addCircleAt(x, y, color);
}

double GuitarBoard::stringPosY(int n) {
	return 10 + (boardWidth - 20)*n/5;
}

double GuitarBoard::bandPosition(int n)
{
		return strLength*(1 -  1/pow(twelftRootOf2, n));
}

int GuitarBoard::pos2Band(QPointF scenePos)
{
	int band;
	for ( band = 0; band <= 12; band++)  if (bandPosition(band) >= scenePos.x()) break;
	return band;
}

int GuitarBoard::pos2String(QPointF pos)
{
	double y = pos.y();
	if (y < spaceBesideStrings) y = spaceBesideStrings;
	if (y > boardWidth - spaceBesideStrings) y = boardWidth - spaceBesideStrings;

	return round((y - spaceBesideStrings)/spaceBetweenStrings);
}

Note GuitarBoard::looseStringNote(int string)
{
	static std::vector<Note> map;
	if (map.size() == 0) {
		map.push_back(Note("E", 5));
		map.push_back(Note("B", 5));
		map.push_back(Note("G", 4));
		map.push_back(Note("D", 4));
		map.push_back(Note("A", 4));
		map.push_back(Note("E", 3));
	}
	return map[string];
}

Note GuitarBoard::note(int band, int string)
{
	return looseStringNote(string) + band;
}

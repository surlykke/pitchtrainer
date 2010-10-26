#include "guitarboard.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <math.h>

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
		addCircleAt(centerX, 75);
	}

	// Two circlemarks between band 11 and 12
	double centX = (bandPosition(12) + bandPosition(11))/2;
	double centY = (stringPosY(2) + stringPosY(1))/2;
	addCircleAt(centX, centY);
	centY = (stringPosY(4) + stringPosY(3))/2;
	addCircleAt(centX, centY);
}

void GuitarBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "mousePressEvent: (" << event->lastScenePos().x() << ", " << event->lastScenePos().y() << ")" << std::endl;
}

void GuitarBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "mouseReleaseEvent: (" << event->lastScenePos().x() << ", " << event->lastScenePos().y() << ")" << std::endl;
	pos2Note(event->lastScenePos()).play();
}

QGraphicsEllipseItem* GuitarBoard::addCircleAt(double centX, double centY, double radius) {
	QGraphicsEllipseItem* result = new QGraphicsEllipseItem(centX - radius, centY - radius, 2*radius, 2*radius);
	addItem(result);
	return result;
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

Note GuitarBoard::pos2Note(QPointF pos)
{
	static std::vector<Note> looseStringNote;
	if (looseStringNote.size() == 0) {
		looseStringNote.push_back(Note("E", 5));
		looseStringNote.push_back(Note("B", 5));
		looseStringNote.push_back(Note("G", 4));
		looseStringNote.push_back(Note("D", 4));
		looseStringNote.push_back(Note("A", 4));
		looseStringNote.push_back(Note("E", 3));
	}


	return looseStringNote[pos2String(pos)] + pos2Band(pos);
}

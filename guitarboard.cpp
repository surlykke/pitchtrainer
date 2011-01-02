/*
  Copyright 2010 Christian Surlykke 
 
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
#include "guitarboard.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <Qt>
#include <QDebug>
#include <QImageWriter>

GuitarBoard::GuitarBoard(QObject *parent): QGraphicsScene(parent),
               green_circle_smiley(":images/green_circle_smiley.png"),
               green_circle(":images/green_circle.png"),
               red_circle(":images/red_circle.png"),
               white_circle(":images/white_circle.png")
{
	// Paint a guitar board
    setBackgroundBrush(Qt::white);
    // Strings
	for (int i = 0; i < 6; i++)  addLine(-20, stringPosY(i), strLength/2, stringPosY(i));
	// Bands
	for (int i = 0; i < 12; i++) addLine(bandPosition(i), 10, bandPosition(i), 140);

	// Circlemarks between band 2 and 3, betweein 4 and 5, between 6 and 7 and also between 8 and 9.
	int circlebands[] = {3, 5, 7, 9};
	for (int i = 0; i < 4; i++) {
		double centerX = (bandPosition(circlebands[i]) + bandPosition(circlebands[i] - 1))/2;
                addImageAt(centerX, 75, white_circle);
	}

	// Two circlemarks between band 11 and 12
	double centX = (bandPosition(12) + bandPosition(11))/2;
	double centY = (stringPosY(2) + stringPosY(1))/2;
        addImageAt(centX, centY, white_circle);
	centY = (stringPosY(4) + stringPosY(3))/2;
        addImageAt(centX, centY, white_circle);
	currentNoteCircle = 0;
        connect(&timer, SIGNAL(timeout()), SLOT(donePlaying()));
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
        currentNoteCircle = addImageOnString(band, string, green_circle);
}

void GuitarBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    int band = pos2Band(event->lastScenePos());
	int string = pos2String(event->lastScenePos());
	if (band == currentBand && string == currentString) {
		emit guess(note(band, string));
	}
	else {
                removeGuessCircle();
        }
}

void GuitarBoard::donePlaying() {
    removeGuessCircle();
}

void GuitarBoard::removeGuessCircle() {
	if (currentNoteCircle != 0) {
		removeItem(currentNoteCircle);
		delete currentNoteCircle;
		currentNoteCircle = 0;
	}
}

void GuitarBoard::newExcercise(QList<Note>& notes) {
	clearNotes();
	showNotes(notes, false);
}

void GuitarBoard::answerFound(QList<Note>& notes) {
	showNotes(notes, true);
}

void GuitarBoard::gaveUp(QList<Note>& notes) {
    showNotes(notes, false);
}

void GuitarBoard::showNotes(QList<Note> &notes, bool answer) {
	QList<Note>::Iterator iterator;
	for (iterator = notes.begin(); iterator != notes.end(); iterator++) {
		Note note = *iterator;
		for (int string = 0; string < 6; string++) {
			int band = note - looseStringNote(string);
			if (0 <= band && band < 13) {
                            tmpCircles.push_back(addImageOnString(band, string, answer ? green_circle_smiley : green_circle));
                        }
		}
	}
}

void GuitarBoard::clearNotes() {
	while (tmpCircles.size() > 0) {
		QGraphicsItem *circle = tmpCircles.at(tmpCircles.size() - 1);
		tmpCircles.pop_back();
		removeItem(circle);
		delete circle;
	}
}


QGraphicsItem* GuitarBoard::addImageAt(double centX, double centY, QImage& image) {
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    item->setOffset(centX - image.width()/2, centY - image.height()/2);
    addItem(item);
    return item;
}

QGraphicsItem* GuitarBoard::addImageOnString(int band, int string, QImage& image) {
	double x;
	if (band <= 0) {
                x = - image.width()/2 - 3;
	}
	else {
		if (band > 12) {
			band = 12;
		}
                x = (bandPosition(band) + bandPosition(band - 1))/2; - image.width()/2;
	}
	double y = stringPosY(string);
        return addImageAt(x, y, image);
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

Note GuitarBoard::looseStringNote(int string) {
	static Note lsn[] = {76, 71, 67, 62, 57, 52};
	return lsn[string];
}

Note GuitarBoard::note(int band, int string) {
	return looseStringNote(string) + band;
}

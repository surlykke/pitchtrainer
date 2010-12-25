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
#ifndef GUITARBOARD_H
#define GUITARBOARD_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include "note.h"
#include <QList>

class GuitarBoard : public QGraphicsScene
{
    Q_OBJECT
public:

    explicit GuitarBoard(QObject *parent = 0);
	void unshowNotes();
	Note min();
	Note max();

signals:
	void guess(Note note);

public slots:
        void donePlaying();
	void newExcercise(QList<Note>& notes);
	void answer(QList<Note>& notes);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	static const int strLength = 1400;
	static const int boardWidth = 150;
	static const int spaceBesideStrings = 10;
	static const int circleRadius = 8;
	static const int spaceBetweenStrings = (boardWidth - 2*spaceBesideStrings)/5;
	static const double twelftRootOf2 = 1.0594630943593;

	void showNotes(QList<Note> &notes, bool answer);
	void clearNotes();
	QGraphicsItem* addCircleAt(double centX, double centY, QColor color);
	QGraphicsItem* addCircleOnString(int band, int string, QColor color);
	void removeGuessCircle();
	double stringPosY(int n);
	double bandPosition(int n);
	int pos2Band(QPointF scenePos);
	int pos2String(QPointF pos);
	Note note(int band, int string);
	Note looseStringNote(int string);
	QGraphicsItem* currentNoteCircle;
	int currentBand;
	int currentString;
	std::vector<QGraphicsItem*> tmpCircles;
	QTimer timer;
};

#endif // GUITARBOARD_H

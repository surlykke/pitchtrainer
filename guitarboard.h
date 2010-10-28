#ifndef GUITARBOARD_H
#define GUITARBOARD_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include "interval.h"
#include "note.h"

class GuitarBoard : public QGraphicsScene
{
    Q_OBJECT
public:
	static const int strLength = 1400;
	static const int boardWidth = 150;
	static const int spaceBesideStrings = 10;
	static const int circleRadius = 8;
	static const int spaceBetweenStrings = (boardWidth - 2*spaceBesideStrings)/5;
	static const double twelftRootOf2 = 1.0594630943593;

    explicit GuitarBoard(QObject *parent = 0);
	void show(Note note, bool isAnswer = false);
	void unshowNotes();

signals:
	void guess(Note& note);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QGraphicsItem* addCircleAt(double centX, double centY, QColor color);
	QGraphicsItem* addCircleOnString(int band, int string, QColor color);
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
};

#endif // GUITARBOARD_H

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
	void guessShown();
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

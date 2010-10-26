#ifndef GUITARBOARD_H
#define GUITARBOARD_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "note.h"

class GuitarBoard : public QGraphicsScene
{
    Q_OBJECT
public:
	static const int strLength = 1400;
	static const int boardWidth = 150;
	static const int spaceBesideStrings = 10;
	static const int spaceBetweenStrings = (boardWidth - 2*spaceBesideStrings)/5;
	static const double twelftRootOf2 = 1.0594630943593;

    explicit GuitarBoard(QObject *parent = 0);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QGraphicsEllipseItem* addCircleAt(double centX, double centY, double radius = 8);
	double stringPosY(int n);
	double bandPosition(int n);
	int pos2Band(QPointF scenePos);
	int pos2String(QPointF pos);
	Note pos2Note(QPointF pos);
};

#endif // GUITARBOARD_H

#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QGraphicsEllipseItem>

class Sensor : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
public:
	Sensor(int band, int string);

	int getString();
	int getBand();
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//	virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);

signals:
	void pressed(int band, int string);

private:
	int string;
	int band;
};

#endif // SENSOR_H

#include "sensor.h"
#include "mainwindow.h"
#include <iostream>
Sensor::Sensor(int band, int string) : QObject()
{
	this->band = band;
	this->string = string;
	const double rad = 9;

	double x = (band == 0) ?
			   -rad - 2 :
			   (MainWindow::bandPosition(band) + MainWindow::bandPosition(band - 1))/2;

	double y = MainWindow::stringPosY(string);

	setRect(x - rad, y - rad, 2*rad, 2*rad);
}

void Sensor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setOpacity(100);
	std::cout << "Pressed\n";
	std::cout.flush();

}


void Sensor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setOpacity(0.01);
	std::cout << "Hey\n";
	std::cout.flush();
	emit pressed(band, string);
}


/*void Sensor::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
	setOpacity(0);
	std::cout << "Howdy\n";
}*/

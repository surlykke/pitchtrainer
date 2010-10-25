#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <math.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	static const double strLength = 1400;
	static const double boardWidth = 150;
	static const double twelftRootOf2 = 1.0594630943593;
	static double stringPosY(int n);
	static double bandPosition(int n);

	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void pressed(int band, int string);
	void newInterval();
	void repeat();
	void giveUp();
	void exit();

private:
	Ui::MainWindow *ui;
	QGraphicsEllipseItem* circleAt(double centX, double centY, double radius = 8);

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "interval.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void newInterval();
	void repeat();
	void giveUp();

private:
	Ui::MainWindow *ui;
	Interval* interval;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "interval.h"
#include "guitarboard.h"

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
	void guess(Note& note);

private:
	Ui::MainWindow *ui;
	GuitarBoard *guitarBoard;
	Interval* interval;
};

#endif // MAINWINDOW_H

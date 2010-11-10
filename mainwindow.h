#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "guitarboard.h"
#include "midiplayer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
	void noteGiven(Note note);

public slots:
	void newInterval();
	void repeat();
	void giveUp();
	void guess(Note note);

private:
	Ui::MainWindow *ui;
	GuitarBoard *guitarBoard;
	Note note1, note2;
	MidiPlayer midiPlayer;
};

#endif // MAINWINDOW_H

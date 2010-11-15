#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "guitarboard.h"
#include "midiplayer.h"
#include <QList>

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
	void newExcercise(QList<Note>& notes);
	void answer(QList<Note>& notes);

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
	bool answerGiven;
};

#endif // MAINWINDOW_H

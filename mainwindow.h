#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "guitarboard.h"
#include "midiplayer.h"
#include <QString>
#include <QSettings>

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
	void newPitch();
	void repeat();
	void giveUp();
    void settings();
    void guess(Note note);
    void instrumentChanged(int newInstrument);

private:
	Ui::MainWindow *ui;
	GuitarBoard *guitarBoard;
	Note note1, note2;
	MidiPlayer midiPlayer;
	bool answerGiven;

    // Utils
    QString intervalName(Note note1, Note note2);
    QString noteName(Note n);
    QSettings *huske;
};

#endif // MAINWINDOW_H

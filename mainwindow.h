/*
  Copyright 2010 Christian Surlykke 
 
  This file is part of PitchTrainer.
 
  PitchTrainer is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, version 3 
 
  PitchTrainer is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with PitchTrainer.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "guitarboard.h"
#include "midiplayer.h"
#include <QString>
#include <QSettings>
#include "settings.h"

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
	void answerFound(QList<Note>& notes);
        void answerWrong();
        void gaveUp(QList<Note>& notes);

public slots:
	void newPitch();
	void repeat();
	void giveUp();
        void editSettings();
        void guess(Note note);

private:
	Ui::MainWindow *ui;
        Settings* settings;
        GuitarBoard *guitarBoard;
        MidiPlayer *midiPlayer;
        Note note1, note2;
        bool answerGiven;

    // Utils
    QString intervalName(Note note1, Note note2);
    QString noteName(Note n);
    QIcon appIcon;
};

#endif // MAINWINDOW_H

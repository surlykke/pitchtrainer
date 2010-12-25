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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "guitarboard.h"
#include "midiplayer.h"
#include "settings_dialog.h"
#include <QList>
#include <QDebug>
#include "ui_settings_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    settings = new Settings();
    midiPlayer = new MidiPlayer(settings);
    ui->setupUi(this);
    guitarBoard = new GuitarBoard(parent);
    ui->graphicsView->setScene(guitarBoard);

    std::cout.flush();
    ui->repeatButton->setEnabled(false);
    ui->giveUpButton->setEnabled(false);
    connect(ui->newPitchButton, SIGNAL(clicked()), SLOT(newPitch()));
    connect(ui->repeatButton, SIGNAL(clicked()), SLOT(repeat()));
    connect(ui->giveUpButton, SIGNAL(clicked()), SLOT(giveUp()));
    connect(ui->settingsButton, SIGNAL(clicked()), SLOT(editSettings()));
    connect(this, SIGNAL(newExcercise(QList<Note>&)), guitarBoard, SLOT(newExcercise(QList<Note>&)));
    connect(this, SIGNAL(answer(QList<Note>&)), guitarBoard, SLOT(answer(QList<Note>&)));
    connect(guitarBoard, SIGNAL(guess(Note)), SLOT(guess(Note)));
    connect(midiPlayer, SIGNAL(donePlaying()), guitarBoard, SLOT(donePlaying()));
}

void MainWindow::newPitch()
{
	int span = (guitarBoard->max() - guitarBoard->min()) - 20 + 1;
	note1 = guitarBoard->min() + 10 + rand() % span;
	int space = 0;
	while (space == 0) {
                space = rand() % 21 - 10;
	}
	note2 = note1 + space;
    qDebug() << noteName(note1) << "-->" << noteName(note2) << "    " << intervalName(note1, note2);
	ui->repeatButton->setEnabled(true);
	ui->giveUpButton->setEnabled(true);
        midiPlayer->playInterval(note1, note2);
	answerGiven = false;
	ui->message->setText("Identify the interval");
	emit newExcercise(QList<Note>() << note1);

}

void MainWindow::repeat()
{
        midiPlayer->playInterval(note1, note2);
}

void MainWindow::giveUp()
{
	if (answerGiven) {
		return;
	}
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);
        ui->message->setText(QString("%1 ->  %2   %3").arg(noteName(note1)).arg(noteName(note2)).arg(intervalName(note1, note2)));
	answerGiven = true;
	emit answer(QList<Note>() << note2);

}

void MainWindow::editSettings()
{
    qDebug() << "I editSettings, intervals er: " << settings->getIntervals();
    SettingsDialog settingsDialog(settings->getInstrument(), settings->getExcercise(), settings->getIntervals(), this);
    connect(settingsDialog.ui->instrumentBox, SIGNAL(currentIndexChanged(int)), settings, SLOT(instrumentChanged(int)));
    connect(settingsDialog.ui->excerciseBox, SIGNAL(currentIndexChanged(int)), settings, SLOT(excerciseChanged(int)));
    connect(&settingsDialog, SIGNAL(intervalAddedOrRemoved(int,bool)), settings, SLOT(intervalChanged(int,bool)));
    settingsDialog.exec();

}


void MainWindow::guess(Note note)
{
    qDebug() << "Ind i guess";
    if (answerGiven) {
		return;
	}
    midiPlayer->playNote(note);
	if (note == note2)
	{
                ui->message->setText(QString("Correct!  %1 -> %2   %3").arg(noteName(note1)).arg(noteName(note2)).arg(intervalName(note1, note2)));
		answerGiven = true;
		ui->giveUpButton->setEnabled(false);
		emit answer(QList<Note>() << note2);
	}
	else
	{
		ui->message->setText("Wrong!");
        }
    qDebug() << "Ud af guess";
}


MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::intervalName(Note n1, Note n2) {
    static QList<QString> intervalNames;

    if (intervalNames.size() == 0) {
           intervalNames <<
            "Perfect Unison" <<
            "Minor second" <<
            "Major second" <<
            "Minor third" <<
            "Major third" <<
            "Perfect fourth" <<
            "Diminished fifth" <<
            "Perfect fifth" <<
            "Minor sixth" <<
            "Major sixth" <<
            "Minor seventh" <<
            "Major seventh" <<
            "Perfect octave";
    }

    std::cout << n1 << ", " << n2 << " = " << (n2>n1? n2-n1:n1-n2) << std::endl;
    int diff = n2 >= n1 ? n2 - n1 : n1 - n2;
    return diff > 12 ? "?" : intervalNames.at(diff);
}

QString MainWindow::noteName(Note n) {
    static QList<QString> noteNames;

    if (noteNames.size() == 0) {
        noteNames << "C" << "C#" << "D" << "D#" << "E" << "F" << "F#" << "G" << "G#" << "A" << "A#" << "B";
    }

   int noteNumber = (((n - 60) % 12)  + 12) % 12;
   int octaveNumber = 4 + ((n - 60)/ 12);
   return noteNames.at(noteNumber) + QString::number(octaveNumber);
}

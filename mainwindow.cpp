#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "guitarboard.h"
#include "midiplayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow), note1(69), note2(69)
{
    ui->setupUi(this);
	guitarBoard = new GuitarBoard(parent);
	ui->graphicsView->setScene(guitarBoard);

	std::cout.flush();
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);
	connect(ui->newIntervalButton, SIGNAL(clicked()), SLOT(newInterval()));
	connect(ui->repeatButton, SIGNAL(clicked()), SLOT(repeat()));
	connect(ui->giveUpButton, SIGNAL(clicked()), SLOT(giveUp()));
	connect(this, SIGNAL(noteGiven(Note)), guitarBoard, SLOT(noteGiven(Note)));
	connect(guitarBoard, SIGNAL(guess(Note)), SLOT(guess(Note)));
}

void MainWindow::newInterval()
{
	int span = (guitarBoard->max() - guitarBoard->min()) - 20 + 1;
	note1 = guitarBoard->min() + 10 + rand() % span;
	int space = 0;
	while (space == 0) {
		space = rand() % 21 - 10;
	}
	note2 = note1 + space;
	std::cout << "Note1: " << note1 << ", note2: " << note2 << std::endl;
	ui->repeatButton->setEnabled(true);
	ui->giveUpButton->setEnabled(true);
	midiPlayer.play(note1, note2);
	emit noteGiven(note1);

}

void MainWindow::repeat()
{
	midiPlayer.play(note1, note2);
}

void MainWindow::giveUp()
{
	guitarBoard->noteGiven(note2);
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);

}

void MainWindow::guess(Note note)
{
	std::cout << "Ind i guess" << std::endl;
	midiPlayer.play(note);
	if (note == note2)
	{
		ui->message->setText("Correct!");
	}
	else
	{
		ui->message->setText("Wrong!");
	}
}
MainWindow::~MainWindow()
{
    delete ui;
}

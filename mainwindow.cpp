#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "guitarboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
	connect(guitarBoard, SIGNAL(guess(Note&)), SLOT(guess(Note&)));
}

void MainWindow::newInterval()
{
	int span = (guitarBoard->max() - guitarBoard->min()) - 20 + 1;
	note1 = guitarBoard->min() + 10 + rand() % span;
	int space = 0;
	while (space == 0) {
		space = rand() % 21 - 10;
	}
	std::cout << "Danner note2, note1 = " << note1 << ", space = " << space << std::endl;
	note2 = note1 + space;
	note1.play();
	note2.play();
	ui->repeatButton->setEnabled(true);
	ui->giveUpButton->setEnabled(true);
	guitarBoard->unshowNotes();
	guitarBoard->show(note1);
}

void MainWindow::repeat()
{
	note1.play();
	note2.play();
}

void MainWindow::giveUp()
{
	guitarBoard->show(note2, true);
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);

}

void MainWindow::guess(Note &note)
{
	std::cout << "Ind i guess" << std::endl;
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

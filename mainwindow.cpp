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
	interval = 0;
}

void MainWindow::newInterval()
{
	if (interval != 0) {
		delete interval;
		interval = 0;
	}
	interval = new Interval();
	interval->play();
	ui->repeatButton->setEnabled(true);
	ui->giveUpButton->setEnabled(true);
	guitarBoard->unshowNotes();
	guitarBoard->show(interval->note1);
}

void MainWindow::repeat()
{
	if (interval != 0) {
		interval->play();
	}
}

void MainWindow::giveUp()
{
	guitarBoard->show(interval->note2, true);
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);

}

void MainWindow::guess(Note &note)
{
	std::cout << "Ind i guess" << std::endl;
	if (note == interval->note2)
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

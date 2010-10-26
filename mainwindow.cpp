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
	GuitarBoard* guitarBoard = new GuitarBoard();
	ui->graphicsView->setScene(guitarBoard);


	std::cout.flush();
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);
	connect(ui->newIntervalButton, SIGNAL(clicked()), SLOT(newInterval()));
	connect(ui->repeatButton, SIGNAL(clicked()), SLOT(repeat()));
	connect(ui->giveUpButton, SIGNAL(clicked()), SLOT(giveUp()));
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
}

void MainWindow::repeat()
{
	if (interval != 0) {
		interval->play();
	}
}

void MainWindow::giveUp()
{
	if (interval != 0) {
		delete interval;
		interval = 0;
	}
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}

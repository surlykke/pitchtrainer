#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sensor.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	QGraphicsScene* scene = new QGraphicsScene();
	ui->graphicsView->setScene(scene);

	for (int i = 0; i < 6; i++)  scene->addLine(0, stringPosY(i), strLength/2, stringPosY(i));
	for (int i = 0; i < 12; i++) scene->addLine(bandPosition(i), 10, bandPosition(i), 140);

	int circlebands[] = {3, 5, 7, 9};
	for (int i = 0; i < 4; i++) {
		double centerX = (bandPosition(circlebands[i]) + bandPosition(circlebands[i] - 1))/2;
		scene->addItem(circleAt(centerX, 75));
	}
	double centX = (bandPosition(12) + bandPosition(11))/2;
	double centY = (stringPosY(2) + stringPosY(1))/2;
	scene->addItem(circleAt(centX, centY));
	centY = (stringPosY(4) + stringPosY(3))/2;
	scene->addItem(circleAt(centX, centY));

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++) {
			Sensor *s = new Sensor(j, i);
			connect(s, SIGNAL(pressed(int,int)), SLOT(pressed(int,int)));
			s->setOpacity(0.01);
			scene->addItem(s);

		}
	}

	std::cout.flush();
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);
	connect(ui->newIntervalButton, SIGNAL(clicked()), SLOT(newInterval()));
	connect(ui->repeatButton, SIGNAL(clicked()), SLOT(repeat()));
	connect(ui->giveUpButton, SIGNAL(clicked()), SLOT(giveUp()));
	connect(ui->exitButton, SIGNAL(clicked()), SLOT(exit()));
}

double MainWindow::bandPosition(int n)
{
		return strLength*(1 -  1/pow(twelftRootOf2, n));
}

double MainWindow::stringPosY(int n) {
	return 10 + (boardWidth - 20)*n/5;
}

QGraphicsEllipseItem* MainWindow::circleAt(double centX, double centY, double radius) {
	QGraphicsEllipseItem* result = new QGraphicsEllipseItem(centX - radius, centY - radius, 2*radius, 2*radius);
	return result;
}

void MainWindow::pressed(int band, int string) {
	std::cout << "String pressed(" << band << ", " << string << ")\n";
	std::cout.flush();
}

void MainWindow::newInterval()
{
	ui->repeatButton->setEnabled(true);
	ui->giveUpButton->setEnabled(true);
}



void MainWindow::repeat()
{
}

void MainWindow::giveUp()
{
	ui->repeatButton->setEnabled(false);
	ui->giveUpButton->setEnabled(false);
}

void MainWindow::exit()
{
	QMessageBox msgBox;
	msgBox.setText("Exit Interval trainer?");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.exec();
	if (msgBox.clickedButton() == msgBox.button(QMessageBox::Ok)) {
		QCoreApplication::exit(0);
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}

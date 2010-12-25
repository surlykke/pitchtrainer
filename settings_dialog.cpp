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
#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include "settings.h"
#include <QDebug>

SettingsDialog::SettingsDialog(Instrument instrument, int excercise, QList<bool> intervals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{ 
    ui->setupUi(this);
    intervalButtons.setExclusive(false);
    intervalButtons.addButton(ui->interval0, 0);
    intervalButtons.addButton(ui->interval1, 1);
    intervalButtons.addButton(ui->interval2, 2);
    intervalButtons.addButton(ui->interval3, 3);
    intervalButtons.addButton(ui->interval4, 4);
    intervalButtons.addButton(ui->interval5, 5);
    intervalButtons.addButton(ui->interval6, 6);
    intervalButtons.addButton(ui->interval7, 7);
    intervalButtons.addButton(ui->interval8, 8);
    intervalButtons.addButton(ui->interval9, 9);
    intervalButtons.addButton(ui->interval10, 10);
    intervalButtons.addButton(ui->interval11, 11);
    intervalButtons.addButton(ui->interval12, 12);

    ui->instrumentBox->setCurrentIndex(instrument);
    ui->excerciseBox->setCurrentIndex(excercise);
    qDebug() << "I settingsdialog construktor, intervals er: " << intervals;
    for (int interval = 0; interval < 13; interval++) {
        qDebug() << "Sætter knap " << interval << " til " << intervals[interval];
        intervalButtons.button(interval)->setChecked(intervals[interval]);
    }

    connect(&intervalButtons, SIGNAL(buttonClicked(int)), this, SLOT(checkboxClicked(int)));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}

void SettingsDialog::checkboxClicked(int checkboxnr) {
    emit intervalAddedOrRemoved(checkboxnr, intervalButtons.button(checkboxnr)->isChecked());
}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::backButtonClicked() {
    done(0);
}

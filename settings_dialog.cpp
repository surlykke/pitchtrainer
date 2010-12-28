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

SettingsDialog::SettingsDialog(Settings *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{ 
    ui->setupUi(this);
    this->settings = settings;
    ui->instrumentBox->setCurrentIndex(settings->getInstrument());
    ui->excerciseBox->setCurrentIndex(settings->getExcercise());
    QList<bool> intervals = settings->getIntervals();
    for (int i = 0; i < 13; i++) {
        ui->intervalList->item(i)->setCheckState(intervals[i] ? Qt::Checked : Qt::Unchecked);
    }
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}



SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::okButtonClicked() {
    settings->setInstrument(ui->instrumentBox->currentIndex());
    settings->setExcercise(ui->excerciseBox->currentIndex());
    QList<bool> intervals;
    for (int i = 0; i < 13; i++) {
        intervals << (ui->intervalList->item(i)->checkState() == Qt::Checked);
    }
    settings->setIntervals(intervals);
    done(0);
}

void SettingsDialog::cancelButtonClicked() {
    done(0);
}

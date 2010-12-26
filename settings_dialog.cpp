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

    ui->instrumentBox->setCurrentIndex(instrument);
    ui->excerciseBox->setCurrentIndex(excercise);
    for (int i = 0; i < 13; i++) {
        ui->intervalList->addItem(QString("%1").arg(i));
    }
    ui->intervalList->setSelectionMode(QAbstractItemView::MultiSelection);

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}



SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::backButtonClicked() {
    done(0);
}

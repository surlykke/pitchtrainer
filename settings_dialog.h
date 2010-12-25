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
#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QList>
#include <QCheckBox>
#include "midiplayer.h"
#include <QButtonGroup>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(Instrument instrument, int excercise, QList<bool> intervals, QWidget *parent = 0);
    ~SettingsDialog();
    Ui::SettingsDialog *ui;
    QButtonGroup intervalButtons;

signals:
    void intervalAddedOrRemoved(int interval, bool added);

public slots:
    void checkboxClicked(int checkboxnr);
    void backButtonClicked();

};

#endif // SETTINGS_DIALOG_H

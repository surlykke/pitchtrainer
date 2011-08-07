/*
  Copyright 2010, 2011 Christian Surlykke

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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QList>
#include <QString>

class Settings : public QSettings
{
  Q_OBJECT
public:
  Settings(QObject *parent = 0);
  Q_INVOKABLE QVariant instrument();
  Q_INVOKABLE void setInstrument(QVariant instrument);
  Q_INVOKABLE QVariant excercise();
  Q_INVOKABLE void setExcercise(QVariant excercise);
  Q_INVOKABLE QList<QVariant> intervals();
  Q_INVOKABLE void setIntervals(QList<QVariant> intervals);
};

#endif // SETTINGS_H

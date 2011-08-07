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
#include "settings.h"
#include <QCoreApplication>
#include <QDebug>

Settings::Settings(QObject *parent) : QSettings(parent) {
}

QVariant Settings::instrument() {
  return value("instrument");
}

void Settings::setInstrument(QVariant instrument) {
  setValue("instrument", instrument);
}

QVariant Settings::excercise() {
  return value("excercise");
}

void Settings::setExcercise(QVariant excercise) {
  setValue("excercise", excercise);
}

QList<QVariant> Settings::intervals() {
  return value("intervals").toList();
}

void Settings::setIntervals(QList<QVariant> intervals) {
  setValue("intervals", intervals);
}

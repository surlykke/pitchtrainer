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

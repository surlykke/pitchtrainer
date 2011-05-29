#include "settings.h"
#include <QCoreApplication>
#include <QDebug>

Settings::Settings(QObject *parent) : QSettings(parent) {
}

int Settings::getInstrument() {
    return  value("instrument", 0).toInt();
}

void Settings::setInstrument(int instrument) {
    setValue("instrument", instrument);
}


int Settings::getExcercise() {
    return value("excercise", 0).toInt();
}

void Settings::setExcercise(int excercise) {
    setValue("excercise", excercise);
}



QList<bool> Settings::getIntervals() {
    QList<QVariant> temp = getIntervals_helper();
    QList<bool> result;
    for (int i = 0; i < 13; i++) {
        result << temp[i].toBool();
    }
    return result;
}

QList<QVariant> Settings::getIntervals_helper() {
    QList<QVariant> temp = value("intervals").toList();
    if (temp.size() != 13) {
        temp.clear();
        temp << true << true << true << true << true << true << true << true << true << true << true << true << true;
        setValue("intervals", temp);
    }
    return temp;
}



void Settings::setIntervals(QList<bool> newIntervals) {
    QList<QVariant> intervals;
    for (int i = 0; i < 13; i++) {
        intervals << newIntervals[i];
    }
    setValue("intervals", intervals);
}

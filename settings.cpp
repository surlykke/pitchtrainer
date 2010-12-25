#include "settings.h"
#include <QCoreApplication>
#include <QDebug>

Settings::Settings(QObject *parent) : QSettings(parent) {
}

Instrument Settings::getInstrument() {
    qDebug() << "Getting instrument: " << value("intrument", 0);
    return  value("instrument", 0).toInt();
}

int Settings::getExcercise() {
    qDebug() << "Getting excercise: " << value("excercise", 0);
    return value("excercise", 0).toInt();
}

QList<bool> Settings::getIntervals() {
    QList<QVariant> temp = getIntervals_helper();
    QList<bool> result;
    for (int i = 0; i < 13; i++) {
        result << temp[i].toBool();
    }
    qDebug() << "Getting :" << temp;
    return result;
}

QList<QVariant> Settings::getIntervals_helper() {
    QList<QVariant> temp = value("intervals").toList();
    qDebug() << "temp: " << temp;
    if (temp.size() != 13) {
        temp.clear();
        temp << true << true << true << true << true << true << true << true << true << true << true << true << true;
        setValue("intervals", temp);
    }
    return temp;
}

void Settings::instrumentChanged(int newInstrument) {
    qDebug() << "instrumentChanged: " << newInstrument;
    setValue("instrument", newInstrument);
}

void Settings::excerciseChanged(int newExcercise) {
    qDebug() << "excerciseChanged: " << newExcercise;
    setValue("excercise", newExcercise);
}

void Settings::intervalChanged(int interval, bool enabled) {
    qDebug() << "Ind i intervalChanged";
    if (interval < 0 || interval > 12) return;

    QList<QVariant> intervals = getIntervals_helper();
    intervals[interval] = enabled;
    qDebug() << "Setting: " << intervals;
    setValue("intervals", intervals);

}

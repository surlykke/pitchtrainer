#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <note.h>
#include <QList>

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    Instrument getInstrument();
    void setInstrument(Instrument instrument);

    int getExcercise();
    void setExcercise(int excercise);

    QList<bool> getIntervals();
    void setIntervals(QList<bool> intervals);

private:
    QList<QVariant> getIntervals_helper();
};

#endif // SETTINGS_H

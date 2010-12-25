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
    int getExcercise();
    QList<bool> getIntervals();

public slots:
    void instrumentChanged(int newInstrument);
    void excerciseChanged(int newExcercise);
    void intervalChanged(int interval, bool enabled);

private:
    QList<QVariant> getIntervals_helper();
};

#endif // SETTINGS_H

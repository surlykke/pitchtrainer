#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QList>

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    int getInstrument();
    void setInstrument(int instrument);

    int getExcercise();
    void setExcercise(int excercise);

    QList<bool> getIntervals();
    void setIntervals(QList<bool> intervals);

private:
    QList<QVariant> getIntervals_helper();
};

#endif // SETTINGS_H

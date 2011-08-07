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

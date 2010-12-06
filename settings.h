#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "midiplayer.h"

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    Settings(int instrument, QWidget *parent = 0);
    ~Settings();
    Ui::Settings *ui;

public slots:
    void backButtonClicked();

};

#endif // SETTINGS_H

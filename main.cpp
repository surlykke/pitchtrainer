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
#include <QtGui/QApplication>
#include <QDebug>
#include <QDeclarativeView>
#include <QDeclarativeError>
#include <QObject>
#include <QGraphicsObject>
#include <QCoreApplication>
#include <QDeclarativeContext>
#include "settings.h"
#include "midiplayer.h"
#include <time.h>

int main(int argc, char *argv[])
{
    qDebug() << "Ind i main" << "\n";
    QCoreApplication::setOrganizationName("Surlykke IT");
    QCoreApplication::setOrganizationDomain("surlykke-it.dk");
    QCoreApplication::setApplicationName("Pitch Trainer");

    QApplication app(argc, argv);
    Settings settings;

    QDeclarativeView view;
    view.rootContext()->setContextProperty("applicationSettings", &settings);
    view.setSource(QUrl("qrc:/qml/PitchTrainerRoot.qml"));
    qDebug() << view.errors() << "\n";
    QObject *obj = dynamic_cast<QObject*>(view.rootObject());
    view.showFullScreen();

    MidiPlayer midiPlayer(&settings);

    QObject::connect(obj, SIGNAL(play(int)), &midiPlayer, SLOT(playNote(int)));
    QObject::connect(obj, SIGNAL(playInterval(int, int)), &midiPlayer, SLOT(playInterval(int, int)));

    return app.exec();
}

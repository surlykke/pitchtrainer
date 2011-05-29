# Copyright 2010 Christian Surlykke 
#
# This file is part of PitchTrainer.
#
# PitchTrainer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 
#
# PitchTrainer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PitchTrainer.  If not, see <http://www.gnu.org/licenses/>.
#-------------------------------------------------
#
# Project created by QtCreator 2010-10-20T22:14:10
#
#-------------------------------------------------

QT       += core gui multimedia declarative

TARGET = PitchTrainer
TEMPLATE = app


SOURCES += main.cpp\
           midiplayer.cpp \
           settings_dialog.cpp \
           settings.cpp

HEADERS  += \
            midiplayer.h \
            settings_dialog.h \
            settings.h

FORMS    += mainwindow.ui \
            settings_dialog.ui

LIBS += -L/usr/lib/ -lWildMidi

RESOURCES += \
    images.qrc \
    qml.qrc

OTHER_FILES += \
    images/Rød prik med smiley.png \
    images/Prik grøn med smiley.png \
    images/Prik grøn.png \
    band.qml \
    string.qml \
    circle.qml \
    Button.qml \
    GuitarBoard.qml \
    guitarboard.js \
    Main.qml \
    main.js \
    boardarea.js \
    BoardArea.qml

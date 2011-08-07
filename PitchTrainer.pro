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
           settings.cpp \
    pcmplayer.cpp

HEADERS  += \
            midiplayer.h \
            settings.h \
    pcmplayer.h

FORMS    +=

LIBS += -L/usr/lib/ -L/scratchbox/users/christian/targets/HARMATTAN_X86/usr/lib/ -lWildMidi

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
    GuitarBoard.qml \
    guitarboard.js \
    main.js \
    boardarea.js \
    BoardArea.qml \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    PitchTrainerSettings.qml \
    PitchTrainerMain.qml \
    PitchTrainerRoot.qml

unix:!symbian:!maemo5 {
    target.path = /opt/PitchTrainer/bin
    INSTALLS += target
}















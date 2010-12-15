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

QT       += core gui multimedia

TARGET = PitchTrainer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    guitarboard.cpp \
    midiplayer.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    guitarboard.h \
    midiplayer.h \
    note.h \
    settings.h

FORMS    += mainwindow.ui \
    settings.ui

LIBS += -L/usr/lib/ -lWildMidi

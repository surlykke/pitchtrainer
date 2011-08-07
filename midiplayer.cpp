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
#include "midiplayer.h"
#include <stdio.h>
#include <unistd.h>
#include <QProcess>
#include <QByteArray>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>
#include <QStringList>
#include <QDateTime>
#include <QThread>

extern "C" {
#include "wildmidi_lib.h"
}

MidiPlayer::MidiPlayer(Settings *settings):  QObject() {
    qDebug() << "Ind i midiplayer constructor" << "\n";
    this->settings = settings;
    WildMidi_Init("/etc/wildmidi/wildmidi.cfg", 44100, 0);

}

MidiPlayer::~MidiPlayer() {

}

void MidiPlayer::playNote(int n)
{
    qDebug() << "-->playNote(" << n << ")";
    unsigned char instrument = (unsigned char) settings->value("instrument").toInt();
    unsigned char noteMidi[] =  {
        0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
        0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/second
        0x4D, 0x54, 0x72, 0x6B,                         // Track header
        0x00, 0x00, 0x00, 0x0F,                         // 15 bytes of event data
        0x00, 0xc0, instrument,                         // Set instrument
        0x00, 0x90,    n, 0xF0,                         // note on at time 0
        0x60, 0x80,    n, 0x00,                         // note off at 96/144 beats
        0x00, 0xFF, 0x2F, 0x00                          // end of track
    };
    QFile fil("/tmp/note.mid");
    fil.open(QIODevice::WriteOnly);
    fil.write((char*) noteMidi, sizeof(noteMidi));
    playMidi(noteMidi, sizeof(noteMidi));
}

void MidiPlayer::playInterval(int n1, int n2)
{
    qDebug() << "-->playInterval(" << n1 << ", " << n2 << ")";
    unsigned char instrument = (unsigned char) settings->value("instrument").toInt();
    unsigned char intervalMidi[] = {
        0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
        0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/beat.
        0x4D, 0x54, 0x72, 0x6B,                         // Track header
        0x00, 0x00, 0x00, 0x18,                         // 18 bytes of event data
        0x00, 0xc0, instrument,                         // Set instrument
        0x00, 0x90,   n1, 0xF0,                         // First note on at time 0
        0x60, 0x80,   n1, 0x00,                         // First note off at 96/144 beats
        0x60, 0x90,   n2, 0xF0,                         // Second note on at 96/144 beats
        0x81, 0x40, 0x80,   n2, 0x00,                   // Second note off at 192/144 beats
        0x00, 0xFF, 0x2F, 0x00                          // end of track
    };
    QFile fil("/tmp/interval.mid");
    fil.open(QIODevice::WriteOnly);
    fil.write((char*) intervalMidi, sizeof(intervalMidi));
    playMidi(intervalMidi, sizeof(intervalMidi));
}

void MidiPlayer::playMidi(unsigned char *mididata, unsigned long size) {
    unsigned char* mididataCopy = (unsigned char*) malloc(size);  // WildMidi insists on freeing the memory used to hold mididata
    memcpy(mididataCopy, mididata, size);             // on close, so we have to make a copy of mididata

    midi* midiPtr = WildMidi_OpenBuffer(mididataCopy, size);
    QByteArray buffer;
    int bufsize = 1000000;
    char buf[bufsize];
    int converted;
    while ((converted = WildMidi_GetOutput(midiPtr, buf, bufsize)) > 0) {
      buffer.append(buf, converted);
    }
    qDebug() << "Buffersize: " << buffer.size();

    unsigned char wavHdr[] = {
             0x52, 0x49, 0x46, 0x46, 0xac, 0x3b, 0x09, 0x00,
             0x57, 0x41, 0x56, 0x45, 0x66, 0x6d, 0x74, 0x20,
             0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
             0x48, 0x7d, 0x00, 0x00, 0x20, 0xf5, 0x01, 0x00,
             0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61,
             0x88, 0x3b, 0x09, 0x00
    };

    QFile fil("/tmp/output.wav");
    fil.open(QIODevice::WriteOnly);
    fil.write((char*) wavHdr, sizeof(wavHdr));
    fil.write(buffer);

    wavPlayer.play(buffer);
}

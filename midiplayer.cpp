/*
  Copyright 2010 Christian Surlykke 
 
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

extern "C" {
#include "wildmidi_lib.h"
}

MidiPlayer::MidiPlayer():  QObject(), process() {
    this->instrument = 0;
    WildMidi_Init("/etc/timidity/timidity.cfg", 44100, 0);
}

MidiPlayer::~MidiPlayer() {
}

void MidiPlayer::playNote(Note note)
{
    unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
                                 0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/second
                                 0x4D, 0x54, 0x72, 0x6B,                         // Track header
                                 0x00, 0x00, 0x00, 0x0F,                         // 15 bytes of event data
                                 0x00, 0xc0, instrument,                         // Set instrument
                                 0x00, 0x90, note, 0xF0,                         // note n on at time
                                 0x60, 0x80, note, 0x00,                         // note n off at 96/144 beats
                                 0x00, 0xFF, 0x2F, 0x00                          // end of track
                               };
        // play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));
    play2(mididata, sizeof(mididata));
}

void MidiPlayer::playInterval(Note n1, Note n2)
{
    unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
                                 0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/beat.
                                 0x4D, 0x54, 0x72, 0x6B,                         // Track header
                                 0x00, 0x00, 0x00, 0x18,                         // 18 bytes of event data
                                 0x00, 0xc0, instrument,                         // Set instrument
                                 0x00, 0x90, n1, 0xF0,                           // note un1 on at time 0
                                 0x60, 0x80, n1, 0x00,                           // note un1 off at 96/144 beats
                                 0x60, 0x90, n2, 0xF0,                           // note un2 on at 96/144 beats
                                 0x81, 0x40, 0x80, n2, 0x00,                     // note un2 off at 192/144 beats
                                 0x00, 0xFF, 0x2F, 0x00                          // end of track
                               };
//    play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));

    play2(mididata, sizeof(mididata));
}

void MidiPlayer::play(QByteArray arr)
{
    while (process.state() != 0) {
        process.waitForFinished();
    }
    process.start("/usr/bin/gst-launch-0.10 playbin uri=fd://0");
    process.write(arr);
    process.closeWriteChannel();
}

void MidiPlayer::play2(unsigned char *mididata, unsigned long size) {
    static char* wav_data = 0;
    static int wav_hdr_size = 0;
    if (wav_data == 0) {
        wav_data = (char*) malloc(250000);
        const char wav_hdr[] = { 0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00,
                                 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
                                 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
                                 0x44, 0xAC, 0x00, 0x00, 0x10, 0xB1, 0x02, 0x00,
                                 0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61,
                                 0x00, 0x00, 0x00, 0x00 };
        wav_hdr_size = sizeof(wav_hdr);
        memcpy(wav_data, wav_hdr, wav_hdr_size);
    }

    midi* midiPtr = WildMidi_OpenBuffer(mididata, size);
    int outputsize = WildMidi_GetOutput(midiPtr, wav_data + wav_hdr_size, 250000 - wav_hdr_size) + wav_hdr_size;
    qDebug() << "outputsize: " << outputsize;

    process.start("/usr/bin/gst-launch-0.10 playbin uri=fd://0");
    process.write(wav_data, outputsize);
    process.closeWriteChannel();
}

int MidiPlayer::getInstrument() {
    return instrument;
}

void MidiPlayer::setInstrument(int instrument) {
    qDebug() << "Setting instrument to " << instrument;
    this->instrument = instrument;
}

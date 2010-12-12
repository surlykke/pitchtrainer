#include "midiplayer.h"
#include <stdio.h>
#include <unistd.h>
#include <QProcess>
#include <QByteArray>
#include <iostream>
#include <QDebug>
#include <QFile>

MidiPlayer::MidiPlayer():  QObject(), process() {
    this->instrument = 0;
}

MidiPlayer::~MidiPlayer() {
}

void MidiPlayer::playNote(Note note)
{
        unsigned char n = (unsigned char) note;
    unsigned char u_instr = (unsigned char) instrument;
        unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
                                     0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/second
                                     0x4D, 0x54, 0x72, 0x6B,                         // Track header
                                     0x00, 0x00, 0x00, 0x0F,                         // 15 bytes of event data
                                     0x00, 0xc0, u_instr,                            // Set instrument
                                     0x00, 0x90, n, 0xF0,                            // note n on at time
                                     0x60, 0x80, n, 0x00,                            // note n off at 96/144 beats
                                     0x00, 0xFF, 0x2F, 0x00                          // end of track
                                   };
	play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));
}

void MidiPlayer::playInterval(int n1, int n2)
{
	unsigned char un1 = (unsigned char) n1;
	unsigned char un2 = (unsigned char) n2;
    unsigned char u_instr = (unsigned char) instrument;
    unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
                                 0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/beat.
                                 0x4D, 0x54, 0x72, 0x6B,                         // Track header
                                 0x00, 0x00, 0x00, 0x18,                         // 18 bytes of event data
                                 0x00, 0xc0, u_instr,                            // Set instrument
                                 0x00, 0x90, un1, 0xF0,                          // note un1 on at time 0
                                 0x60, 0x80, un1, 0x00,                          // note un1 off at 96/144 beats
                                 0x60, 0x90, un2, 0xF0,                          // note un2 on at 96/144 beats
                                 0x81, 0x40, 0x80, un2, 0x00,                    // note un2 off at 192/144 beats
                                 0x00, 0xFF, 0x2F, 0x00                          // end of track
                               };
	play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));
}

void MidiPlayer::play(QByteArray arr)
{
	while (process.state() != 0) {
		process.waitForFinished();
        }
    process.start("/usr/bin/gst-launch-0.10 playbin uri=fd://0");
    process.write(arr);
    process.closeWriteChannel();
    // QFile file("/tmp/IntervalTrainerOut.mid");
//    file.open(QIODevice::WriteOnly);
 //   file.write(arr);
  //  file.close();
    //process.start("/usr/bin/gst-launch-0.10 playbin uri=file:///tmp/IntervalTrainerOut.mid");


    //process.start("/usr/bin/timidity", QStringList() << "-");
        // process.write(arr);
        // process.closeWriteChannel();
}

int MidiPlayer::getInstrument() {
    return instrument;
}

void MidiPlayer::setInstrument(int instrument) {
    qDebug() << "Setting instrument to " << instrument;

    this->instrument = instrument;
}

#include "midiplayer.h"
#include <stdio.h>
#include <unistd.h>
#include <QProcess>
#include <QByteArray>
#include <iostream>
#include <QDebug>

MidiPlayer::MidiPlayer():  QObject(), process() {
    this->instrument = 0;
}

MidiPlayer::~MidiPlayer() {
}

void MidiPlayer::playNote(Note note)
{
	unsigned char n = (unsigned char) note;
	unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
								 0x00, 0x00, 0x00, 0x01, 0x00, 0x90,
								 0x4D, 0x54, 0x72, 0x6B, 0x00, 0x00, 0x00, 0x11,
                                                                 0x00, 0xc0, instrument,
								 0x00, 0x90, n, 0xF0, 0x60, 0x80, n, 0x00,
								 0x00, 0xFF, 0x2F, 0x00 };
	play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));
}

void MidiPlayer::playInterval(int n1, int n2)
{
	unsigned char un1 = (unsigned char) n1;
	unsigned char un2 = (unsigned char) n2;
	unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
								 0x00, 0x00, 0x00, 0x01, 0x00, 0x90,
								 0x4D, 0x54, 0x72, 0x6B, 0x00, 0x00, 0x00, 0x16,
                                                                 0x00, 0xc0, instrument,
								 0x00, 0x90, un1, 0xF0, 0x60, 0x80, un1, 0x00,
								 0x60, 0x90, un2, 0xF0, 0x81, 0x40, 0x80, un2, 0x00,
								 0x00, 0xFF, 0x2F, 0x00 };
	play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));
}

void MidiPlayer::play(QByteArray arr)
{
	while (process.state() != 0) {
		process.waitForFinished();
	}
	process.start("/usr/bin/timidity", QStringList() << "-");
	process.write(arr);
	process.closeWriteChannel();
}

int MidiPlayer::getInstrument() {
    return instrument;
}

void MidiPlayer::setInstrument(int instrument) {
    qDebug() << "Setting instrument to " << instrument;

    this->instrument = instrument;
}

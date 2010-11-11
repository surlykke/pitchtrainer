#include "midiplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QProcess>
#include <QByteArray>
#include <iostream>
MidiPlayer::MidiPlayer(): process() {
}

unsigned char MidiPlayer::getInstrument() {
	return instrument;
}

void MidiPlayer::setInstrument(unsigned char instrument) {
	if (instrument > 127) {
		std::cerr << "Instrument should be in range 0..127, defaulting to 0" << std::endl;
		instrument = 0;
	}
	this->instrument = instrument;
}

float MidiPlayer::getNoteLength() {
	return noteLength;
}

void MidiPlayer::setNoteLength(float noteLength) {
	this->noteLength = noteLength;
}

/*void MidiPlayer::playNote()
{
	unsigned char n = (unsigned char) note;
	unsigned char mididata[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
								 0x00, 0x00, 0x00, 0x01, 0x00, 0x90,
								 0x4D, 0x54, 0x72, 0x6B, 0x00, 0x00, 0x00, 0x11,
								 0x00, 0xc0, 0x22,
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
								 0x00, 0xc0, 0x22,
								 0x00, 0x90, un1, 0xF0, 0x60, 0x80, un1, 0x00,
								 0x60, 0x90, un2, 0xF0, 0x81, 0x40, 0x80, un2, 0x00,
								 0x00, 0xFF, 0x2F, 0x00 };
	play(QByteArray(reinterpret_cast<const char*>(mididata), sizeof(mididata)));
}*/

void MidiPlayer::play(std::vector<Note> notes, bool sequential)
{
	QByteArray midiData;
	const char midiHeader[]    = {0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x90};
	midiData.append(midiHeader, sizeof(midiHeader));


	QByteArray events;
	const char program_change[] = {0x00, 0xC0, instrument};
	events.append(program_change, sizeof(program_change)); // Program change
	unsigned long time = 0;
	std::vector<Note>::iterator it;
	for (it = notes.begin(); it != notes.end(); it++) {
		events.append(long2varlen(time)).append(0x90).append((char) *it).append(0xF0); // Note on
		events.append(long2varlen(time + 0x60)).append(0x80).append((char) *it).append((char) 0x00); // Note off
	}
	const char endOfTrack[] = {0x00, 0xFF, 0x2F, 0x00 };
	events.append(endOfTrack, sizeof(endOfTrack));
	unsigned short trackSize = events.size();
	const char trackHeader[]   = {0x4D, 0x54, 0x72, 0x6B, 0x00, 0x00, trackSize & 0xFF00, trackSize & 0xFF};
	midiData.append(trackHeader, sizeof(trackHeader));
	midiData.append(events);

	std::cout << "Process state: " << process.state() << std::endl;
	if (process.state() != 0) {
		std::cout << "Killing..." << std::endl;
		process.kill();
		process.waitForFinished();
	}
	process.start("/usr/bin/timidity", QStringList() << "-");
	QByteArray::iterator qbit;
	for (qbit = midiData.begin(); qbit != midiData.end(); qbit++) {
		std::cout << *qbit << " ";
	}
	std::cout << std::endl;

	process.write(midiData);
	process.closeWriteChannel();
}

void MidiPlayer::play(Note note)
{
	std::vector<Note> notes;
	notes.push_back(note);
	play(notes);
}

void MidiPlayer::play(Note note1, Note note2)
{
	std::vector<Note> notes;
	notes.push_back(note1);
	notes.push_back(note2);
	play(notes);
}

QByteArray MidiPlayer::long2varlen(unsigned long val)
{
	if (val > 0x1FFFFF) throw "Overflow";

	QByteArray result;
	char c = val & 0x7F;
	result.insert(0, c);
	val = val >> 7;
	while (val > 0) {
		char c = ((val & 0x7F) | 0x80);
		result.insert(0, c);
		val = val >> 7;
	}
	return result;
}

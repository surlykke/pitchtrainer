#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H
#include "note.h"
#include <qprocess.h>
#include <vector>

class MidiPlayer
{
public:
	MidiPlayer();
	unsigned char getInstrument();
	void setInstrument(unsigned char instrument);
	float getNoteLength();
	void setNoteLength(float noteLength);
	void play(std::vector<Note> notes, bool sequential = true);
	void play(Note note);
	void play(Note note1, Note note2);
private:
	QByteArray long2varlen(unsigned long val);
	unsigned char instrument;
	float noteLength;
	QProcess process;
};

#endif // MIDIPLAYER_H

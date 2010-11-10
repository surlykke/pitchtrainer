#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H
#include "note.h"
#include <qprocess.h>

class MidiPlayer
{
public:
    MidiPlayer();
	void playNote(Note note);
	void playInterval(int n1, int n2);
private:
	void play(QByteArray arr);
	QProcess process;
};

#endif // MIDIPLAYER_H

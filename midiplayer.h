#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H
#include "note.h"
#include <qprocess.h>
#include <QObject>

class MidiPlayer: public QObject
{
    Q_OBJECT

public:
    MidiPlayer();
    ~MidiPlayer();
    void playNote(Note note);
	void playInterval(int n1, int n2);
    int getInstrument();

public slots: 
    void setInstrument(int instrument);

private:
	void play(QByteArray arr);
    QProcess process;
    int instrument;
};

#endif // MIDIPLAYER_H

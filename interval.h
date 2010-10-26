#ifndef INTERVAL_H
#define INTERVAL_H

#include "note.h"
class Interval
{
public:
    Interval();
	void play();
private:
	Note note1;
	Note note2;
};

#endif // INTERVAL_H

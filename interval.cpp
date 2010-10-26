#include "interval.h"

Interval::Interval(): note1("A", 5), note2("D", 5)
{
}

void Interval::play()
{
	note1.play();
	note2.play();
}

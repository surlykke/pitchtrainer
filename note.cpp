#include "note.h"
#include <iostream>
Note::Note(std::string note, int octave)
{
	this->note_index = string2int(note);
	this->octave = octave;
}

std::string Note::getNote()
{
	return int2string(note_index);
}

int Note::getOctave()
{
	return octave;
}

void Note::play()
{
	std::cout << *this << std::endl;
}

std::ostream& operator <<(std::ostream &out, Note &note)
{
	return (out << note.getNote() << note.getOctave());
}

Note& operator++(Note &note)
{
	note.octave = note.octave + (note.note_index + 1)/12;
	note.note_index = (note.note_index + 1) % 12;
	return note;
}

Note Note::operator +(int i)
{
	return Note(note_index + i, octave);
}

Note Note::operator -(int i)
{
	return Note(note_index - i, octave);
}

bool Note::operator ==(Note note)
{
	return note.note_index == note_index && note.octave == octave;
}

Note::Note(int i, int octave)
{
	note_index = i % 12;
	this->octave = octave + i/12;
}

std::vector<std::string> Note::getIntStringMap()
{
	static std::vector<std::string> map;
	if (map.size() == 0)
	{
		map.push_back("A");
		map.push_back("Ais");
		map.push_back("B");
		map.push_back("C");
		map.push_back("Cis");
		map.push_back("D");
		map.push_back("Dis");
		map.push_back("E");
		map.push_back("F");
		map.push_back("Fis");
		map.push_back("G");
		map.push_back("Gis");
	}
	return map;
}


int Note::string2int(std::string str)
{
	for (int i = 0; i < getIntStringMap().size(); i++)
	{
		if (getIntStringMap()[i] == str)
			return i;
	}
	return -1;
}


std::string Note::int2string(int i)
{
	return getIntStringMap()[i % 12];
}

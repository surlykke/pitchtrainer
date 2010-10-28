#ifndef NOTE_H
#define NOTE_H
#include <string>
#include <vector>
#include <iostream>

class Note
{
public:
	Note(std::string note, int octave);
	std::string getNote();
	int getOctave();
	friend Note& operator++(Note &note);
	bool operator==(Note note);
	Note operator+(int semitones);
	Note operator-(int semitones);
	void play();
	friend std::ostream& operator<< (std::ostream &out, Note &note);

private:
	Note(int i, int octave);
	int string2int(std::string str);
	std::string int2string(int i);
	int note_index;
	int octave;
	static std::vector<std::string> getIntStringMap();
};

#endif // NOTE_H

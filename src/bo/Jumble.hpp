#ifndef JUMBLE_H
#define JUMBLE_H

#include "../entity/Dictionary.h"

class Jumble
{
public:
				Jumble(Dictionary&, int = 5);	// Default public constructor
	
	void		setDifficulty(int&);			// Sets difficulty level
	int			getDifficulty();				// Returns current difficulty level
	void		update();						// Loads a new word
	
	bool		checkWord(const string&);		// Checks word against player's guess
	
	string		getJumbled();					// Returns jumbled version of the currently loaded word
	string		getHint();						// Returns definition of the currently loaded word

private:
	string		toUpper(const string&);			// Converts a string to uppercase letters (to allow case-insensitive searches)
	void		randomize();					// Randomizes the positions of letters of the loaded word

	Dictionary&	wordList;						// Reference to the Dictionary object
	string		jumbledWord;					// Jumbled-up letters of the currently loaded word
	Word		currentWord;					// Currently loaded word
	uint		difficultyLevel;				// length of word = difficultyLevel ± 1
};
#endif
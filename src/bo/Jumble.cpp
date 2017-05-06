#include "Jumble.hpp"


/*
Default public constructor, used for initializations.
: parameters: Dictionary& dict (reference to the Dictionary object which has
			  list of words in the database).
			  int level (difficulty level of the game, default is 5)
*/
Jumble::Jumble(Dictionary& dict, int level)
	: wordList(dict)
{
	setDifficulty(level);
}


/*
Loads a new word of length as specified in the difficulty level.
Jumbles-up the word by randomizing its letter positions.
*/
void Jumble::update()
{
	do
	{
		currentWord = wordList.getWord();
	} while (currentWord.getWord().size() < difficultyLevel ||
			 currentWord.getWord().size() > 1.5 * difficultyLevel);
	
	randomize();
}


/*
Checks if player's guess matches the currently loaded guess.
: parameter: const string& guess (player's guess).
: returns true if player has guessed correctly, false if not.
*/
bool Jumble::checkWord(const string& guess)
{
	return toUpper(guess) == toUpper(currentWord.getWord());
}


/*
Returns the jumbled-up version of the currently loaded word.
*/
string Jumble::getJumbled()
{
	return jumbledWord;
}


/*
Returns definition of the currently loaded word.
*/
string Jumble::getHint()
{
	return currentWord.getDefinition();
}


/*
Sets difficulty level of the game. Difficulty level is reflected in the
length of the words that would be used in the game. This length can never
be less than 3.
: parameter: int level (level of difficulty)
*/
void Jumble::setDifficulty(int& level)
{
	if (level > 8) level = 8;
	if (level < 3) level = 3;

	level <= 3 ?
		difficultyLevel = 3 :
		difficultyLevel = level;
}


/*
Returns current difficulty level
*/
int Jumble::getDifficulty()
{
	return difficultyLevel;
}


/*
Converts a given string to uppercase letters. Original string is not affected.
All words will be converted to uppercase to provide case-insensitive search
functionality.
: parameter: const string& str (string to be converted to uppercase).
: returns copy of the given string in uppercase letters.
*/
string Jumble::toUpper(const string& str)
{
	for (char c : str)
		toupper(c);

	return str;
}


/*
Randomizes the positions of letters of the loaded word
*/
void Jumble::randomize()
{
	jumbledWord = currentWord.getWord();

	for (uint i = 0; i < jumbledWord.size(); i++)
		std::swap(jumbledWord.at(i), jumbledWord.at(rand() % jumbledWord.size()));
}
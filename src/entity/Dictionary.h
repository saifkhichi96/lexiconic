#ifndef DICT_H
#define DICT_H

#define LIST

#include <vector>
#include "Word.h"
#include <ctime>
#include <stack>

using std::string;
using std::vector;

#include "ListSingle.h"
typedef Single_List<Word> WordList;

/*
A hybrid data structure made up of 3D array of linked-lists (or dynamic arrays).

Consider this one-dimensional array of 26 elements. Each element is
a linked list containing all words starting with the letters a-z.

 0	 1	 2	 3	 4	 5 	 6	 7	 8	 9	 ... 26
 _______________________________________________
|a	|b	|c	|d	|e	|f	|g	|h	|i	|j	|...|z	|
 -----------------------------------------------

 If we extend it into two-dimensions, it would look something like
 this:
     0    1    2    3    4    5    6    7    8    9  ...  26
    __________________________________________________________
0  | aa | ba | ca | da | ea | fa | ga | ha | ia | ja |...| za |
    ----------------------------------------------------------
1  | ab | bb | cb | db | eb | fb | gb | hb | ib | jb |...| zb |
    ----------------------------------------------------------
2  | ac | bc | cc | dc | ec | fc | gc | hc | ic | jc |...| zc |
    ----------------------------------------------------------
:  | :: | :: | :: | :: | :: | :: | :: | :: | :: | :: |...| :: |
    ----------------------------------------------------------
26 | az | bz | cz | dz | ez | fz | gz | hz | iz | jz |...| zz |
    ----------------------------------------------------------
Each cell in the above array contains a list of words starting with
letters indicated in that cell.

This concept is further extended into three-dimensions which gives us
a fairly random access as average time to access an element is cut
down considerably.
*/
class Dictionary
{
public:
	bool			insert(const string&, const string&);		// Inserts a new word
	bool			update(const string&, const string&);		// Updates definition of an existing word
	bool			remove(const string&);						// Deletes a word
	const string&	lookUp(const string&);						// Searches for definition of a word

	Word			getWord();									// Returns a random word
	Word*			getSequence(const int);						// Returns an array of random words
	vector<string>	wordsWithPrefix(string&);					// Returns all words starting with given prefix

	bool			diskIn(const string&);						// Reads in dictionary data from a text file
	bool			diskOut(const string&);						// Writes contents of the dictionary to a text file

private:
	string			toUpper(const string&);						// Converts a string to uppercase letters (to allow case-insensitive searches)
	int				indexOf(char) const;						// Converts an alphabet to a numeric value, e.g. indexOf('a') -> 0
	char			atIndex(int) const;							// Converts a number to corresponding alphabet, e.g. atIndex('25') -> z
	bool			loacteList(const string&, int&, int&, int&);// Locates appropriate list (cell) from the 3D structure

	WordList		wordList[26][26][26];						// 3D array of singly-linked lists
};

#endif
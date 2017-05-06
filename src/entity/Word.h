#ifndef WORD_H
#define WORD_H
#include <string>

using std::ostream;
using std::istream;
using std::string;

/*
Word represents one word in the dictionary. Each word has a key value and
a definition. The class also provides a set of overloaded operators to
facilitate comparisons.
*/
class Word
{
public:
			Word(string = "", string = "");		// Default public constructor
			operator string();					// Typecasts Word to a string
	
	string&	getWord();							// Returns reference to the key value
	string&	getDefinition();					// Returns reference to the definition
	
	bool	operator == (const Word&) const;	// Do the two words have same keys?
	bool	operator != (const Word&) const;	// Do the two words not have same keys?
	bool	operator >= (const Word&) const;	// Is this word's key alphabetically greater or equal to the second word's key?
	bool	operator <= (const Word&) const;	// Is this word's key alphabetically lesser or equal to the second word's key?
	bool	operator >  (const Word&) const;	// Is this word's key alphabetically greater than the second word's key?
	bool	operator <  (const Word&) const;	// Is this word's key alphabetically lesser than the second word's key?

	friend ostream& operator << (ostream&, Word&);	// Sends a word to the output stream (file, display, etc.)
	friend istream& operator >> (istream&, Word&);	// Reads a word from the input stream

	Word* next;									// For linear chaining method of collision resolution in hash table

private:
	string key;									// Word
	string definition;							// Definition of the word
};

#endif
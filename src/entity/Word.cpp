#include "Word.h"
using std::endl;

/*
Default constructor of the Word class. Used for initialization.
: parameters: string wd (Key value of the Word object, empty by default)
			  string def (Definition of the Word object, empty by default)
*/
Word::Word(string wd, string def)
	: key(wd), definition(def), next(NULL)
{
	
}


/*
Typecasts an object of type Word to a string by returning its key.
*/
Word::operator string()
{
	return key;
}


/*
Returns reference to the key of the word.
*/
string& Word::getWord()
{
	return key;
}


/*
Returns reference to the definition of the word.
*/
string& Word::getDefinition()
{
	return definition;
}


/*
Checks two Word objects for eqaulity. Two Words are considered same
if they have same keys.
: parameters: const Word& (against which current Word is checked for equality).
: returns bool indicating whether the current Word and Word passed as argument are
  equal or not.
*/
bool Word::operator == (const Word& wd) const
{
	return key == wd.key;
}


/*
Checks two Word objects for ineqaulity. Two Words are considered different
if they have different keys.
: parameters: const Word& (against which current Word is checked for inequality).
: returns bool indicating whether the current Word and Word passed as argument are
  different or not.
*/
bool Word::operator != (const Word& wd) const
{
	return key != wd.key;
}


/*
Checks if one Word object is alphabetically greater than or equal to other Word object.
: parameters: const Word& (against which current Word is checked).
: returns bool indicating whether the current Word is greater than or equal to Word in
  argument or not.
*/
bool Word::operator >= (const Word& wd) const
{
	return key >= wd.key;
}


/*
Checks if one Word object is alphabetically lesser than or equal to other Word object.
: parameters: const Word& (against which current Word is checked).
: returns bool indicating whether the current Word is lesser than or equal to Word in
  argument or not.
*/
bool Word::operator <= (const Word& wd) const
{
	return key <= wd.key;
}


/*
Checks if one Word object is alphabetically greater than another Word object.
: parameters: const Word& (against which current Word is checked).
: returns bool indicating whether the current Word is greater than the Word in
  argument or not.
*/
bool Word::operator >  (const Word& wd) const
{
	return key > wd.key;
}


/*
Checks if one Word object is alphabetically lesser than another Word object.
: parameters: const Word& (against which current Word is checked).
: returns bool indicating whether the current Word is lesser than the Word in
  argument or not.
*/
bool Word::operator <  (const Word& wd) const
{
	return (key < wd.key);
}


/*
Sends a Word object to an output stream. This method is used to print a Word object
on screen and/or to write it in a file.
: parametrs: ostream& out (reference to the stream where Word is to be sent)
			 Word& wd (reference to the word to be sent)
: returns reference to the output stream to allow chaining as in cout << word_1 << word_2;
*/
ostream& operator << (ostream& out, Word& wd)
{
	out << wd.getWord() << endl;
	out << wd.getDefinition() << '$';

	return out;
}


/*
Reads a Word object from an input stream. This method is used to read a Word object
from keyboard and/or from a file.
: parametrs: istream& in (reference to the stream from where Word is to be read)
			 Word& wd (reference to the Word object where data that is read will be stored)
: returns reference to the input stream to allow chaining as in cin >> word_1 >> word_2;
*/
istream& operator >> (istream& in, Word& wd)
{
	getline(in, wd.getWord());
	getline(in, wd.getDefinition(), '$');

	return in;
}
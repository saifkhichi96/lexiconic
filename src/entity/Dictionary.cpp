#include "Dictionary.h"
#include <fstream>


/*
Returns a random word from the Dictionary.
*/
Word Dictionary::getWord()
{
	// While a word has not been found
	while (true)
	{
		// Pick up a random list from the 26x26x26 lists available
		auto& list = wordList[rand() % 26][rand() % 26][rand() % 26];

		// Get the size of the list
		int size = list.size();

		// If the list is not empty
		if (size != 0)
		{
			// Choose a random word from the list
			auto wd = list[rand() % size];
			
			// If this is a valid word, return this word
			if (wd.getWord() != "") return wd;
		}
	}
}


/*
Chooses specified number of random words from the Dictionary.
: parameter: const int len (number of words to be returned)
: returns pointer to the array containing specified number of random words
*/
Word* Dictionary::getSequence(const int len)
{
	/*
	Create a new list to store words
	(Required no. of words will be retrieved from the Dictionary at
	 random and stored in this list, which will eventually be returned
	 to the caller method.)
	*/
	auto selectedWords = new Word[len];


	/*
	Retrieve 'len' number of random words using the getWord method and
	put them in the 'selectedWords' array.
	*/
	for (int count = 0; count < len; count++)
		selectedWords[count] = getWord();


	/*
	Selected number of words are returned to the caller function. This
	list of words can have possible duplicates but will always contain
	asked number of words. That is, the words are not guaranteed to be
	distinct.
	*/
	return selectedWords;
}


/*
Inserts a new Word (word and definition) into the Dictionary.
: parameters: const string& word (word to be inserted).
			  const string& def (definition of the word to be inserted).
: returns an indication of whether the word has been successfully inserted
  or not.
*/
bool Dictionary::insert(const string& word, const string& def)
{
	int row = 0, col = 0, layer = 0;

	if (loacteList(word, row, col, layer) == true)
	{
		wordList[row][col][layer].append(Word(toUpper(word), def));
		return true;
	}

	return false;
}


/*
Updates definition of an existing Word in the Dictionary.
: parameters: const string& word (word to be updated).
			  const string& new_def (new definition of the word).
: returns an indication of whether the word's definition has been successfully
  updated or not.
*/
bool Dictionary::update(const string& word, const string& new_def)
{
	int row = 0, col = 0, layer = 0;
	
	if (loacteList(word, row, col, layer) == true)
	{
		auto node = wordList[row][col][layer].search(Word(toUpper(word), ""));
		if (node)
		{
			node->getDefinition() = new_def;
			return true;
		}
	}

	return false;
}


/*
Searches for definition of a word.
: parameter: const string& word (word to be looked up)
: returns constant reference to the definition if found, "Not found" otherwise
*/
const string& Dictionary::lookUp(const string& word)
{
	int row = 0, col = 0, layer = 0;

	if (loacteList(word, row, col, layer) == true)
	{
		auto node = wordList[row][col][layer].search(Word(toUpper(word), ""));
		if (node)
		{
			return node->getDefinition();
		}
	}

	return *new string("Not found");
}


/*
Reads data from text file and puts it in the structure.
: parameter: const string& FILENAME (name of the file to read data from).
: returns true on successfully reading data, false in case of an error.
*/
bool Dictionary::diskIn(const string& FILENAME)
{
	ifstream infile(FILENAME);
	string word, meaning;

	// If the file could not be loaded
	if (!infile)
	{
		cout << "\nError loading data from file: " << FILENAME << endl;
		cout << "Closing now ..." << endl;
		return false;
	}

	// Load data into memory
	while (!infile.eof())
	{
		getline(infile, word);								// Skip a line
		getline(infile, word);								// Read word/phrase till end of the line
		getline(infile, meaning, '$');						// Read multilined definition of this word till a '$' is encountered

		insert(word, meaning);								// Insert word into Dictionary
	}

	return true;
}


/*
Saves all the data in Dictionary structure to a text file.
: parameter: const string& FILENAME (name of the file to write data to).
: returns true on successfully saving data, false in case of an error.
*/
bool Dictionary::diskOut(const string& FILENAME)
{
	ofstream fout(FILENAME);
	fout << endl;
	for (int row = 0; row < 26; row++)
		for (int col = 0; col < 26; col++)
			for (int layer = 0; layer < 26; layer++)
			{
				for (uint i = 0; i < wordList[row][col][layer].size(); i++)
				{
					if (wordList[row][col][layer][i].getWord() != "")
						fout << wordList[row][col][layer][i] << endl;
				}
			}
	return true;
}


/*
Converts an alphabet into a number corresponding to the array index where words
starting with that alphabet could be found. For example, indexOf('a') will return
0 and indexOf('S') will return 18.
: parameter: char alphabet (letter whose index is needed)
: returns integer index corresponding to the passed alphabet. If the character
  given in the argument of the function call was not an alphabet, -1 is returned
  to indicate an error.
*/
int Dictionary::indexOf(char alphabet) const
{
	if (alphabet >= 'A' && alphabet <= 'Z')
		return alphabet - 'A';

	else if (alphabet >= 'a' && alphabet <= 'z')
		return alphabet - 'a';

	else return -1;
}


/*
Converts an numeric index into an alphabet. For example, atIndex(1) could translate
into 'what alphabet could be found at array index 1?'. atIndex(1) will return 'b'.
These indices are used to access appropriate lists from the 3D array of lists.
: parameter: int index (index whose corresponding letter is to be found).
: returns an alphabet corresponding to the given index. If the index is outside the
  range of alphabets (that is, 0-25 inclusive), a null character is returned to
  indicate an error.
*/
char Dictionary::atIndex(int index) const
{
	return (index >= 0 && index <= 25) ? static_cast<char>(index + 65) : '\0';
}


/*
Locates index of the appropriate list from the 26x26x26 lists available.
: parameters: const string& wd (word for which corresponding list is needed).
			  int& row (first-dimensional index of the required list).
			  int& col (second-dimensional index of the required list).
			  int& layer (third-dimensional index of the required list).
: returns true if a list is successfully located, false otherwise.
*/
bool Dictionary::loacteList(const string& wd, int& row, int& col, int& layer)
{
	if (wd.size() >= 1)	row = indexOf(wd[0]);
	if (wd.size() >= 2)	col = indexOf(wd[1]);
	if (wd.size() >= 3)	layer = indexOf(wd[2]);

	if (layer != -1 && row != -1 && col != -1)
		return true;

	else
		return false;
}


/*
Converts a given string to uppercase letters. Original string is not affected.
All words will be converted to uppercase to provide case-insensitive search
functionality.
: parameter: const string& str (string to be converted to uppercase).
: returns copy of the given string in uppercase letters.
*/
string Dictionary::toUpper(const string& str)
{
	string upper = str;

	for (auto it = upper.begin(); it != upper.end(); it++)
	{
		*it = toupper(*it);
	}

	return upper;
}


/*
Finds all words that have the given word as a prefix (i.e. that start with the
given string).
: parameter: string& prefix (prefix words starting with which are to be searched).
: returns array of words starting with given prefix (if any).
*/
vector<string> Dictionary::wordsWithPrefix(string& prefix)
{
	vector<string> words;

	int row = 0, col = 0, layer = 0;
	prefix = toUpper(prefix);

	loacteList(prefix, row, col, layer);

	if (row != -1 && col != -1 && layer != -1)
	{
		for (uint x = 0; x < wordList[row][col][layer].size(); x++)
		{
			string word = wordList[row][col][layer][x].getWord();

			bool flag = true;
			uint i = 0, j = 0;
			for (; i < prefix.size() && j < word.size(); i++, j++)
			{
				if (word[i] != prefix[i])
				{
					flag = false;
					break;
				}
			}

			if (i == prefix.size() && j <= word.size() && flag)
				words.push_back(word);
		}
	}
	if (prefix.size() == 2)
	{
		for (int layer = 0; layer < 26; layer++)
		{
			for (uint x = 0; x < wordList[row][col][layer].size(); x++)
			{
				string word = wordList[row][col][layer][x].getWord();

				bool flag = true;
				uint i = 0, j = 0;
				for (; i < prefix.size() && j < word.size(); i++, j++)
				{
					if (word[i] != prefix[i])
					{
						flag = false;
						break;
					}
				}

				if (i == prefix.size() && j <= word.size() && flag)
					words.push_back(word);
			}
		}
	}

	return words;
}
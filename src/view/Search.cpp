#include "11 - Search Screen.hpp"


//------------------------------------------------------------------------------//
//            class SearchWord                                                  //
//                  User interface of the search submodule of the dictionary    //
//                  part of the system.                                         //
//------------------------------------------------------------------------------//
SearchWord::SearchWord()
	: ClearQueryButton("", 730, 525, 30, 30),
	MAX_RESULTS(10), RESULT_COUNT(0), isSearching(false)
{
	textures.load("Clear_Query", "res/drawable/dictionary/clear.png");
	textures.load("Search_Box_Text", "res/drawable/dictionary/search_box_placeholder.png");
	textures.load("Result", "res/drawable/dictionary/search_result.png");
	textures.get("Result").setSize(800, 600);

	ClearQueryButton.setImage(&textures.get("Clear_Query"));

	addButton("Search Box", Button(&textures.get("Search_Box_Text"), 260, 515, 515, 50));
}


void SearchWord::Display()
{
	// Clear query button shown when searching, placeholder shown else
	isSearching ?
		ClearQueryButton.Display() :
		getButton("Search Box").Display();

	// Search result buttons (created dynamically, maximum 5 search results at a time)
	if (!SearchResults.empty())
	{
		for (uint i = 0; i < RESULT_COUNT; i++){
			SearchResults[i].Display();
		//	cout << SearchResults[i].getLabel() << endl;
		}
	}

	gout.setColor(Black);
	gout.setFont(GLUT_BITMAP_HELVETICA_18);
	gout.setPosition(345, 535);
	gout << string(query);

	if (query == "" &&
		!(word.getDefinition() == "Not found" || word.getDefinition() == ""))
	{
		textures.get("Result").Display();
		gout.setColor(Black);
		gout.setFont(GLUT_BITMAP_TIMES_ROMAN_24);
		gout.setPosition(175, 475);
		gout << string(word.getWord());

		gout.setLineWidth(85);
		gout.setFont(GLUT_BITMAP_HELVETICA_12);
		gout.setPosition(150, 375);
		gout << string(word.getDefinition());

		gout.setColor(Black);
		gout.setFont(GLUT_BITMAP_HELVETICA_18);
	}
}


void SearchWord::KeyboardEvents(unsigned char& key, int&, int&)
{
	if (isSearching)
	{
		switch (key)
		{
		case BACKSPACE:
			if (query != "")
			{
				query.pop_back();
			}
			break;
		default:
			word.getWord() = "";
			word.getDefinition() = "";
			query.push_back(key);
			break;
		}
		Search(query);
	}
}


void SearchWord::MouseEvents(int& button, int& state, int& x, int& y)
{
	if (state == 0 && button == 0)
	{
		if (query == "" && 
			!(word.getDefinition() == "Not found" || word.getDefinition() == ""))
		{
			word.getDefinition() = "";
			word.getWord() = "";
			SearchResults.clear();
			RESULT_COUNT = 0;
			isSearching = false;
		}

		if (ClearQueryButton.isClicked(x, y))
		{
			query = "";
			SearchResults.clear();
			RESULT_COUNT = 0;
			isSearching = false;
		}
		else if (getButton("Search Box").isClicked(x, y))
		{
			isSearching = true;
		}

		if (!SearchResults.empty())
		{
			for (uint i = 0; i < RESULT_COUNT; i++)
			{
				if (SearchResults[i].isClicked(x, y))
				{
					query = "";
					word.getWord() = SearchResults[i].getLabel();
					word.getDefinition() = wordList.lookUp(word.getWord());

					if (word.getDefinition() == "Not found")
					{
						word.getDefinition() = userDictionary.lookUp(word.getWord());
					}

					SearchResults.clear();
					RESULT_COUNT = 0;
				}
			}
		}
	}
}


void SearchWord::Search(string& query)
{
	if (query.empty())
	{
		SearchResults.clear();
		RESULT_COUNT = 0;
	}

	else
	{
		vector<string> results;
		vector<string> inbuilt = wordList.wordsWithPrefix(query);
		vector<string> user = userDictionary.wordsWithPrefix(query);
		results.reserve(inbuilt.size() + user.size()); // preallocate memory
		results.insert(results.end(), inbuilt.begin(), inbuilt.end());
		results.insert(results.end(), user.begin(), user.end());
		SearchResults.clear();
		RESULT_COUNT = 0;

		for (uint i = 0; i < results.size() && i < MAX_RESULTS; i++)
		{
			if (RESULT_COUNT == 0)
			{
				SearchResults.push_back(Button(results[i], 260, 485, 515, 30, Black, 0.65f));
				RESULT_COUNT++;
			}

			else if (RESULT_COUNT < MAX_RESULTS)
			{
				int yPos = SearchResults.rbegin()->getY() - 32;
				SearchResults.push_back(Button(results[i], 260, yPos, 515, 30, Black, 0.65f));
				RESULT_COUNT++;
			}
		}
	}
}


void SearchWord::onStop()
{
	isSearching = false;
	SearchResults.clear();
	RESULT_COUNT = 0;

	word.getWord() = "";
	word.getDefinition() = "";
	query = "";
}

vector<string> SearchWord::getSuggestions(string query)
{
	/*
	This method implements the auto-complete feature of the Dictionary
	by looking for all words starting with the given query and suggesting
	some of them to the user. Number of suggestions are limited by a pre-
	defined upper bound MAX_RESULTS
	: parameter: string query (string against which suggestions are required)
	: returns a vector of suggested words
	*/

	vector<string> suggestions;													// This dynamic array will hold the suggested words

	vector<string> inbuilt = wordList.wordsWithPrefix(query);					// Get suggestions from built-in dictionary database.
	vector<string> user = userDictionary.wordsWithPrefix(query);				// Get suggestions from user dictionary.

	suggestions.reserve(inbuilt.size() + user.size());
	suggestions.insert(suggestions.end(), inbuilt.begin(), inbuilt.end());
	suggestions.insert(suggestions.end(), user.begin(), user.end());

	return suggestions;
}
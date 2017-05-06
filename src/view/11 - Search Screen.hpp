#pragma once
#include "GUI.hpp"


class SearchWord : public Activity
{
public:
				SearchWord();
	void		Display();
	void		KeyboardEvents(unsigned char&, int&, int&);
	void		MouseEvents(int&, int&, int&, int&);
	void		onStop();

private:
	bool		isSearching = false;
	vector<string> getSuggestions(string);
	void		Search(string&);

	Word		word;
	string		query;

	Button		ClearQueryButton;
	deque<Button> SearchResults;
	uint		RESULT_COUNT;
	const uint	MAX_RESULTS;
};
#ifndef DICT_UI_HPP
#define DICT_UI_HPP
#include "GUI.hpp"

#include "11 - Search Screen.hpp"
#include "12 - Word of the Day Screen.hpp"
#include "13 - VocaBank Screen.hpp"


class DictionaryUI : public GUI
{
public:
			DictionaryUI();									// Default public constructor
	void	Display();										// Defines the layout of the activity.
	void	MouseEvents(int&, int&, int&, int&);			// Defines program behaviour on mouse input.
	void	PassiveMotionEvents(int&, int&);				// Defines program behaviour on mouse motion.
	void	KeyboardEvents(unsigned char& key, int&, int&);	// Defines program behaviour on keyboard events.
	void	IdleGL();										// Used for periodic updates

	void	onStart();										// Called everytime this activity is set active
	void	onStop();										// Called everytime this activity is closed

private:
	void	loadTextures();									// Loads images
	void	createButtons();								// Creates buttons

	bool	insertingWord;									// Flag to indicate that a new word is being inserted
	bool	updatingDefinition;								// Flag to indicate that a definition is being updated
	bool	wordBoxSelected;								// Flag to indicate that the Word Text Box is selected
	bool	definitionBoxSelected;							// Flag to indicate that the Definition Text Box is selected

	string	word;											// Active word
	string	definition;										// Active definition
	
	string	activeScreen;									// Contain the ID of active screen
	SearchWord	searchScreen;								// Search definitions activity
	TodaysWord	dailyWordScreen;							// Word of the day activity
	VocaBank	vocaBankScreen;								// Vocabulary bank activity
//	UserDictionary userDictionaryScreen;					// User dictionary activity
};

#endif
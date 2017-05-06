#ifndef GAMES_UI_HPP
#define GAMES_UI_HPP
#include "GUI.hpp"

#define GAME_COLOR 0.855f, 0.263f, 0.227f

class GamesUI : public GUI
{
public:
			GamesUI();
	void	Display();
	void	onClick(UIElement&);
	void	PassiveMotionEvents(int&, int&);
};

#endif

#ifndef SUDOKU_UI_HPP
#define SUDOKU_UI_HPP
#include "../bo/Sudoku.h"

class SudokuUI : public GamesUI
{
public:
			SudokuUI();
	void	Display();
	void	KeyboardEvents(unsigned char&, int&, int&);
	void	onClick(UIElement&);
	void	onStop();

private:
	void	SelectCell(int, int);
	void	DeselectCell(int, int);
	void	CreateBoard();
	void	UpdateLabels();

	int		sRow;										// Currently selected row
	int		sCol;										// Currently selected col
	bool	isStarted;									// Flag to indicate game status
	Sudoku	_Sudoku;									// Game object
};

#endif

#ifndef WORD_TRAIN_UI_HPP
#define WORD_TRAIN_UI_HPP
#include "../bo/WordTrain.hpp"

// Interface of the Word Train game
class WordTrainUI : public GamesUI
{
public:
				WordTrainUI();								// Constructor
	void		Display();									// Defines layout
	void		KeyboardEvents(unsigned char&, int&, int&);	// Handles keyboard inputs
	void		onStart();									// Called when this Activity is started

private:
	WordTrain	gameObject;									// Word Train game object
	bool		isStarted;									// Indicates game satues (being played/not yet started)
};

#endif

#ifndef JUMBLE_UI_HPP
#define JUMBLE_UI_HPP
#include "../bo/Jumble.hpp"

class JumbleUI : public GamesUI
{
public:
			JumbleUI();
	void	Display();
	void	KeyboardEvents(unsigned char&, int&, int&);
	void	KeyboardSpecialEvents(int&, int&, int&);
	void	onClick(UIElement&);
	void	onStart();

private:
	void	startGame();
	
	bool	playerHasGuessed;
	bool	correctGuess;
	bool	isOver;

	Jumble	gameObject;
	int		wordLength;
	string	playerGuess;
	int		activeLetter;
};

#endif

#ifndef HANGMAN_UI_HPP
#define HANGMAN_UI_HPP
class Hangman : public GamesUI
{
public:
	Hangman();
	void	Display();
	void	KeyboardEvents(unsigned char&, int&, int&);
	void	onClick(UIElement&);
	void	onStop()
	{
		isOver = false;
		isStarted = false;
		wrongGuesses = 0;
		playersGuess = "";
		usedKeys.clear();
		wordIndex++;
		getButton("GH_1").setLabel("Start");
	}
private:
	void	init_game_states();
	void	game_end_display();
	void	print_hint();
	void	print_player_guess();
	void	print_player_lives();
	void	list_used_keys();
	bool	find_match(const char&);

	typedef	unsigned int uint;
	typedef vector<char> chars;

	Word*	loadedWords;
	uint	wordIndex;
	Word	currentWord;
	string	playersGuess;
	chars	usedKeys;
	uint	noOfWords;
	bool	isOver, isStarted;
	uint	MAX_MISTAKES;
	uint	wrongGuesses;
};

#endif
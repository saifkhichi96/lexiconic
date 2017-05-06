#include "_GamesUI.hpp"


Hangman::Hangman()
	: MAX_MISTAKES(8), wrongGuesses(0), noOfWords(50),
	isOver(false), isStarted(false), loadedWords(NULL), wordIndex(0)
{
	cout << "Activity 'Hangman' created\n";

	textures.load("h_background", "res/drawable/hangman/background.tga");
	textures.get("h_background").setSize(800, 600);
	textures.get("h_background").setPosition(0, 0);

	textures.load("hanged", "res/drawable/hangman/hanged.tga");
	textures.get("hanged").setSize(500, 500);
	textures.get("hanged").setPosition(300, 0);

	textures.load("post", "res/drawable/hangman/hanging_post.tga");
	textures.get("post").setSize(500, 500);
	textures.get("post").setPosition(300, 0);

	textures.load("win", "res/drawable/hangman/alive.tga");
	textures.get("win").setSize(500, 500);
	textures.get("win").setPosition(300, 0);

	addButton("GH_1", Button("Start", 535, 25, 75, 75, GAME_COLOR));
}


void Hangman::Display()
{
	// Clear display and 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textures.get("h_background").Display();
	textures.get("post").Display();
	
	/*
	If the game has been started but is not yet over
	show various game elements
	*/
	getButton("GH_1").Display();
	if (isStarted)
	{
		print_hint();
		print_player_guess();
		print_player_lives();
		list_used_keys();

		// If the game is over, show the end of game state
		if(isOver) game_end_display();
	}
	
	

	// Display inherited User Interface
	GUI::Display();
}


void Hangman::KeyboardEvents(unsigned char& key, int& x, int& y)
{
	if (key == 32 || key == 45 || (key >= 65 && key <= 122))
	{
		if (key <= 90 || key >= 97 && isStarted && !isOver)
		{
			bool alreadyUsed = false;
			for (auto it = usedKeys.begin(); it != usedKeys.end(); it++)
			{
				if (key == *it) alreadyUsed = true;
			}

			if (!alreadyUsed)
			{
				if (!find_match(key))
				{
					++wrongGuesses;

					if (wrongGuesses >= MAX_MISTAKES)
					{
						isOver = true;
					}
				}

				usedKeys.push_back(key);
			}
		}
	}
}


void Hangman::onClick(UIElement& view)
{
	GamesUI::onClick(view);

	if (view.getID() == "GH_1")
	{
		isOver = false;
		isStarted = false;
		wrongGuesses = 0;
		playersGuess = "";
		usedKeys.clear();
		wordIndex++;

		init_game_states();
		getButton("GH_1").setLabel("Restart");
	}
}


bool Hangman::find_match(const char& key)
{
	int sz = currentWord.getWord().size();
	bool found = false;

	for (int i = 0; i < sz; i++)
	{
		if (toupper(key) == currentWord.getWord().at(i) || tolower(key) == currentWord.getWord().at(i))
		{
			playersGuess[i] = toupper(key);
			found = true;
		}
	}

	if (playersGuess == currentWord.getWord())
		isOver = true;

	return found;
}


void Hangman::init_game_states()
{
	// If all words have been used, delete currently loaded words
	if (wordIndex + 1 > noOfWords)
	{
		delete[] loadedWords;
		wordIndex = 0;
		loadedWords = NULL;
	}

	// If no words loaded, load 50 words
	if (loadedWords == NULL)
		loadedWords = wordList.getSequence(noOfWords);

	// Choose current word
	currentWord = loadedWords[wordIndex++];

	// Format player's guess output
	for (unsigned int i = 0; i < currentWord.getWord().size(); i++)
		playersGuess += "_";

	// Start the game
	isStarted = true;
}


void Hangman::game_end_display()
{
	gout.setColor(GAME_COLOR);
	gout.setPosition(535, 300);
	if (wrongGuesses < 8)
	{
		textures.get("win").Display();
		gout << string(string("YOU WIN!"));
	}
	else
	{
		textures.get("hanged").setAlpha(255.f);
		textures.get("hanged").Display();
		gout << string(string("YOU LOSE!"));
		gout.setColor(Black);
		gout.setLineWidth(100);
		gout.setPosition(60, 365);
		gout << string(string("Correct Word: " + currentWord.getWord()));
	}
}


void Hangman::print_hint()
{
	// Print word definition
	gout.setColor(Black);
	gout.setLineWidth(50);
	gout.setPosition(60, 300);	gout << string(currentWord.getDefinition());
}


void Hangman::print_player_guess()
{
	// Print player's guess
	gout.setColor(Black);
	string str = "";
	for (auto c : playersGuess)
	{
		str += c;
		str += ' ';
	}
	gout.setPosition(60, 395);
	gout << string(str);

	// If wrong guesses made, gradually make the hanged man visible
	textures.get("hanged").setAlpha(wrongGuesses * 31.875f);
	textures.get("hanged").Display();
}


void Hangman::print_player_lives()
{
	// Print player's lives
	gout.setColor(Black);
	gout.setPosition(735, 445);
	gout << string(string("Lifes: " + to_string(MAX_MISTAKES - wrongGuesses)));
}


void Hangman::list_used_keys()
{
	// Print keys that have been used
	gout.setColor(Black);
	int x = 535;
	gout.setLineWidth(20);
	for (auto it = usedKeys.begin(); it != usedKeys.end(); it++)
	{
		string str = "";
		str += *it;
		gout.setPosition(x, 395);
		gout << string(str);
		x += 25;
	}
}
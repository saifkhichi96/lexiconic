#include "_GamesUI.hpp"


JumbleUI::JumbleUI()
	: gameObject(wordList), playerHasGuessed(false), isOver(false),
	activeLetter(0), wordLength(0), correctGuess(true)
{
	addButton("Check", Button("Check",	475, 300, 100, 100, Black, 0.5f));
	addButton("Start", Button("New",	625, 300, 100, 100, GAME_COLOR));

	addButton("-", Button("-", 475, 260, 35, 35, GAME_COLOR));
	addButton("Difficulty", Button("Difficulty: " + to_string(5), 505, 260, 200, 35, GAME_COLOR));
	addButton("+", Button("+", 695, 260, 35, 35, GAME_COLOR));

	textures.load("Win", "res/drawable/jumble_win.png");
	textures.get("Win").setSize(100, 100);
	textures.get("Win").setPosition(300, 300);

	textures.load("Lose", "res/drawable/jumble_lose.png");
	textures.get("Lose").setSize(100, 100);
	textures.get("Lose").setPosition(300, 300);
}


void JumbleUI::onStart()
{
	startGame();
}


void JumbleUI::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GamesUI::Display();

	glColor3f(GAME_COLOR);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(25, 25);
		glVertex2f(775, 25);
		glVertex2f(775, 435);
		glVertex2f(25, 435);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(450, 410);
		glVertex2f(750, 410);
		glVertex2f(750, 250);
		glVertex2f(450, 250);
	}
	glEnd();

	gout.setColor(Black);
	int x = 50;
	for (char c : gameObject.getJumbled()){
		gout.setPosition(x += 25, 280);	gout << string(1, c);
	}

	for (int i = 0; i < wordLength; i++)
		getButton("J_" + to_string(i)).Display();

	gout.setColor(Black);
	gout.setLineWidth(80);
	gout.setPosition(50, 170);
	gout << gameObject.getHint();

	getButton("Check").Display();
	getButton("Start").Display();
	getButton("-").Display();
	getButton("Difficulty").Display();
	getButton("+").Display();

	if (isOver)	textures.get("Win").Display();

	else if (!correctGuess) textures.get("Lose").Display();

	GUI::Display();
}


void JumbleUI::KeyboardEvents(unsigned char& key, int& x, int& y)
{
	if (playerHasGuessed && !isOver && key == ENTER)
	{
		isOver = gameObject.checkWord(playerGuess);

		if (!isOver) correctGuess = false;
	}
	else if (playerHasGuessed && isOver && key == ENTER)
	{
		startGame();
	}
	else if (wordLength > 0 && !isOver)
	{
		if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '-')
		{
			playerGuess[activeLetter] = toupper(key);
			getButton("J_" + to_string(activeLetter)).setLabel(string(1, toupper(key)));
		}
		
		playerHasGuessed = true;
		for (char c : playerGuess)
			if (c == ' ') playerHasGuessed = false;

		if (playerHasGuessed)
		{
			getButton("Check").setColor(GAME_COLOR);
			getButton("Check").setAlpha(1.f);
		}

		if (!correctGuess) correctGuess = true;
	}

}


void JumbleUI::KeyboardSpecialEvents(int& key, int& x, int& y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (activeLetter > 0)
		{
			getButton("J_" + to_string(activeLetter)).setColor(GAME_COLOR);
			activeLetter--;
			getButton("J_" + to_string(activeLetter)).setColor(GreenCopper);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (activeLetter < wordLength - 1)
		{
			getButton("J_" + to_string(activeLetter)).setColor(GAME_COLOR);
			activeLetter++;
			getButton("J_" + to_string(activeLetter)).setColor(GreenCopper);
		}
		break;
	default:
		break;
	}
}


void JumbleUI::onClick(UIElement& view)
{
	GamesUI::onClick(view);

	if (view.getID() == "Check" && playerHasGuessed)
	{
		isOver = gameObject.checkWord(playerGuess);

		if (!isOver) correctGuess = false;
	}
	else if (view.getID() == "Start")
	{
		startGame();
	}
	else if (view.getID() == "-")
	{
		int level = gameObject.getDifficulty() - 1;
		gameObject.setDifficulty(level);
		getButton("Difficulty").setLabel("Difficulty: " + to_string(gameObject.getDifficulty()));
	}
	else if (view.getID() == "+")
	{
		int level = gameObject.getDifficulty() + 1;
		gameObject.setDifficulty(level);
		getButton("Difficulty").setLabel("Difficulty: " + to_string(gameObject.getDifficulty()));
	}
	else for (int i = 0; i < wordLength; i++)
	{
		if (view.getID() == "J_" + to_string(i))
		{
			getButton("J_" + to_string(activeLetter)).setColor(GAME_COLOR);
			activeLetter = i;
			getButton("J_" + to_string(activeLetter)).setColor(GreenCopper);
		}
	}
}


void JumbleUI::startGame()
{
	// Delete old word
	for (int i = 0; i < wordLength; i++)
		Buttons().erase("J_" + to_string(i));

	playerHasGuessed = false;
	isOver = false;
	getButton("Check").setColor(Black);
	getButton("Check").setAlpha(0.5f);
	activeLetter = 0;
	playerGuess.clear();
	gameObject.update();
	wordLength = gameObject.getJumbled().size();

	for (int i = 0; i < wordLength; i++){
		playerGuess += ' ';
		addButton("J_" + to_string(i), Button("", 50 + i * 50, 200, 35, 35, GAME_COLOR));
	}
}
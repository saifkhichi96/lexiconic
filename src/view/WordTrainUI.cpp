#include "_GamesUI.hpp"

WordTrainUI::WordTrainUI()
	: gameObject(wordList), isStarted(false)
{

}


void WordTrainUI::onStart()
{
	// Clear the word
	gameObject.setWord("");
	
	// Set flag indicating start of game
	isStarted = true;

	// Play CPU's move
	gameObject.takeComputersTurn();
}


void WordTrainUI::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GamesUI::Display();

	gout.setColor(Black);
	gout.setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	gout.setPosition(250, 300);
	gout << gameObject.getWord();
	
	gout.setPosition(250, 200);
	gout.setFont(GLUT_BITMAP_HELVETICA_18);

	if (!isStarted)
	{
		int winner = gameObject.getTurn();

		if (wordList.lookUp(gameObject.getWord()) != "Not found")
		{
			if (winner == 2) gout << "Player wins!";
			else if (winner == 1) gout << "CPU wins!";
		}
		else gout << "Game drawn!";
	}
}


void WordTrainUI::KeyboardEvents(unsigned char& key, int&, int&)
{
	if (isStarted)
	{
		isStarted = !gameObject.takePlayersTurn(toupper(key));

		if (!isStarted) return;

		isStarted = !gameObject.takeComputersTurn();
	}
}
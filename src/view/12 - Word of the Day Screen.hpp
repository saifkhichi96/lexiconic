#pragma once
#include "GUI.hpp"

class TodaysWord
{
public:
			TodaysWord();
	void	Display();
	void	IdleGL();
	string	GetWord(){ return word; }
private:
	void	Update(bool);

	Word	word;
	Date	lastUpdate;
};
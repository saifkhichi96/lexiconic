#pragma once
#include "GUI.hpp"

class VocaBank
{
public:
			VocaBank();
	void	Display();
	void	IdleGL();
	Word*	GetWords(){ return words; }
private:
	void	Update(bool);
	
	Word*	words = NULL;
	Date	lastUpdate;
};
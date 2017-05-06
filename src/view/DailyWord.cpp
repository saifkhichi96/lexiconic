#include "12 - Word of the Day Screen.hpp"
#include "../entity/Dictionary.h"
#include <fstream>

using namespace std;

#ifdef MAP_HPP
extern Map			wordList;
#endif

#ifndef MAP_HPP
#ifdef DICT_H
extern Dictionary	wordList;
#endif
#endif
extern Text gout;

//------------------------------------------------------------------------------//
//            class TodaysWord                                                  //
//                  User interface of the word of the day submodule of the      //
//                  dictionary of the system.                                   //
//------------------------------------------------------------------------------//
TodaysWord::TodaysWord()
{
	cout << "Activity 'TodaysWord' created\n";
	
	ifstream update_info("data/wotd_update");
	update_info >> lastUpdate;

	Update(Date() - lastUpdate != 0);
}


void TodaysWord::Display()
{
	gout.setColor(Black);
	gout.setPosition(150, 400);
	gout.setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	gout << string(word.getWord());

	gout.setPosition(100, 300);
	gout.setLineWidth(75);
	gout.setFont(GLUT_BITMAP_HELVETICA_18);
	gout << string(word.getDefinition());
}


void TodaysWord::IdleGL()
{
	Update(Date() - lastUpdate != 0);
}


void TodaysWord::Update(bool update)
{
	ifstream update_info("data/wotd_update");
	ifstream data("data/wotd");

	if (update || !data || !update_info)
	{
		word = wordList.getWord();
		lastUpdate = Date();

		ofstream outfile("data/wotd");
		outfile << word.getWord() << endl;
		outfile << word.getDefinition() << '$' << endl;
		outfile.close();

		outfile.open("data/wotd_update");
		outfile << lastUpdate;
		outfile.close();
	}
	else
	{
		getline(data, word.getWord());
		getline(data, word.getDefinition(), '$');
		update_info >> lastUpdate;
	}

	data.close();
	update_info.close();
}
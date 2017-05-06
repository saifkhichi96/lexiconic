#include "13 - VocaBank Screen.hpp"
#include <fstream>

using namespace std;

extern Dictionary	wordList;
extern Text gout;

//------------------------------------------------------------------------------//
//            class Vocabank                                                    //
//                  User interface of the daily vocabulary list submodule of the//
//                  dictionary of the system.                                   //
//------------------------------------------------------------------------------//
VocaBank::VocaBank()
{
	cout << "Activity 'VocaBank' created\n";

	ifstream update_info("data/vocabank_update");
	update_info >> lastUpdate;
}


void VocaBank::Display()
{
	gout.setColor(Black);
	gout.setFont(GLUT_BITMAP_HELVETICA_12);
	gout.setPosition(150, 400);
	for (int i = 0; i < 25; i++)
	{
		gout << string(words[i].getWord());
		gout.translate('y', -15);
	}

	gout.setPosition(400, 400);
	for (int i = 25; i < 50; i++)
	{
		gout << string(words[i].getWord());
		gout.translate('y', -15);
	}
}


void VocaBank::IdleGL()
{
	Update(Date() - lastUpdate != 0);
}


void VocaBank::Update(bool update)
{
	ifstream update_info("data/vocabank_update");
	ifstream data("data/vocabank");

	if (update || !data || !update_info)
	{
		words = wordList.getSequence(50);
		lastUpdate = Date();

		ofstream outfile("data/vocabank");

		for (int i = 0; i < 50; i++)
		{
			outfile << words[i].getWord() << endl;
			outfile << words[i].getDefinition() << '$' << endl;
		}

		outfile.close();

		outfile.open("data/vocabank_update");
		outfile << lastUpdate;
		outfile.close();
	}
	else
	{
		if (words)
			delete[] words;

		words = new Word[50];

		for (int i = 0; i < 50; i++)
		{
			getline(data, words[i].getWord());
			getline(data, words[i].getDefinition(), '$');
			getline(data, string());
		}

		update_info >> lastUpdate;
	}

	data.close();
	update_info.close();
}
#ifndef WORD_TRAIN_HPP
#define WORD_TRAIN_HPP

#include <iostream>
#include "../entity/Dictionary.h"

using std::string;

class WordTrain
{
private:
	string		word;
	Dictionary&	wordList;

	enum Turn{ User = 1, CPU = 2 } turn;

	void swapTurn()
	{
		turn == CPU ? turn = User : turn = CPU;
	}

	bool checkWord()
	{
		return (word.length() > 3 && wordList.lookUp(word) != "Not found") ? true : false;
	}

public:
	WordTrain(Dictionary& list)
		: wordList(list), word(""), turn(CPU)
	{

	}

	void setWord(const string& str)
	{
		word = str;
	}

	string getWord()
	{
		return word;
	}

	Turn getTurn()
	{
		return turn;
	}

	bool takePlayersTurn(char c)
	{
		if (turn != User)
			return false;

		word.push_back(c);
		swapTurn();
		return checkWord();
	}

	bool takeComputersTurn()
	{
		if (turn != CPU)
			return true;

		swapTurn();
		if (word.length() >= 2)
		{
			auto list = wordList.wordsWithPrefix(word);

			if (list.size() == 0)
				return false;

			string shortestWord = "";
			while (shortestWord.size() <= word.size())
				shortestWord = list.at(rand() % list.size());

			word.push_back((shortestWord.at(word.length())));
		}
		else
		{
			word += ('A' + rand() % 26);
		}

		return checkWord();
	}
};

#endif
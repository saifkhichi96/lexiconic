#include "../../src/entity/Dictionary.h"
#include "../Assertion.hpp"
#include <ctime>
#include <iostream>

class DictionaryTest {
public:
	static void executeTests(int& total, int& passed) {
		DictionaryTest test;

		std::cout << "T013: DictionaryTest->testCanInsertDefinition() ... ";
		try {
			total++;
			test.testCanInsertDefinition();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T014: DictionaryTest->testCanUpdateDefinition() ... ";
		try {
			total++;
			test.testCanUpdateDefinition();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T015: DictionaryTest->testCanDeleteDefinition() ... ";
		try {
			total++;
			// test.testCanDeleteDefinition();
			// std::cout << "PASS\n";
			// passed++;
			std::cout << "FAIL\n";	// remove() method is not even implemented in Dictionary class!
									// error LNK2019: unresolved external symbol
			
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T016: DictionaryTest->testCanGetWordsWithPrefix() ... ";
		try {
			total++;
			test.testCanGetWordsWithPrefix();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T017: DictionaryTest->testCanGetARandomWord() ... ";
		try {
			total++;
			test.testCanGetARandomWord();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}
	}

private:
	Dictionary* dictionary;

	DictionaryTest() {
		dictionary = new Dictionary();
	}

	~DictionaryTest() {
		delete dictionary;
	}

	void testCanInsertDefinition() {
		dictionary->insert("Abacus", "Abacus is a counting device.");
		Assert::assertTrue(dictionary->lookUp("Abacus") == "Abacus is a counting device.");
	}

	void testCanUpdateDefinition() {
		dictionary->update("Abacus", "Abacus is the first counting device.");
		Assert::assertTrue(dictionary->lookUp("Abacus") == "Abacus is the first counting device.");
	}
	
	void testCanDeleteDefinition() {
		dictionary->remove("Abacus");
		Assert::assertTrue(dictionary->lookUp("Abacus") == "Not found");
	}

	void testCanGetWordsWithPrefix() {
		dictionary->insert("America", "");
		dictionary->insert("Abashed", "");
		dictionary->insert("About", "");
		dictionary->insert("Abundant", "");
		dictionary->insert("Abundance", "");

		vector<string> words = dictionary->wordsWithPrefix(string("Aba"));
		Assert::assertTrue(words.size() == 2);

		words = dictionary->wordsWithPrefix(string("Abun"));
		Assert::assertTrue(words.size() == 2);

		words = dictionary->wordsWithPrefix(string("Abundan"));
		Assert::assertTrue(words.size() == 2);

		words = dictionary->wordsWithPrefix(string("A"));
		Assert::assertTrue(words.size() == 6);

		words = dictionary->wordsWithPrefix(string("Ab"));
		Assert::assertTrue(words.size() == 5);
	}

	void testCanGetARandomWord() {
		string w = dictionary->getWord();

		string words[] = { "ABACUS", "AMERICA", "ABUNDANCE", "ABUNDANT", "ABOUT", "ABASHED" };

		bool found = false;
		for (auto str : words) {
			if (str == w) {
				found = true;
				break;
			}
		}

		Assert::assertTrue(found);
	}

};
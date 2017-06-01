#include "../../src/entity/Word.h"
#include "../Assertion.hpp"
#include <ctime>
#include <iostream>

class WordTest {
public:
	static void executeTests(int& total, int& passed) {
		WordTest wordTest;

		std::cout << "T007: WordTest->testCanInstantiateWordWithNoArguments() ... ";
		try {
			total++;
			wordTest.testCanInstantiateWordWithNoArguments();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T008: WordTest->testCanInstantiateWordWithOneArgument() ... ";
		try {
			total++;
			wordTest.testCanInstantiateWordWithOneArgument();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T009: WordTest->testCanInstantiateWordWithTwoArguments() ... ";
		try {
			total++;
			wordTest.testCanInstantiateWordWithTwoArguments();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T010: WordTest->testCanCompareWordsForEquality() ... ";
		try {
			total++;
			wordTest.testCanCompareWordsForEquality();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T011: WordTest->testCanCompareWordsForInequality() ... ";
		try {
			total++;
			wordTest.testCanCompareWordsForInequality();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T012: WordTest->testCanCompareWordsAlphabetically() ... ";
		try {
			total++;
			wordTest.testCanCompareWordsAlphabetically();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}
	}

private:

	/**
	* @TestCase(id: T001)
	* TestWriter:		Muhammad Saifullah Khan
	* TestDescription:	Tests that a Date object, when first created, has the same
	*                   date/time as CURRENT_TIMESTAMP
	* PreCondition:		Instance of Date class must have been created
	* PostCondition:	None
	*/
	void testCanInstantiateWordWithNoArguments() {
		Word w;

		Assert::assertTrue("" == w.getWord());
		Assert::assertTrue("" == w.getDefinition());
	}

	void testCanInstantiateWordWithOneArgument() {
		Word w("One");

		Assert::assertTrue("One" == w.getWord());
		Assert::assertTrue("" == w.getDefinition());
	}

	void testCanInstantiateWordWithTwoArguments() {
		Word w("One", "Two");

		Assert::assertTrue("One" == w.getWord());
		Assert::assertTrue("Two" == w.getDefinition());
	}

	void testCanCompareWordsForEquality() {
		Word w1("Abacus");
		Word w2("Abacus");

		Assert::assertTrue(w1 == w2);
	}

	void testCanCompareWordsForInequality() {
		Word w1("Abacus");
		Word w2("Mark I");

		Assert::assertTrue(w1 != w2);
	}

	void testCanCompareWordsAlphabetically() {
		Word w1("Abacus");
		Word w2("About");

		Assert::assertTrue(w1 < w2);
		Assert::assertTrue(w2 > w1);

		Assert::assertTrue(w1 <= w2);
		Assert::assertTrue(w1 <= w1);

		Assert::assertTrue(w2 >= w1);
		Assert::assertTrue(w2 >= w2);
	}
};
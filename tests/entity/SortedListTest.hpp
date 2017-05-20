#include "../../src/entity/SortedList.h"
#include "../Assertion.hpp"
#include <ctime>
#include <iostream>

class SortedListTest {
public:
	static void executeTests(int& total, int& passed) {
		SortedListTest listTest;

		std::cout << "T003: ListSingleTest->testDefaultOrder() ... ";
		try {
			total++;
			listTest.testDefaultOrder();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T004: ListSingleTest->testAscendingOrder() ... ";
		try {
			total++;
			listTest.testAscendingOrder();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}


		std::cout << "T005: ListSingleTest->testDescendingOrder() ... ";
		try {
			total++;
			listTest.testDescendingOrder();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T006: ListSingleTest->testSetOrder() ... ";
		try {
			total++;
			listTest.testSetOrder();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}
	}

private:
	/**
	* @TestCase(id: T003)
	* TestWriter:		Muhammad Saifullah Khan
	* TestDescription:	Tests that list sorted in ascending order by default.
	* PreCondition:		None
	* PostCondition:	None
	*/
	void testDefaultOrder() {
		SortedList<int> list;

		list.insert(3);
		list.insert(1);
		list.insert(7);

		// Assert correctness of Date object
		Assert::assertTrue(list[0] == 1);
		Assert::assertTrue(list[1] == 3);
		Assert::assertTrue(list[2] == 7);
	}

	/**
	* @Test(id: T002)
	* TestWriter:		Muhammad Saifullah Khan
	* TestDescription:	Tests boundaries of date/time in Date object. i.e. e.g. month
	*                   can only have values 1-12.
	* PreCondition:		@Test(id: 001) should already have been executed
	* PostCondition:	None
	*/
	void testAscendingOrder() {
		SortedList<int> list;

		list.insert(3);
		list.insert(1);
		list.insert(7);

		// Assert correctness of Date object
		Assert::assertTrue(list[0] == 1);
		Assert::assertTrue(list[1] == 3);
		Assert::assertTrue(list[2] == 7);
	}

	/**
	* @Test(id: T002)
	* TestWriter:		Muhammad Saifullah Khan
	* TestDescription:	Tests boundaries of date/time in Date object. i.e. e.g. month
	*                   can only have values 1-12.
	* PreCondition:		@Test(id: 001) should already have been executed
	* PostCondition:	None
	*/
	void testDescendingOrder() {
		SortedList<int> list;
		list.setAscending(false);

		list.insert(3);
		list.insert(1);
		list.insert(7);


		// Assert correctness of Date object
		Assert::assertTrue(list[0] == 7);
		Assert::assertTrue(list[1] == 3);
		Assert::assertTrue(list[2] == 1);
	}

	void testSetOrder() {
		SortedList<int> list;

		list.insert(3);
		list.insert(1);
		list.insert(7);

		list.setAscending(false);
		// Assert correctness of Date object
		Assert::assertTrue(list[0] == 7);
		Assert::assertTrue(list[1] == 3);
		Assert::assertTrue(list[2] == 1);
	}
};
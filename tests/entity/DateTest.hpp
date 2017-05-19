#include "../../src/entity/Date.hpp"
#include "../Assertion.hpp"
#include <ctime>
#include <iostream>

class DateTest {
public:
	static void executeTests(int& total, int& passed) {
		DateTest dateTest;

		std::cout << "T001: DateTest->testCurrentTimestamp() ... ";
		try {
			total++;
			dateTest.testCurrentTimestamp();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}

		std::cout << "T002: DateTest->testBoundayValues() ... ";
		try {
			total++;
			dateTest.testBoundayValues();
			std::cout << "PASS\n";
			passed++;
		}
		catch (...) {
			std::cout << "FAIL\n";
		}
	}

private:
	Date *date;

	DateTest() {
		date = new Date();
	}

	~DateTest() {
		delete date;
	}

	/**
	* @TestCase(id: T001)
	* TestWriter:		Muhammad Saifullah Khan
	* TestDescription:	Tests that a Date object, when first created, has the same
	*                   date/time as CURRENT_TIMESTAMP
	* PreCondition:		Instance of Date class must have been created
	* PostCondition:	None
	*/
	void testCurrentTimestamp() {
		// Get current timestamp
		time_t rawtime;
		tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		// Assert correctness of Date object
		Assert::assertTrue(date->day == timeinfo->tm_mday);
		Assert::assertTrue(date->month == timeinfo->tm_mon);
		Assert::assertTrue(date->year == 1900 + timeinfo->tm_year);

		Assert::assertTrue(date->minutes == timeinfo->tm_min);
		Assert::assertTrue(date->hours == timeinfo->tm_hour);
	}

	/**
	* @Test(id: T002)
	* TestWriter:		Muhammad Saifullah Khan
	* TestDescription:	Tests boundaries of date/time in Date object. i.e. e.g. month
	*                   can only have values 1-12.
	* PreCondition:		@Test(id: 001) should already have been executed
	* PostCondition:	None
	*/
	void testBoundayValues() {
		// Assert correctness of Date object
		date->day = 0;
		date->month = 0;
		date->hours = -1;
		date->minutes = -1;
		date->minutes = -1;

		Assert::assertTrue(date->day != 0);
		Assert::assertTrue(date->month != 0);

		Assert::assertTrue(date->minutes == 0);
		Assert::assertTrue(date->hours == 0);
	}
};
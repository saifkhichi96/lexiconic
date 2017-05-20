#include "entity\DateTest.hpp"
#include "entity\SortedListTest.hpp"
#include <iostream>

class TestSuite {

public:
	static void execute() {
		int totalTests = 0;
		int passedTests = 0;
		DateTest::executeTests(totalTests, passedTests);
		SortedListTest::executeTests(totalTests, passedTests);

		std::cout << passedTests << " test(s) out of " << totalTests << " passed.\n";
	}
};
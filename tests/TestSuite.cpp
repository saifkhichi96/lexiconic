#include "entity\DateTest.hpp"
#include <iostream>

// Comment the following line to start App instead of TestSuite
#define TEST_RUN
#ifdef TEST_RUN
int main() {
	int totalTests = 0;
	int passedTests = 0;
	DateTest::executeTests(totalTests, passedTests);

	std::cout << passedTests << " test(s) out of " << totalTests << " passed.\n";
}
#endif
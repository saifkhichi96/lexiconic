#include <exception>

class AssertionError : public std::exception {

};

class Assert {
public:
	static void assertTrue(bool condition) {
		if (!condition) {
			throw new AssertionError();
		}
	}
	static void assertFalse(bool condition){
		if (condition) {
			throw new AssertionError();
		}
	}
};
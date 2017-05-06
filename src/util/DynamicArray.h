#pragma once

#include <iostream>
#include <string>

using namespace std;
typedef unsigned int uint;

template <typename T>
class DynamicArray
{
private:
	T*	array;								// Dynamic array
	uint noOfElements;						// Number of elements in the array
	uint maxElements;						// Capacity of the array

	bool	isFull();						// Indicates if there is space left in the array or not
	void	doubleCapacity();				// Doubles the capacity of the array

public:
			DynamicArray(uint = 0);			// Default public constructor
			~DynamicArray();				// Destructor

	void	insert(T);						// Inserts new data in specified order (ascending by default)
	void	append(T);						// Inserts new data at end of the array

	void	clear();						// Deletes all nodes
	void	remove(unsigned int);			// Removes node from specified position

	uint	size();							// Returns number of elements in the array
	uint	capacity();						// Returns capacity of the array

	T*		search(const T&);				// Searches for an element using binary search
	T&		operator[](uint);				// Returns reference to the element at given index

	void	sort();							// Sorts the list in specified order (ascending by default)
	void	setOrder(bool);					// Sets sort order of the list (true->ascending, false->descending)
	bool	getOrder();						// Indicates if sort order of the list (true->ascending, false->descending)
};

#include "DynamicArray.inl"
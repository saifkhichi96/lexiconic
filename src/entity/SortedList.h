#pragma once

#include <iostream>
#include <string>

using namespace std;
typedef unsigned int uint;

/*
Singly Linked List
Each node is linked to only one more node. Can only navigate forward, from head to tail
*/
template <typename T>
class SortedList
{
protected:
	struct Node
	{
		T		data;
		Node*	next;

		Node(T i) 
		: next(NULL), data(i)
		{ }
	};

	int		count;							// Number of nodes in the list
	Node*	head;							// First node of the list
	Node*	tail;							// Last node of the list

	bool	sortedAscending;				// Flag to indicate sorting order
	void	insertAscending(const T&);		// Inserts data in ascending order
	void	insertDescending(const T&);		// Inserts data in descending order

public:
			SortedList();					// Default public constructor
			~SortedList();					// Destructor

	void	insert(T);						// Inserts new data in specified order (ascending by default)
	
	void	remove(unsigned int);			// Removes node from specified position
	void	clear();						// Deletes all nodes

	uint	size();							// Returns number of elements in the array
	
	T*		search(const T&);				// Searches for an element using binary search
	T&		operator[](uint);				// Returns reference to the element at given index

	void	sort();							// Sorts the list in specified order (ascending by default)
	void	setAscending(bool);				// Sets sort order of the list (true->ascending, false->descending)
	bool	isAscending();					// Indicates if sort order of the list (true->ascending, false->descending)
};

#include "SortedList.inl"
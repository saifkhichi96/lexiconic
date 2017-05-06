//--------------------------------------------------------------------------------------------------//
//		Sudoku.cpp																					//
//																									//
//			 Author: Muhammad Saifullah Khan														//
//		Description: C++ program to solve a Sudoku board. Uses brute force algorithm with			//
//					 backtracking to solve any given problem. Sudoku boards can be generated		//
//					 by computer or input by the user.												//
//			   Date: Sunday, Novermber 9, 2015.														//
//																									//
//--------------------------------------------------------------------------------------------------//

#include "Sudoku.h"
#include <ctime>

Sudoku::Sudoku()
{
	/*
	Default public constructor. Initializes each cell of the board, storing row
	and column number of each cell. It is required that every cell know its own
	row and column number for my implementation of backtracking algorithm to
	solve the puzzle.
	*/

	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			Board[i][j].row = i;
			Board[i][j].col = j;
		}
}

bool Sudoku::solve()
{
	/*
	Attempts to solve the given puzzle. Return true on success, false otherwise.
	Solve() method uses a brute force algorithm which solves the provided puzzle
	by filling a cell with first possible value and moving to next unfilled cell,
	and if the puzzle reaches a dead end, backtracking to the cell which was last
	filled and filling it with another possible value. This process is repeated
	until either the puzzle is completely solved or the program tries to backtrack
	from the first unfilled cell, which indicates that the puzzle could not be
	solved.

	REFERENCE LINKS:
	https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#Backtracking
	https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#Brute-force_algorithm
	*/


	while (!isSolved())												// Repeat till filled completely:
	{
		for (int row = 0; row < 9; row++)							// For all the rows and columns in
			for (int col = 0; col < 9; col++)						// in the 9x9 grid, visit each
				if (!Board[row][col].isFilled)						// unfilled cell.
				{
					int value = Board[row][col].value;				// Fill the cell with first possible
					for (; value <= 9; value++)						// value, ranging from 1-9. If this
					{												// cell has never been visited before
						if (!checkConflicts(row, col, value))		// it will have a zero. Starting from
						{											// 1, we look for value that can fill
							Board[row][col].fill(value);			// up this cell without conflicts.
							visited.push(Board[row][col]);			// Keeping track of all the previously
							break;									// filled cells (to make returning to
						}											// a previous cell possible), we move
																	// to next cell if this cell has been
						if (value == 9)								// successfully filled. If no number
						{											// from 1-9 fits current cell, we
							if (visited.empty())					// backtrack to the cell which was
								return false;						// filled last and refill it with
																	// another value.
							auto c = visited.top();
							Board[row][col].unfill();				// When a dead end is encountered (i.e.
							Board[c.row][c.col].isFilled = false;	// none of the numbers 1-9 fit), we un-
							row = c.row;							// fill the current cell, and mark the
							col = c.col;							// cell that was last filled as 'not f-
							visited.pop();							// illed' without changing its value.
																	// This makes sure that whent it is re-
							col -= 2;								// filled, it will be filled with a di-
							if (col < 0)							// fferent value.
							{
								--row;								// Next we change indices of current r-
								col = 8;							// ow and column to go to the position
							}										// of the cell that was filled last.
							break;
						}											// If, when a dead end is encountered,
																	// no cell has already been filled, th-
					}												// is means that the puzzle is not sol-
				}													// vable. Solve() method returns false
	}																// in that case.

	return true;													// On success, true is returned.
}

void Sudoku::swapGrids(int i, int j)
{
	if (i == j && ++j > 2) j = 0;

	for (int x = 0; x < 3; x++)
		swapRows(3 * i + x, 3 * j + x);
}

void Sudoku::swapRows(int i, int j)
{
	for (int x = 0; x < 9; x++)
		std::swap(Board[i][x].value, Board[j][x].value);
}

void Sudoku::swapColumns(int i, int j)
{
	for (int x = 0; x < 9; x++)
		std::swap(Board[x][i].value, Board[x][j].value);
}

void Sudoku::generate()
{
	/*
	Creates a new Sudoku board.
	Generate() method is used to create a new computer-generated Sudoku puzzle.
	It successfully generates a solvable puzzle in constant time. O(1)
	*/

	// Fill the board with valid values
	for (int i = 0; i < 9; i++)
	{
		int num = 1 + abs(9 - 3 * i) + (i / 3);
		for (int j = 0; j < 9; j++)
		{
			if (num > 9) num -= 9;
			Board[i][j].fill(num++);
		}
	}

	// Randomly swap entire rows of 3x3 blocks twice
	for (int i = 0; i < 2; i++)
	{
		int first = rand() % 3;
		int second = rand() % 3;
		swapGrids(first, second);
	}

	// Randomly swap complete rows 5 times
	for (int i = 0; i < 3; i++)
	{
		int first = 3 * i + rand() % 3;
		int second = 3 * i + rand() % 3;
		swapRows(first, second);
	}

	// Randomly swap complete cloumns 5 times
	for (int i = 0; i < 3; i++)
	{
		int first = 3 * i + rand() % 3;
		int second = 3 * i + rand() % 3;
		swapColumns(first, second);
	}

	
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++){
			Board[i][j].preFilled = true;
			if (rand() % 4 > 0) Board[i][j].unfill();
		}
}

bool Sudoku::isSolved()
{
	/*
	This method is used to ascertain if the Sudoku board has been solved or not.
	bool isSolved() returns true if the Sudoku board is solved, false otherwise.
	*/

	for (int i = 0; i < 9; i++)							// Visit each cell one by one to check if it is
		for (int j = 0; j < 9; j++)						// filled with a valid value. If any one cell
			if (Board[i][j].isFilled == false)			// is encountered which is not yet filled, stop
				return false;							// looking further and return false

	return true;										// If every cell is filled, return true
}

bool Sudoku::checkConflicts(const int row, const int col, const int num)
{
	/*
	bool CheckConflicts(row, column, number) returns false if number can be placed
	at intersection of given row and column without any conflicts. If it conflicts
	with any of the existing value, true is returned
	*/

	if (col >= 9 || col < 0)
		throw std::out_of_range("Sudoku::CheckConflicts - No such column exists. (Column range 0-8 inclusive).");

	if (row >= 9 || row < 0)
		throw std::out_of_range("Sudoku::CheckConflicts - No such row exists. (Row range 0-8 inclusive).");

	// If no conflicts exists in row, column and subgrid, return false
	if (!checkRowConflicts(row, num) && !checkColumnConflicts(col, num) && !checkGridConflicts(row, col, num))
		return false;

	// Else return true
	else return true;
}

bool Sudoku::checkColumnConflicts(const int& col, const int& num)
{
	/*
	bool ColumnConflicts(column, number) returns true if number already exists
	in the given column. If not, false is returned
	*/

	for (int i = 0; i < 9; i++)
	{
		if (Board[i][col].value == num)
			return true;
	}

	return false;
}

bool Sudoku::checkRowConflicts(const int& row, const int& num)
{
	/*
	bool RowConflicts(row, number) returns true if number already exists in the
	given row. If not, false is returned.
	*/

	for (int i = 0; i < 9; i++)
	{
		if (Board[row][i].value == num)
			return true;
	}

	return false;
}

bool Sudoku::checkGridConflicts(const int& row, const int& col, const int& num)
{
	/*
	bool GridConflicts(column, number, number) returns true if the number already
	exists in the 3x3 grid containing the cell at intersection of given row and
	column. If not, false is returned.
	*/

	// Figure out which 3x3 sub-grid of the Sudoku board contains the cell at intersection
	// of given row and column. Then the elements of corresponding sub-grid are matched
	// against the given number to see if they conflict

	if (row >= 0 && col >= 0 && row < 3 && col < 3)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 3 && col >= 0 && row < 6 && col < 3)
	{
		for (int i = 3; i < 6; i++)
			for (int j = 0; j < 3; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 6 && col >= 0 && row < 9 && col < 3)
	{
		for (int i = 6; i < 9; i++)
			for (int j = 0; j < 3; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 0 && col >= 3 && row < 3 && col < 6)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 3; j < 6; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 3 && col >= 3 && row < 6 && col < 6)
	{
		for (int i = 3; i < 6; i++)
			for (int j = 3; j < 6; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 6 && col >= 3 && row < 9 && col < 6)
	{
		for (int i = 6; i < 9; i++)
			for (int j = 3; j < 6; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 0 && col >= 6 && row < 3 && col < 9)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 6; j < 9; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 3 && col >= 6 && row < 6 && col < 9)
	{
		for (int i = 3; i < 6; i++)
			for (int j = 6; j < 9; j++)
				if (Board[i][j].value == num)
					return true;
	}

	else if (row >= 6 && col >= 6 && row < 9 && col < 9)
	{
		for (int i = 6; i < 9; i++)
			for (int j = 6; j < 9; j++)
				if (Board[i][j].value == num)
					return true;
	}

	return false;
}

bool Sudoku::fillCell(int row, int col, char value)
{
	// If value does not conflict, fill in
	if (!checkConflicts(row, col, value))
	{
		Board[row][col].fill(value);
		return true;
	}

	return false;
}

void Sudoku::reset()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			Board[i][j].unfill();
}

void Sudoku::Cell::fill(int val, bool prefilled)
{
	value = val;
	preFilled = prefilled;
	isFilled = true;
}

void Sudoku::Cell::unfill()
{
	value = 0;
	preFilled = false;
	isFilled = false;
}
//--------------------------------------------------------------------------------------------------//
//		Sudoku.h																					//
//																									//
//			 Author: Muhammad Saifullah Khan														//
//		Description: Definition of the Sudoku class. Sudoku is a popular puzzle game.				//
//			   Date: Sunday, Novermber 9, 2015.														//
//																									//
//																									//
//				SUDOKU RULES:																		//
//				A Sudoku board is a 9x9 grid (having 9 rows and 9 columns). The board				//
//				is further divided into 9 3x3 sub-grids. Following constrains must be				//
//				met when solving a Sudoku board:													//
//					1 - Every row must contain numbers 1 to 9, each only once						//
//					2 - Every colums must contain numbers 1 to 9, each only once					//
//					3 - Every 3x3 sub-grid must contain numbers 1 to 9, each only once				//
//																									//
//				The following methods check if the three constraints defined above are				//
//				being violated (or not) when placing a number in a cell of the board.	 			//
//				The three methods checkRowConflicts(), checkColumnConflicts() and checkGridConflicts()				//
//				correspond to each of the three rules stated above. CheckConflicts()				//
//				combines all three checks in one place. It checks for all three rules				//
//				by calling the first three functions.												//
//																									//
//--------------------------------------------------------------------------------------------------//

#ifndef SUDOKU_H
#define SUDOKU_H

#include <stack>
using std::stack;


/*
Sucoku class handles all the operations related to generating a valid Sudoku puzzle and
solving a given puzzle.
*/
class Sudoku
{
	// Represents one cell of the Sudoku board
	struct Cell
	{
		// Default public constructor, used for initiliazations
		Cell() : isFilled(false), preFilled(false), value(0), row(0), col(0)	{}

		bool	preFilled;				// Was this cell filled in the original puzzle?
		bool	isFilled;				// Is this cell filled with a valid number?
		int		value;					// What is the number conatined in this cell?
		int		row;					// In which row of the Sudoku board is this cell?
		int		col;					// In which column of the Sudoku board is this cell?

		void	fill(int, bool = false);// Fills a cell with given value
		void	unfill();				// Clears a cell
	};

public:
			Sudoku();										// Default public constructor
	
	bool	solve();										// Tries to solves the given puzzle
	void	generate();										// Generates a valid puzzle
	void	reset();										// Clears the board

	bool	checkConflicts(const int, const int, const int);// Enforces Sudoku rules
	bool	fillCell(int, int, char);						// Tries to fill a cell with given value
	
	Cell	Board[9][9];									// A Suduko board has 9x9 cells (i.e. 9 rows, 9 columns)

private:
	bool	isSolved();										// Checks if the puzzle has been solved or not

	bool	checkColumnConflicts(const int&, const int&);	// Enforces Sudoku's columns rule
	bool	checkRowConflicts(const int&, const int&);		// Enforces Sudoku's rows rule
	bool	checkGridConflicts(const int&, const int&, const int&);// Enforces Sudoku's grids rule
	
	void	swapGrids(int, int);							// Exchanges two rows of 3x3 grids
	void	swapRows(int, int);								// Exchanges two rows in same row of 3x3 grids
	void	swapColumns(int, const int);					// Exchanges two columns in same column of 3x3 grids

	/*
	Stack of already visited cells with most recently visited cell on top.
	Needed for backtracing to previous cells if a dead end is encountered
	when solving the puzzle.
	*/
	stack<Cell> visited;
};

#endif
#include "_GamesUI.hpp"


/*
Default constructor, creates a Sudoku board and other UI elements.
*/
SudokuUI::SudokuUI()
	: isStarted(false), sRow(-1), sCol(-1)
{
	CreateBoard();

	addButton("GS_1", Button("Create",		670,  40, 80, 80, GAME_COLOR));
	addButton("GS_2", Button("Generate",	 50, 140, 80, 80, GAME_COLOR));
	addButton("GS_3", Button("Solve",		 50,  40, 80, 80, GAME_COLOR));
	addButton("GS_4", Button("Reset",		670, 140, 80, 80, GAME_COLOR));
}

/*
Overrides parent class method Activity::Display() and is called
polymorphically to draw Sudoku board on the screen.
*/
void SudokuUI::Display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear previous frame
	textures.get("Games").Display();                       // Display interface

	// Draw the board (each of the 9x9 cells is a Button)
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			getButton(string("GS_" + to_string(row) + "x" + to_string(col))).Display();

	// When a game is being played
	if (isStarted)
	{
        // Disable 'create' and 'generate' buttons
		getButton("GS_1").setColor(Black);
		getButton("GS_1").setAlpha(0.5f);

		getButton("GS_2").setColor(Black);
		getButton("GS_2").setAlpha(0.5f);

		// Enable 'solve' and 'reset' buttons
		getButton("GS_3").setColor(GAME_COLOR);
		getButton("GS_3").setAlpha(1.f);
		
		getButton("GS_4").setColor(GAME_COLOR);
		getButton("GS_4").setAlpha(1.f);
	}
    // When game is not being played
	else
	{
		// Disable 'solve' and 'reset' buttons
		getButton("GS_3").setColor(Black);
		getButton("GS_3").setAlpha(0.5f);

		getButton("GS_4").setColor(Black);
		getButton("GS_4").setAlpha(0.5f);

		// Enable 'create' and 'generate' buttons
		getButton("GS_1").setColor(GAME_COLOR);
		getButton("GS_1").setAlpha(1.f);

		getButton("GS_2").setColor(GAME_COLOR);
		getButton("GS_2").setAlpha(1.f);
	}
    
    // Draw action buttons
	for (int i = 1; i < 5; i++)
	{
		string id = "GS_" + to_string(i);
		getButton(id).Display();
	}

    // Display shared user interface
	GUI::Display();
}

/*
Overrides a parent class method to handle keyboard-generated events.
*/
void SudokuUI::KeyboardEvents(unsigned char& key, int& x, int& y)
{
    // When the sidebar is hidden, game is being played, and some
    // cell on the Sudoku board is selected
	if (!showSidebar && isStarted && !(sRow == -1 && sCol == -1))
	{
		string id = "GS_" + to_string(sRow) + "x" + to_string(sCol);      // Get id of the selected cell
	
		if (key - '0' > 0 && key - '0' <= 9)                              // If a numeric key is pressed
		{
			if (_Sudoku.fillCell(sRow, sCol, key - '0'))                     // try to fill the selected cell that number and
				getButton(id).setLabel(to_string(key - '0'));                // update the cell's label if number is filled successfully
		}
		else if (key == 8)                                                // If backspace key is pressed
		{
			_Sudoku.Board[sRow][sCol].unfill();                              // unfill the selected cell
			getButton(id).setLabel(" ");                                     // and remove its label
		}

		getButton(id).setColor(GAME_COLOR);                               // Deselect the cell which was currently
		sCol = sRow = -1;                                                 // selected.
	}

    // Call parent class method to handle shared keyboard events
	GamesUI::KeyboardEvents(key, x, y);
}

/*
Selects a cell. A selected cell (currently active cell) is represented by green color.
: parameters: int x, int y (x and y coordinates of the cell in the 9x9 2D array) 
*/
void SudokuUI::SelectCell(int x, int y)
{
	// Check for an out of bounds index
	// x and y can only be 0-8 inclusive
	if (!((x >= 0 && x < 9) && (y >= 0 && y < 9)))
	{
		cout << x << "," << y << endl;
		throw out_of_range("SudokuUI::SelectCell() - Index out of bounds\n");
	}
    
	// Deselect the previously selected cell (if any)
	DeselectCell(sRow, sCol);

	// Select new cell
	sRow = x;
	sCol = y;

	// Update color
	string id = "GS_" + to_string(x) + "x" + to_string(y);
	getButton(id).setColor(Green_Clr);
}

/*
Deselects a cell. An inactive cell has red color.
: parameters: int x, int y (x and y coordinates of the cell in the 9x9 2D array)
*/
void SudokuUI::DeselectCell(int x, int y)
{
	if (x != -1 && y != -1)											// If the cell is selected
	{
		// Check for an out of bounds index
		// x and y can only be 0-8 inclusive
		if (!((x >= 0 && x < 9) && (y >= 0 && y < 9)))
			throw out_of_range("SudokuUI::DeselectCell() - Index out of bounds\n");

		string lSelect = "GS_" + to_string(x) + "x" + to_string(y);		// Restore color to default
		getButton(lSelect).setColor(GAME_COLOR);

		sRow = -1;														// Deselect cell
		sCol = -1;
	}
}

/*
Overrides base class method which is called whenever a mouse button is
clicked. Handles user's mouse input.
*/
void SudokuUI::onClick(UIElement& view)
{
	// Call base class method
	// Needed to allow base class onClick() behaviour on this Activity
	GamesUI::onClick(view);

	if (!isStarted && view.getID() == "GS_1")			// If game is not started and 'create' is pressed
	{
		DeselectCell(sRow, sCol);							// Deselect any selected cell
		//	_Sudoku.Create(puzzle);							// Create a new puzzle
	}
	else if (!isStarted && view.getID() == "GS_2")		// If game is not started and 'generate' is pressed
	{
		DeselectCell(sRow, sCol);							// Deselect any selected cell
		_Sudoku.generate();									// Generate a new puzzle
		UpdateLabels();										// Update labels on the Sudoku board
		isStarted = true;									// Set flag to indicate start of game
	}
	else if (isStarted && view.getID() == "GS_3")		// If game is started and 'solve' is pressed
	{
		DeselectCell(sRow, sCol);							// Deselect any selected cell
		if (_Sudoku.solve())									// Try to solve the puzzle, and on success
			UpdateLabels();										// update labels on the Sudoku board
	}
	else if (isStarted && view.getID() == "GS_4")		// If game is started and 'reset' is pressed
	{
		DeselectCell(sRow, sCol);							// Deselect any selected cell
		_Sudoku.reset();									// Reset puzzle
		UpdateLabels();										// Update labels in the Sudoku board
		isStarted = false;									// Set flag to indicate end of game
	}
	else
	{
		for (int row = 0; row < 9; row++){					// From 9x9 cells on the Sudoku board
			for (int col = 0; col < 9; col++)
			{
				string id = "GS_" + to_string(row) + "x" + to_string(col);

				if (!_Sudoku.Board[row][col].preFilled &&	// if any Button representing a cell that was not filled in
					view.getID() == id)						// the original puzzle (preFilled) is pressed
				{
					return SelectCell(row, col);				// select that cell
				}
			}
		}
	}
}


/*
Overrides parent class method Activity::onStop() and is (polymorphically)
called every time this Activity is stopped. i.e. Every time you leave
the Activity and go to some other Activity. It resets game states. 
*/
void SudokuUI::onStop()
{
	DeselectCell(sRow, sCol);
	_Sudoku.reset();
	UpdateLabels();
	isStarted = false;
}


/*
Creates 9x9 Buttons to represent the Sudoku board and displays
the puzzle stored in the 2D array on this board.
*/
void SudokuUI::CreateBoard()
{
	// Initial (x, y) coordinates on screen and length of a Cell
	// (represented as a Button)
	int x = 190;
    int y = 400;
    int length = 40;
    
	// Create 9x9 Buttons representing the Cells on the Sudoku board
	// Arrange the cells in a grid-like form to represent the 2D array-shaped board
	for (int i = 0; i < 9;)
	{
		for (int j = 0; j < 9;)
		{
			string id = "GS_" + to_string(i) + "x" + to_string(j);

			int value = _Sudoku.Board[i][j].value;
			string label = " ";
			if (value != 0) label = to_string(value);
			addButton(id, Button(label, x, y, length, length, GAME_COLOR));

			++j % 3 == 0 ?
				x += 55 :
				x += 45;
		}
		x = 190;
		++i % 3 == 0 ?
			y -= 55 :
			y -= 45;
	}
}

/*
Updates the labels on the Buttons representing the Sudoku board
*/
void SudokuUI::UpdateLabels()
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
		{
			string id = "GS_" + to_string(row) + "x" + to_string(col);

			int value = _Sudoku.Board[row][col].value;
			string label = " ";
			if (value != 0) label = to_string(value);
			getButton(id).setLabel(label);

			if (_Sudoku.Board[row][col].preFilled)
				getButton(id).setAlpha(0.75f);
			else
				getButton(id).setAlpha(1.f);
		}
}
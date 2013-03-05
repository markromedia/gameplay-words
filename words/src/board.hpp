#ifndef __BOARD__hpp
#define __BOARD__hpp

#include <iostream>

#include "gameplay.h"
#include "letter_provider.hpp"

class Tile;
class BoardColumn;

class BoardCell {
public:
	BoardColumn* parent_column;
	Tile* tile;
	std::string letter;
	int x;
	int y;
};

class BoardColumn {
private:
	/// runs the adjustment algorithm recursively until 
	/// count is 0
	/// @param	count	the recursive counter
	void adjust(int count);
public:
	/// @summary	The cells of this grid.
	BoardCell* cells[4];

	/// Adjusts this object.
	void AdjustTiles();
};

class Board {
private:
	/// @summary	The instance.
	static Board* instance;

	/// @summary	The columns.
	BoardColumn* columns[4];

	/// @summary	The start time.
	static long start_time;
public:

	/// Removes the given tile from its cell
	/// @param [in,out]	tile	If non-null, the Tile* to remove.
	static void Remove(Tile* tile);

	/// Adjust the tiles to fill in spaces 
	static void AdjustColumns();

	/// @summary	The columns.
	static BoardColumn** Columns();

	/// Called to inform the board that it should do whatever it
	/// needs to to begin preparing the letters
	static void PrepareLetters();

	/// Called after PrepareLetters() is run. This will assign 
	/// a letter to each of the grid cells of this object
	static void AssignLetters();

	/// Initializes all the letters of the board to new characters
	static void CreateNewBoard();

	/// Initialises this object.
	/// @param [in,out]	letter_model	If non-null, the letter model.
	static void Init(gameplay::Node* letter_model);
};

#endif  // __BOARD__hpp
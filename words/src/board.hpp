#ifndef __BOARD__hpp
#define __BOARD__hpp

#include <iostream>
#include <queue>
#include <algorithm>
#include <assert.h>

#include "gameplay.h"
#include "letter_provider.hpp"


class Tile;
class BoardColumn;
class Board;

/// utility macro for cells of the board
/// @param	id	The identifier.
#define BOARD(row, col) (Board::Columns())[row][col]

class PrecalculatedBoard {
public:
	int word_count;
	int board[16][2];
};

class BoardCell {
friend class Board;
friend class BoardColumn;
private:
	//the location of the cell within the board
	int col_index;
	int row_index;

	Tile* tile;
public:
	BoardColumn* parent_column;
	int x;
	int y;
	Dice* die;

	/// Assign tile to this cell
	/// @param [in,out]	tile	If non-null, the tile.
	void AssignTile(Tile* tile, bool assignPosition = false);

	/// Query if this object is empty.
	/// @return	true if empty, false if not.
	bool IsEmpty();
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

	/// Array indexer operator.
	/// @param	parameter1	The first parameter.
	/// @return	The indexed value.
	BoardCell* &operator[] (int index);
};

class Board {
private:
	/// @summary	The instance.
	static Board* instance;

	/// @summary	The columns.
	BoardColumn* columns[4];

	/// @summary	The start time.
	static long start_time;

	/// @summary	The precalculated boards.
	std::queue<PrecalculatedBoard*> precalculated_boards;

	/// Builds the precomputer boards queue.
	void buildPrecomputerBoardsQueue();
public:
	/// Gets the static instance
	/// @return	null if it fails, else.
	static Board* get();

	/// Removes the given tile from its cell
	/// @param [in,out]	tile	If non-null, the Tile* to remove.
	static void Remove(Tile* tile);

	/// Adjust the tiles to fill in spaces 
	static void AdjustColumns();

	/// @summary	The columns.
	static BoardColumn** Columns();

	/// Called to inform the board that it should do whatever it
	/// needs to to begin preparing the letters
	static void PrepareBoard();

	/// Called after PrepareLetters() is run. This will assign 
	/// a letter to each of the grid cells of this object
	static void AssignBoard();

	/// Initializes all the letters of the board to new characters
	static void CreateNewBoardFromPrecalculatedBoards();

	/// Creates a new random board
	static void CreateRandomBoard();

	/// Initialises this object.
	/// @param [in,out]	letter_model	If non-null, the letter model.
	static void Init(gameplay::Node* letter_model);

	/// Array indexer operator.
	/// @param	parameter1	The first parameter.
	/// @return	The indexed value.
	BoardColumn* &operator[] (int index);

	/// Print the board for debugging.
	static void PrintBoard();
};

#endif  // __BOARD__hpp
#ifndef __WORD_CHECKER__hpp
#define __WORD_CHECKER__hpp

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "gameplay.h"
#include "../perf-solver/boggle_solver.h"

#include "board.hpp"
#include "dice_manager.hpp"

class BoardValue {
public:
	//associated with values that are fixed
	int die_id;
	int die_side_index;
	char value;
	bool is_fixed;
	BoardCell* cell;

	/// Resets this object.
	inline void Reset() {
		die_id = 0;
		die_side_index = 0;
		is_fixed = false;
		cell = NULL;
	}
};

class UniqueSidedDie {
public:
	Dice* die;
	char unique_values[6];
	int unique_count;
	int index;

	inline void Reset() {
		unique_count = 0;
		die = NULL;
		index = 0;
		for (int i = 0; i < 6; i++) unique_values[i] = 0;
	}

	inline bool contains(char c) {
		for (int i = 0; i < unique_count; i++) {
			if (unique_values[i] == c) {
				return true;
			}
		}
		return false;
	}

	inline void add(char c) {
		if (!contains(c)) {
			unique_values[unique_count++] = c;
		}
	}

};

class ValueProvider {
private:
	/// @summary	The values this object can set
	BoardValue* values[16];

	/// @summary	The current dice.
	Dice* dice[16];

	/// @summary	Number of values.
	int num_values;

	/// @summary	The unique sides to each of our dice
	UniqueSidedDie* unique_sided_dice[16];

	/// @summary	The unique dice side indices.
	int unique_dice_side_indices[16];
public:
	/// Default constructor.
	ValueProvider();

	void Init(BoardValue** values, int num_values);

	/// Assigns the next set of values to the values which 
	/// are changing. If no more values to assign will
	/// return false
	/// @return	true if more values, false otherwise
	bool AssignNextValues();
};

class BoardSolver {
private:
	/// @summary	The perf-solver instance.
	BoggleSolver* solver;

	/// @summary	The singleon instance.
	static BoardSolver* instance;

	/// @summary	The value provider.
	static ValueProvider* value_provider;

	/// @summary	The current 16 letter board to score.
	char* board_to_score;

	/// @summary	The current maximum words
	int current_max_words;

	/// @summary	The variable values.
	BoardValue* variable_values[16];

	/// @summary	Number of variable values.
	int num_variable_values;

	/// @summary	The current board.
	BoardValue* board[16];

	/// @summary	The board with the higest # of words so far
	BoardValue* high_board[16];

	/// @summary	Number of boards solved.
	int number_of_boards_solved;
public:
	/// Prepare to solve current board.
	static void PrepareToSolveCurrentBoard();

	/// Gets the board and from the values provider and solves
	/// it, tracking how many words it produces
	static void SolveBoard();

	/// Makes the current hi-board (from calculating boards in the
	/// background) the board thats actually displayed
	static void AssignHighBoardToMainBoard();

	/// Initialises this object.
	static void Init();

	/// Query if 'str' is word.
	/// @param [in,out]	str	If non-null, the.
	/// @return	true if word, false if not.
	static bool IsWord(const char* str);

	/// Generates a random hi(300+ word) board.
	/// @return	The random hi board. (first 16 are the letters. then a space then the word count)
	static std::string GenerateRandomHiBoard();

	/// Creates the precalculated boards and writes it to the /dict folder
	static void CreatePrecalculatedBoards();
};

#endif  // __WORD_CHECKER__hpp
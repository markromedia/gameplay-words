#ifndef __WORD_CHECKER__hpp
#define __WORD_CHECKER__hpp

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "gameplay.h"
#include "perf-solver/boggle_solver.h"

#include "board.hpp"
#include "dice_manager.hpp"

class BoardSolver {
private:
	/// @summary	The perf-solver instance.
	BoggleSolver* solver;

	/// @summary	The singleon instance.
	static BoardSolver* instance;
public:
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
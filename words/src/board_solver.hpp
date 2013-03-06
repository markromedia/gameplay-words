#ifndef __WORD_CHECKER__hpp
#define __WORD_CHECKER__hpp

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iostream>

#include "gameplay.h"
#include "perf-solver/boggle_solver.h"

#include "board.hpp"
#include "letter_provider.hpp"

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
};

#endif  // __WORD_CHECKER__hpp
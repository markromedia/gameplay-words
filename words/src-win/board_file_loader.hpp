#ifdef WIN32
#ifndef __BOARD_FILE_LOADER__hpp
#define __BOARD_FILE_LOADER__hpp

#include <vector>
#include <queue>
#include <iostream>
#include <queue>
#include <algorithm>
#include <assert.h>

#include "gameplay.h"
#include "../src/board.hpp"
#include "../src/letter_provider.hpp"

class BoardFileLoader
{
public:
	static void LoadPrecalculatedBoard(std::queue<PrecalculatedBoard*> *precalculated_boards);
};

#endif  // __BOARD_FILE_LOADER__hpp
#endif
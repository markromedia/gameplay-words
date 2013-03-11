//
//  board_file_loader.hpp
//  words
//
//  Created by Mark Udit on 3/11/13.
//
//

#ifdef __APPLE__
#ifndef words_board_file_loader_hpp
#define words_board_file_loader_hpp

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <assert.h>


#include "../src/board.hpp"
#include "../src/letter_provider.hpp"

class BoardFileLoader {
public:
    static void LoadPrecalculatedBoard(std::queue<PrecalculatedBoard*>* precalculated_boards);
};

#endif
#endif

//
//  board_file_loader.hpp
//  words
//
//  Created by Mark Udit on 3/11/13.
//
//

#ifndef words_board_file_loader_hpp
#define words_board_file_loader_hpp

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <assert.h>


#include "../board/board.hpp"
#include "../board/dice_manager.hpp"

class BoardFileLoader {
public:
    static void LoadPrecalculatedBoard(std::queue<PrecalculatedBoard*>* precalculated_boards);
};

#endif

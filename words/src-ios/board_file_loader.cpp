//
//  board_file_loader.cpp
//  words
//
//  Created by Mark Udit on 3/11/13.
//
//

#ifdef __APPLE__
#include "board_file_loader.hpp"
#include "board_loader_bridge.h"

void BoardFileLoader::LoadPrecalculatedBoard(std::queue<PrecalculatedBoard*>* precalculated_boards) {
    readBoardLoaderLine();
}

#endif
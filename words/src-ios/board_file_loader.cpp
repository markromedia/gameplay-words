//
//  board_file_loader.cpp
//  words
//
//  Created by Mark Udit on 3/11/13.
//
//

#ifdef __APPLE__
#include "../src/board_file_loader.hpp"
#include "ios_bridge.h"

void BoardFileLoader::LoadPrecalculatedBoard(std::queue<PrecalculatedBoard*>* precalculated_boards) {
    loadPrecalculatedBoardsFile();
    
    int* line_values;
    std::vector<PrecalculatedBoard*> boards_vec;
    while ((line_values = readLineFromPrecalculateBoardsFile()) != NULL) {
        PrecalculatedBoard* board = new PrecalculatedBoard();;
        
        int idx = 0;
        for (int i = 0; i < 16; i++) {
            board->board[i][0] = line_values[idx++];
            board->board[i][1] = line_values[idx++];
        }
        boards_vec.push_back(board);
        
        //clean up array memory
        delete line_values;
    }
    
    assert (boards_vec.size() > 1);
    
    std::random_shuffle(boards_vec.begin(),boards_vec.end());
    for (unsigned int i = 0; i < boards_vec.size(); i++) {
        precalculated_boards->push(boards_vec[i]);
    }
}

#endif
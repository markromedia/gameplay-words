//
//  board_loader_bridge.h
//  words
//
//  Created by Mark Udit on 3/10/13.
//
//

#ifdef __APPLE__
#ifndef words_board_loader_bridge_h
#define words_board_loader_bridge_h

/**
 * Loads the precalcuated boards contents into
 * memory
 */
void loadPrecalculatedBoardsFile();

/**
 * Returns a 16 x 2 + 1 sized array that presents
 * a line (dice data followed by the word count)
 */
int* readLineFromPrecalculateBoardsFile();

/**
 * Prints the current thread name
 */
void printThreadName();

#endif
#endif

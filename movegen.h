#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <cstdint>
#include "board.h"
#include "move.h"

// move gen flags
#define ALL_MOVES 0
#define CAPTURES  1
#define QUIET     2

template<int flag>
int generateMoves(Board& board, struct Move moveList[], int color);

#endif
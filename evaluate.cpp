#include "evaluate.h"
#include "board.h"

#include <immintrin.h>

const int pieceValue[] = {100, 300, 320, 500, 900}; // pawn, knight, bishop, rook, queen

int evaluation(Board& board) {
    int whiteValue = materialValue(board, white);
    int blackValue = materialValue(board, black);

    int eval = whiteValue - blackValue;

    return board.blackToMove ? -eval : eval;
}

int materialValue(Board& board, int color) {
    int totalValue = 0;
    for (int i = 0; i < 5; i++) {
        uint64_t temp = board.pieces[i * 2 + color];
        int count = _mm_popcnt_u64(temp);
        totalValue += count * pieceValue[i];
    }

    return totalValue;
}
#include "evaluate.h"
#include "board.h"
#include <bit>

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
        int count = std::popcount(temp);
        totalValue += count * pieceValue[i];
    }

    return totalValue;
}
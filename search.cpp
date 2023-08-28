#include "search.h"
#include "board.h"
#include "evaluate.h"
#include "movegen.h"
#include "check_pin_masks.h"
#include "zobrist.h"
#include <cstdint>
#include <climits>

using namespace std;

#define INFINITY (INT_MAX)
#define NEGATIVE_INFINITY (-(INT_MAX))

struct Move bestMove;
int bestEval = NEGATIVE_INFINITY;

Move getBestMove(Board& board, int depth) {
    search(board, depth, depth, NEGATIVE_INFINITY, INFINITY, false);

    return bestMove;
}

bool flag = false;

// (* Initial call *)
// alphabeta(origin, depth, −∞, +∞, TRUE)
int search(Board& board, int startDepth, int depth, int alpha, int beta, bool capture) {

    if (depth == 0) {

        if (capture) {
            return quiesce(board, alpha, beta);
        } else {
            return evaluation(board);
        }

    }

    if (board.halfMoves >= 100) {
        return 0; // 50 move rule, stalemate
    }

    if (board.highestRepeat == 3) {
        return NEGATIVE_INFINITY;
    }

    Move moveList[256];
    int captureMoveCount = generateMoves<CAPTURES>(board, moveList, board.blackToMove);

    for (int i = 0; i < captureMoveCount; i++) {

        board.makeMove(moveList[i]);
        int eval = -search(board, startDepth, depth - 1, -beta, -alpha, false);
        board.unmakeMove();

        // if (depth == startDepth) {
        //     cout << i << " " << moveList[i] << " " << eval << endl;
        // }

        if (eval >= beta) {
            return beta;
        }

        if (eval > alpha) {
            alpha = eval;
            if (depth == startDepth) {
                bestMove = moveList[i];
            }
        }

    }

    int quietMoveCount = generateMoves<QUIET>(board, moveList, board.blackToMove);

    for (int i = 0; i < quietMoveCount; i++) {

        board.makeMove(moveList[i]);
        int eval = -search(board, startDepth, depth - 1, -beta, -alpha, true);
        board.unmakeMove();

        // if (depth == startDepth) {
        //     cout << i << " " << moveList[i] << " " << eval << endl;
        // }

        if (eval >= beta) {
            return beta;
        }

        if (eval > alpha) {
            alpha = eval;
            if (depth == startDepth) {
                bestMove = moveList[i];
            }
        }

    }

    int moveCount = quietMoveCount + captureMoveCount;
    if (moveCount == 0) {
        if (board.inCheck()) {
            return NEGATIVE_INFINITY + (startDepth - depth); // loss, + (startDepth - depth) makes faster mates worse
        } else {
            return 0; // stalemate
        }
    }

    return alpha;

}

int quiesce(Board& board, int alpha, int beta) {
    int eval = evaluation(board);

    if (eval >= beta) {
        return beta;
    }
    if (alpha < eval) {
        alpha = eval;
    }

    struct Move moveList[256];
    int moveCount = generateMoves<CAPTURES>(board, moveList, board.blackToMove);

    for (int i = 0; i < moveCount; i++) {

        board.makeMove(moveList[i]);
        int eval = -quiesce(board, -beta, -alpha);
        board.unmakeMove();

        if (eval >= beta) {
            return beta;
        }
        if (alpha < eval) {
            alpha = eval;
        }

    }

    return alpha;
}
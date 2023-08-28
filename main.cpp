#include <iostream>
#include <cstdint>
#include "board.h"
#include "precompute_masks.h"
#include "movegen.h"
#include "move.h"
#include "helpers.h"
#include "check_pin_masks.h"
#include "evaluate.h"
#include <chrono>
#include <thread>
#include "test_suite.h"
#include "search.h"
#include "zobrist.h"

using namespace std;

int moveGenTest(int depth, Board& board);

#define MAX_DEPTH 6

int main() {
    Board board;
    board.setStartPos();
    initMasks();

    board = generateBoardFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); // 8/2p5/3p4/KP5r/1R3pPk/8/4P3/8 b - - 0 1 // 8/4p3/8/1r3PpK/kp5R/3P4/2P5/8 w - - 0 1

    // start - > r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -
    // a1b1 -> r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/1R2K2R b Kkq - 0 1
    // h3g2 -> r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q2/PPPBBPpP/1R2K2R w Kkq - 0 1
    // a2a3 -> r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/P1N2Q2/1PPBBPpP/1R2K2R b Kkq - 0 1
    // g2h1b -> r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/P1N2Q2/1PPBBP1P/1R2K2b w kq - 0 1

    //board.setPieceSet(bpawns, 1);
    cout << board << endl;

    struct Move moveList[256];
    int count = generateMoves<CAPTURES>(board, moveList, board.blackToMove);
    cout << count << endl;

    // for (int i = 0; i < MAX_DEPTH + 1; i++) {
    //     chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    //     int nodes = moveGenTest(i, board);
    //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    //     auto time_span = chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //     cout << "depth " << i << " total nodes: " << nodes << " time: " << time_span.count() << " milliseconds" << endl;
    // }

    // cout << count << endl;
    // cout << evaluation(test) << endl;
    //runTests();

    initZobrist();

    // game loop
    while (board.halfMoves < 100 && board.highestRepeat < 3) {
        struct Move bestMove = getBestMove(board, 6);
        cout << bestMove << endl;
        board.makeMove(bestMove);

        std::cout << "\x1B[2J\x1B[H"; // clear screen
        cout << board << endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        string x;
        cin >> x;
    }

    return 0;
}

// g++ -Wall -g -std=c++20 -o chess main.cpp board.cpp movegen.cpp precompute_masks.cpp
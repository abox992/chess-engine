#include "test_suite.h"
#include "helpers.h"
#include "movegen.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int moveGenTestRecurrsive(int startDepth, int depth, Board& board);

int moveGenTest(int startDepth, Board& board) {
    return moveGenTestRecurrsive(startDepth, startDepth, board);
}

int moveGenTestRecurrsive(int startDepth, int depth, Board& board) {
    if (depth == 0) {
        return 1;
    }

    struct Move moveList[256];
    int count = generateMoves(ALL_MOVES, board, moveList, board.blackToMove);
    int totalNodes = 0;
    
    for (int i = 0; i < count; i++) {
        Board temp = board;
        temp.makeMove(moveList[i]);
        // cout << depth << " " << moveList[i] << endl;
        // cout << temp << endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        int subCount = 0;
        // if (depth == MAX_DEPTH && i != 50) {
        // } else {
        //     subCount = moveGenTest(depth - 1, temp);
        // }
        subCount = moveGenTestRecurrsive(startDepth, depth - 1, temp);
        // if (depth == startDepth) {
        //     cout << moveList[i] << " " << subCount << endl;
        // }
        //cout << moveList[i] << " " << subCount << endl;

        totalNodes += subCount;
    }
    
    return totalNodes;
}

void runTests() {

    std::vector<std::tuple<int, int, std::string>> tests = {
        std::make_tuple(5, 4865609, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"),
        std::make_tuple(6, 11030083, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"), 
        std::make_tuple(5, 15587335, "r3k2r/pp3pp1/PN1pr1p1/4p1P1/4P3/3P4/P1P2PP1/R3K2R w KQkq - 4 4"),
        std::make_tuple(5, 89941194, "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"),
        std::make_tuple(4, 3894594, "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"), 
        std::make_tuple(5, 193690690, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"), 
        std::make_tuple(4, 497787, "r3k1nr/p2pp1pp/b1n1P1P1/1BK1Pp1q/8/8/2PP1PPP/6N1 w kq - 0 1"), 
        std::make_tuple(6, 1134888, "3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1"), 
        std::make_tuple(6, 1440467, "8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1"), 
        std::make_tuple(6, 661072, "5k2/8/8/8/8/8/8/4K2R w K - 0 1"),
        std::make_tuple(7, 15594314, "3k4/8/8/8/8/8/8/R3K3 w Q - 0 1"),
        std::make_tuple(4, 1274206, "r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1"),
        std::make_tuple(5, 58773923, "r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1"),
        std::make_tuple(6, 3821001, "2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1"),
        std::make_tuple(5, 1004658, "8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1"),
        std::make_tuple(6, 217342, "4k3/1P6/8/8/8/8/K7/8 w - - 0 1"),
        std::make_tuple(6, 92683, "8/P1k5/K7/8/8/8/8/8 w - - 0 1"),
        std::make_tuple(10, 5966690, "K1k5/8/P7/8/8/8/8/8 w - - 0 1"),
        std::make_tuple(7, 567584, "8/k1P5/8/1K6/8/8/8/8 w - - 0 1"),
        std::make_tuple(6, 3114998, "8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1"),
        std::make_tuple(5, 42761834, "r1bq2r1/1pppkppp/1b3n2/pP1PP3/2n5/2P5/P3QPPP/RNB1K2R w KQ a6 0 12"),
        std::make_tuple(4, 3050662, "r3k2r/pppqbppp/3p1n1B/1N2p3/1nB1P3/3P3b/PPPQNPPP/R3K2R w KQkq - 11 10"),
        std::make_tuple(5, 10574719, "4k2r/1pp1n2p/6N1/1K1P2r1/4P3/P5P1/1Pp4P/R7 w k - 0 6"),
        std::make_tuple(4, 6871272, "1Bb3BN/R2Pk2r/1Q5B/4q2R/2bN4/4Q1BK/1p6/1bq1R1rb w - - 0 1"),
        std::make_tuple(6, 71179139, "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1"),
        std::make_tuple(6, 28859283, "8/PPPk4/8/8/8/8/4Kppp/8 b - - 0 1"),
        std::make_tuple(9, 7618365, "8/2k1p3/3pP3/3P2K1/8/8/8/8 w - - 0 1"),
        std::make_tuple(4, 28181, "3r4/2p1p3/8/1P1P1P2/3K4/5k2/8/8 b - - 0 1"),
        std::make_tuple(5, 6323457, "8/1p4p1/8/q1PK1P1r/3p1k2/8/4P3/4Q3 b - - 0 1")
    };

    int testNum = 1;

    cout << setfill('*') << setw(40) << "*" << endl;
    cout  << setfill(' ') << setw(29) <<  "Running Test Suite" << endl;
    cout << setfill('*') << setw(40) << "*" << endl;

    for (const auto &t : tests) {
        int depth = get<0>(t);
        int expected = get<1>(t);
        string fen = get<2>(t);

        Board board = generateBoardFromFen(fen);
        int output = moveGenTest(depth, board);

        if (output == expected) {

            if (testNum > 9) {
                cout << "Test #" << testNum << " - \033[1;32mPASSED!\033[0m" << endl;
            } else {
                cout << "Test #" << testNum << "  - \033[1;32mPASSED!\033[0m" << endl;
            }

        } else {
            cout << "FEN: " << fen << "\033[1;31m" << " FAILED" << "\033[0m" << " - " << "Expected: " << expected << " Output: " << output << endl;
        }

        testNum++;
    }
}
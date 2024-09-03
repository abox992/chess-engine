#ifndef BOARD_H
#define BOARD_H

#include "bit_manip.h"
#include "board_state.h"
#include "move.h"
#include "types.h"
#include <cstdint>
#include <iostream>
#include <memory>

class Board {
private:
    std::unique_ptr<BoardState> curState;

public:
    Board();
    explicit Board(std::string fen);
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    // https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    void set(const std::string fen);

    void setPieceSet(int i, uint64_t num);

    void setStartPos();

    void updateAllPieces();

    void makeMove(const class Move& move);
    void unmakeMove();

    bool inCheck() const;

    // curState getters
    inline uint64_t getBB(const int i) const { return curState->pieces[i]; }

    template <Color color>
    inline uint64_t getAll() const
    {
        return curState->allPieces[color];
    }

    inline uint64_t getAll(Color color) const { return curState->allPieces[color]; }

    inline int getHalfMoves() const { return curState->halfMoves; }

    inline int getFullMoves() const { return curState->fullMoves; }

    inline int getHighestRepeat() const { return curState->highestRepeat; }

    inline uint64_t getEmpty() const { return curState->empty; }

    inline uint64_t getOccupied() const { return ~curState->empty; }

    inline int enpassantPos() const { return curState->enpassantPos; }

    inline bool blackToMove() const { return curState->blackToMove; }

    inline bool canCastle(const int i) const { return curState->canCastle[i]; }

    template <Color color>
    inline int kingPos() const
    {
        return tz_count(curState->pieces[Piece::KINGS + static_cast<int>(color)]);
    }

    inline uint64_t hash() const { return curState->hash; }

    friend std::ostream& operator<<(std::ostream& o, Board& board);
};

#endif

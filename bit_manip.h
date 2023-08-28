#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#define x86 0

#if x86
    #include <bit>
    #include <cstdint>
    #include <immintrin.h>

    // pext equivalent 
    inline uint64_t extract_bits(uint64_t x, uint64_t mask) {
        return _pext_u64(x, mask);
    }

    inline uint64_t maskForPos(int x) {
        return (uint64_t(1) << (x));
    }

    inline int squareOf(uint64_t x) {
        return _tzcnt_u64(x);
    }

    #define Bitloop(X) for(;X; X = _blsr_u64(X))
    // Bitloop(bishops) {
    //      const Square sq = SquareOf(bishops);
    //      ...
    // }

#else
    #include <bit>
    #include <cstdint>

    // pext equivalent 
    constexpr uint64_t extract_bits(uint64_t x, uint64_t mask) {
        uint64_t res = 0;
        for(uint64_t bb = 1; mask != 0; bb += bb) {
            if(x & mask & -mask) {
            res |= bb;
            }
            mask &= (mask - 1);
        }
        return res;
    }

    inline uint64_t maskForPos(int x) {
        return (uint64_t(1) << (x));
    }

    inline int squareOf(uint64_t x) {
        return __builtin_ctzll(x);
    }

    #define Bitloop(X) for(;X; X = (X & (X-1)))

#endif

#endif
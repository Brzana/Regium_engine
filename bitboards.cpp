#include <stdio.h>
#include "defs.h"
#include <stdlib.h>



const int BitTable[64] = {
	63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52, 
	26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	58, 20, 37, 17, 36, 8
};

// this function finds the bit with a 1 that has the lowest index, returns the index and switch the value of that bit
int PopBit(U64* bb) {
	U64 b = *bb ^ (*bb - 1); // isolating the least significant bit (LSB)
	unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32)); // spliting 64 bits into 32 bits
	*bb &= (*bb - 1); // poping LSB
	return BitTable[(fold * 0x783a9b23) >> 26]; // returning index in BitTable
}

// this function counts bits
int CountBits(U64 b) {
	int r;
	for (r = 0; b; r++, b &= b - 1); // incrementing r when we find a bit that's 1, then changing it to 0
	return r;
}


void PrintBitBoard(U64 bb) { // bb = bitboard
	
	U64 shiftMe = 1ULL; // for shifting

	int rank = 0;
	int file = 0;
	int sq = 0;
	int sq64 = 0;

	printf("\n");
	for (rank = RANK_8; rank >= RANK_1; --rank) {
		for (file = FILE_A; file <= FILE_H; ++file) {
			sq = FileRankToSQ(file, rank); // 120 based
			sq64 = SQ64(sq); // 64 based

			if ((shiftMe << sq64) & bb)
				printf("X");
			else
				printf("-");
		}
		printf("\n");
	}
}
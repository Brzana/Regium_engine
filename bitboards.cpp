#include "stdio.h"
#include "defs.h"

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
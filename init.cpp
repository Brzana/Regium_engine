#include "defs.h"


int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

void InitSq120To64() {

	int i = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1; // square in 120 bit representation (starting at A1)
	int sq64 = 0; // square in 64 bit representation

	// initialazing table that maps 64 bit to 120 bit
	for (i = 0; i < 64; ++i) {
		Sq64ToSq120[i] = 120; // sets 120 as a wrong square
	}
	
	// initialazing table that maps 120 bit to 64 bit
	for (i = 0; i < BRD_SQ_NUM; ++i) {
		Sq120ToSq64[i] = 65; // sets 65 as a wrong square
	}
	
	// initialazing proper positions for 64 bits and 120 bits
	for (rank = RANK_1; rank <= RANK_8; ++rank) { // iterating through ranks
		for (file = FILE_A; file <= FILE_H; ++file) { // iterating through collumns
			sq = FileRankToSQ(file, rank);
			Sq64ToSq120[sq64] = sq; // from 64 to 120
			Sq120ToSq64[sq] = sq64; // from 120 to 64
			sq64++;
		}
	}
}

void AllInit() {
	InitSq120To64();
}
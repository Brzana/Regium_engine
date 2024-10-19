#include "defs.h"

// hashing means we xor the bit board to generate the unique position key, which is stored in U64 posKey

U64 GeneratePosKey(const S_BOARD* pos) {

	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;

	// pieces
	for (sq = 0; sq < BRD_SQ_NUM; ++sq) {
		piece = pos->pieces[sq];
		if (piece != NO_SQ && piece != EMPTY) {
			finalKey ^= PieceKeys[piece][sq];
		}
	}

	if (pos-> side == WHITE) {
		finalKey ^= SideKey;
	}

	if (pos->enPas != NO_SQ) {
		finalKey ^= SideKey;
	}

	finalKey ^= CastleKeys[pos->castlePerm];

	return finalKey;
}
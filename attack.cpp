#include "defs.h"

// offset 
const int knightOffSets[8] = { -21, -19, -12, -8, 8, 12, 19, 21 };
const int bishopOffSets[4] = { -11, -9, 9, 11 };
const int rookOffSets[4] = { -10, -1, 1, 10 };
const int kingOffSets[8] = { -11, -10, -9, -1, 1, 9, 10, 11 };

// side we pass in is the side that attacks
int SqAttacked(const int sq, const int side, const S_BOARD* pos) {

	int piece, i, t_sq, dir; // t_sq = temporary sq
	
	// pawns
	if (side == WHITE) {
		if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP) {
			return TRUE;
		}
		else {
			if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP) {
				return TRUE;
			}
		}
	}

	// knights
	for (i = 0; i < 8; ++i) {
		piece = pos->pieces[sq + knightOffSets[i]];
		if (IsKN(piece) && PieceCol[piece] == side) {
			return TRUE;
		}
	}

	// rooks and queens
	for (i = 0; i < 4; ++i) {
		dir = rookOffSets[i];
		t_sq = sq + dir;
		piece = pos->pieces[t_sq];
		while (piece != OFFBOARD) {
			if (piece != EMPTY) {
				if (IsRQ(piece) && PieceCol[piece] == side) {
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			piece = pos->pieces[t_sq];
		}
	}

	// bishops and queens
	for (i = 0; i < 4; ++i) {
		dir = bishopOffSets[i];
		t_sq = sq + dir;
		piece = pos->pieces[t_sq];
		while (piece != OFFBOARD) {
			if (piece != EMPTY) {
				if (IsRQ(piece) && PieceCol[piece] == side) {
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			piece = pos->pieces[t_sq];
		}
	}

	// kings
	for (i = 0; i < 8; ++i) {
		piece = pos->pieces[sq + kingOffSets[i]];
		if (IsKN(piece) && PieceCol[piece] == side) {
			return TRUE;
		}
	}

	return FALSE;
}
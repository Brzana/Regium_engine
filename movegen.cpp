#include <stdio.h>
#include "defs.h"

#define MOVE(f, t, ca, pro, fl)  ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQOFFBOARD(sq)  (FilesBoard[(sq)] == OFFBOARD)


void AddQuietMove(const S_BOARD* pos, int move, S_MOVELIST* list) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddCaptureMove(const S_BOARD* pos, int move, S_MOVELIST* list) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddEnPassantMove(const S_BOARD* pos, int move, S_MOVELIST* list) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddWhitePawnCapMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* list) {
	if (RanksBoard[from] == RANK_7) {
		AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
	}
	else {
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
	}
}

void AddWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list) {
	if (RanksBoard[from] == RANK_7) {
		AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
	}
	else {
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
	}
}



void GenerateAllMoves(const S_BOARD* pos, S_MOVELIST* list) {

	list->count = 0;

	int pce = EMPTY;
	int side = pos->side;
	int sq = 0;
	int t_sq = 0;
	int pceNum = 0;

	if (side == WHITE) {
		for (pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum) {
			sq = pos->pList[wP][pceNum];
			ASSERT(SqOnBoard(sq));

			if (pos->pieces[sq + 10] == EMPTY) {
				AddWhitePawnMove(pos, sq, sq + 10, list);
				if (RanksBoard[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY) {
					AddQuietMove(pos, MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), list);
				}
			}

			if (!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq + 9, pos->pieces[sq + 9], list);
			}
			if (!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK) {
				AddWhitePawnCapMove(pos, sq, sq + 11, pos->pieces[sq + 11], list);
			}

			if (pos->enPas != NO_SQ) {
				if (sq + 9 == pos->enPas) {
					AddEnPassantMove(pos, MOVE(sq, sq + 9, EMPTY, EMPTY, MFLAGEP), list);
				}
				if (sq + 11 == pos->enPas) {
					AddEnPassantMove(pos, MOVE(sq, sq + 11, EMPTY, EMPTY, MFLAGEP), list);
				}
			}
		}
	}
	else {
	}
}
#pragma once

#ifndef DEFS_H
#define DEFS_H

typedef unsigned long long U64;

#define NAME "REGIUM_ENGINE"
#define BRD_SQ_NUM 120
#define MAXGAMEMOVES 2048

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };

enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

enum { WHITE, BLACK, BOTH };

enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

enum { FALSE, TRUE };

// WKCA - white king side castling, WQCA - white queen side castling, B - black
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

// struct for undo (move this before S_BOARD)
typedef struct {
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	U64 posKey;
} S_UNDO;

// board structure
typedef struct {

	int pieces[BRD_SQ_NUM];
	U64 pawns[3];

	int KingSq[2];

	int side;
	int enPas;
	int fiftyMove;
	int castlePerm;

	int ply;
	int hisPly;

	U64 posKey;

	int pceNum[13];
	int bigPce[3];
	int majPce[3];
	int minPce[3];

	S_UNDO history[MAXGAMEMOVES]; // move history

	// piece list
	int pList[13][10];

} S_BOARD;

// moves generation struct
typedef struct {
	unsigned int from;
	unsigned int to;
	unsigned int captured;
	unsigned int flag;

} S_MOVE;

// MACROS
#define SQ64(sq120) Sq120ToSq64[sq120]
#define SQ120(sq64) Sq64ToSq120[64]
#define FileRankToSQ(f,r) (21 + (f)) + ((r) * 10)
#define POP(b) PopBit(b)
#define CountBits(b) CountBits(b)
#define ClearBit(bb,sq) ((bb) &= ClearMask[(sq)])
#define SetBit(bb,sq) ((bb) |= SetMask[(sq)])
 
// offset 
const int knightOffSets[8] = { -21, -19, -12, -8, 8, 12, 19, 21 };
const int bishopOffSets[4] = { -11, -9, 9, 11 };
const int rookOffSets[4] = { -10, -1, 1, 10 };
const int queenOffSets[8] = { -11, -10, -9, -1, 1, 9, 10, 11 };
const int kingOffSets[8] = { -11, -10, -9, -1, 1, 9, 10, 11 };

// GLOBALS
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

// FUNCTIONS

// init.c
extern void AllInit();

// bitboards.c
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64* bb);
extern int CountBits(U64 b);

#endif // DEFS_H

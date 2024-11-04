#pragma once

#include <stdio.h>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
        if (!(n)) { \
            printf("%s - Failed ", #n); \
            printf("On %s ", __DATE__); \
            printf("At %s ", __TIME__); \
            printf("In File %s ", __FILE__); \
            printf("At Line %d\n", __LINE__); \
        }
#endif


#ifndef DEFS_H
#define DEFS_H

typedef unsigned long long U64;

#define NAME "REGIUM_ENGINE"
#define BRD_SQ_NUM 120
#define MAXGAMEMOVES 2048
#define MAXPOSITIONMOVES 256
#define FenStartingPosition "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

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
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum { FALSE, TRUE };

// WKCA - white king side castling, WQCA - white queen side castling, B - black
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

typedef struct {
	int move;
	int score; // move order
} S_MOVE ;

typedef struct {
	S_MOVE moves[MAXPOSITIONMOVES];
	int count;
} S_MOVELIST;

typedef struct {
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	U64 poskey;
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
	int bigPce[2];
	int majPce[2];
	int minPce[2];
	int material[2];

	// piece list
	int pList[13][10];

	S_UNDO history[MAXGAMEMOVES];

} S_BOARD;

// Game Move
/*
0000 0000 0000 0000 0000 0111 1111 -> from 0x7F
0000 0000 0000 0011 1111 1000 0000 -> to >> 7 0x7F
0000 0000 0011 1100 0000 0000 0000 -> captured >> 14 0xF
0000 0000 0100 0000 0000 0000 0000 -> en passant 0x40000
0000 0000 1000 0000 0000 0000 0000 -> pawn start 0x80000
0000 1111 0000 0000 0000 0000 0000 -> pawn promotion >> 20 0xF
0001 0000 0000 0000 0000 0000 0000 -> castling move 0x1000000
better way od storing information instead of creating int for every single value
*/

#define FROMSQ(m)       ((m) & 0x3F)
#define TOSQ(m)         (((m) >> 7) & 0x3F)
#define CAPTURED(m)     (((m) >> 14) & 0xF)
#define PROMOTED(m)     (((m) >> 20) & 0xF)

#define MFLAGEP         0x40000
#define MFLAGPS         0x80000
#define MFLAGCA         0x100000

#define MFLAGCAP        0x7C000
#define MFLAGPROM       0xF00000



// MACROS
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define FileRankToSQ(f,r) (21 + (f)) + ((r) * 10)
#define POP(b) PopBit(b)
#define CountBits(b) CountBits(b)
#define ClearBit(bb,sq) ((bb) &= ClearMask[(sq)])
#define SetBit(bb,sq) ((bb) |= SetMask[(sq)])

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKN(p) (PieceKnight[(p)])
#define IsKI(p) (PieceKing[(p)])

// GLOBALS
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];

extern int FilesBoard[BRD_SQ_NUM];
extern int RanksBoard[BRD_SQ_NUM];

// for telling which piece we hit on the board in attack func
extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceBishopQueen[13];
extern int PieceRookQueen[13];

// FUNCTIONS

// init.cpp
extern void AllInit();

// bitboards.cpp
extern void PrintBitBoard (U64 bb);
extern int PopBit (U64* bb);
extern int CountBits (U64 b);

// haskeys.cpp
extern U64 GeneratePosKey (const S_BOARD* pos);

// board.cpp
extern int ParseFen (char* fen, S_BOARD* pos);
extern void ResetBoard (S_BOARD* pos);
extern void PrintBoard(const S_BOARD* pos);
extern void UpdateListsMaterial(S_BOARD* pos);
extern int CheckBoard(const S_BOARD* pos);

// attacked.cpp
extern int SqAttacked(const int sq, const int side, const S_BOARD* pos);

//io.cpp
extern char* PrSq(const int sq);
extern char* PrMove(const int move);
void PrintMoveList(const S_MOVELIST* list);

// validate.cpp
extern int SqOnBoard(const int sq);
extern int SideValid(const int side);
extern int FileRankValid(const int fr);
extern int PieceValidEmpty(const int pce);
extern int PieceValid(const int pce);

// movegen.cpp
extern void GenerateAllMoves(const S_BOARD* pos, S_MOVELIST* list);

#endif 

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
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 }; // 4 bits will tell us which castling is permited (1001, WKCA and BQCA are not permited)

// board structure
typedef struct {

	int piecies[BRD_SQ_NUM]; //stores information about the board state
	U64 pawns[3]; //stores information about pawns (01000000, theres a pawn on B file, each byte is 1 file), we use array to differantiate the color (using enum)

	int KingSq[2]; //stores kings position

	int side; //which color has a move
	int enPas; //checks the squares where enPassant is viable
	int fiftyMove; //checks for 50 move rule
	int castlePerm;

	int ply; //stores how many half moves we're into the search
	int hisPly; //half moves for determining the repetitions

	U64 posKey; //unique key generated for each position

	int pceNum[13]; //stores the number of pieces
	int bigPce[3]; //stores number of big pieces for each color (anything that isn't a pawn)
	int majPce[3]; //stores number of major pieces (rocks and queens)
	int minPce[3]; //stores number of minor pieces (knights and bishops)

	S_UNDO history[MAXGAMEMOVES]; //stores all needed information to undo moves, index is defined by histPly

} S_BOARD;

typedef struct {
	int move;
	int castlePrem;
	int enPAS;
	int fiftyMobe;
	U64 posKey;
} S_UNDO;

// MACROS

// GLOBALS
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

// FUNCTIONS

#endif // DEFS_H

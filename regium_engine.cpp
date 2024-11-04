﻿#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "defs.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define PAWNMOVES "rnbqkb1r/pp1p1ppp/8/2pP4/8/8/PPP2PPP/RNBQKBNR w KQkq e6 0 1"

int main() {
    AllInit();

    S_BOARD board[1];

    ParseFen((char*)PAWNMOVES, board);
    PrintBoard(board);

    S_MOVELIST list[1];

    GenerateAllMoves(board, list);
    PrintMoveList(list);

    return 0;

}


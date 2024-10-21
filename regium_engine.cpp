﻿#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "defs.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

int main()
{   
    AllInit();
    
    S_BOARD board[1];
    ParseFen((char*)FenStartingPosition, board);
    PrintBoard(board);

    ParseFen((char*)FEN1, board);
    PrintBoard(board);

    ParseFen((char*)FEN2, board);
    PrintBoard(board);

    ParseFen((char*)FEN3, board);
    PrintBoard(board);

    return 0;
}


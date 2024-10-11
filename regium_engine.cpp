#include <iostream>
#include "defs.h"

int main()
{   
    AllInit();

    int i;
    U64 playBitBoard = 0ULL;

    printf("Start: \n\n");
    PrintBitBoard(playBitBoard);

    playBitBoard |= (1ULL << SQ64(D2));
    printf("\n\nD2 Added: \n\n");
    PrintBitBoard(playBitBoard);

    playBitBoard |= (1ULL << SQ64(E2));
    printf("\n\nE2 Added: \n\n");
    PrintBitBoard(playBitBoard);

    // printing 64 bit board
    for (i = 0; i < BRD_SQ_NUM; ++i) {
        if (i % 10 == 0) printf("\n"); // cheking for the end of the board
        printf("%5d", Sq120ToSq64[i]);
    }

    printf("\n\n");

    // printing 120 bit board
    for (i = 0; i < 64; ++i) {
        if (i % 8 == 0) printf("\n"); // cheking for the end of the board
        printf("%5d", Sq64ToSq120[i]);
    }


}


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

    int count = CountBits(playBitBoard);

    printf("\nCount: %i\n", count);

    int index = POP(&playBitBoard);

    printf("Index 1: %i\n", index);

    index = POP(&playBitBoard);

    printf("Index 2: %i", index);

    return 0;
}


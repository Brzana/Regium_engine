#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "defs.h"

int main()
{   
    AllInit();
    srand(time(0));

    int PieceOne = rand();
    int PieceTwo = rand();
    int PieceThree = rand();
    int PieceFour = rand();

    printf("PieceOne:%X\n", PieceOne);
    printf("PieceTwo:%X\n", PieceTwo);
    printf("PieceThree:%X\n", PieceThree);
    printf("PieceFour:%X\n", PieceFour);

    int Key = PieceOne ^ PieceTwo ^ PieceThree ^ PieceFour;
    int TempKey = PieceOne;
    TempKey ^= PieceThree;
    TempKey ^= PieceFour;
    TempKey ^= PieceTwo;

    printf("Key: %X\n", Key);
    printf("TempKey: %X\n", TempKey);

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


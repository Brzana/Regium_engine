#include <iostream>
#include "defs.h"
#include "init.cpp"

int main()
{
    int i;
    
    AllInit();

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


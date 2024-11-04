//algebraic notation
#pragma warning(disable : 4996) // sprintf instead of sprintf_s

#include "stdio.h"
#include "defs.h"

char* PrSq(const int sq) {
	static char SqStr[3];

	int file = FilesBoard[sq];
	int rank = RanksBoard[sq];

	sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));

	return SqStr;
}


char* PrMove(const int move) {
    static char MvStr[6];

    int ff = FilesBoard[FROMSQ(move)];
    int rf = RanksBoard[FROMSQ(move)];
    int ft = FilesBoard[TOSQ(move)];
    int rt = RanksBoard[TOSQ(move)];

    int promoted = PROMOTED(move);

    if (promoted) {
        char pchar = 'q';
        if (IsKN(promoted)) {
            pchar = 'n';
        }
        else if (IsRQ(promoted) && !IsBQ(promoted)) {
            pchar = 'r';
        }
        else if (!IsRQ(promoted) && IsBQ(promoted)) {
            pchar = 'b';
        }
        sprintf(MvStr, "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
    }
    else {
        sprintf(MvStr, "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
    }

    return MvStr;
}


void PrintMoveList(const S_MOVELIST* list) {
	int i = 0;
	int score = 0;
	int move = 0;
	printf("MoveList:\n", list->count);

	for (i = 0; i < list->count; ++i) {
		move = list->moves[i].move;
		score = list->moves[i].score;

		printf("Move:%d > %s (score:%d)\n", i + 1, PrMove(move), score);
	}
	printf("MoveList Total %d Moves: \n\n", list->count);
}

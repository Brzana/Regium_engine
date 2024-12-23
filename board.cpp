#include <stdio.h>
#include "defs.h"


int CheckBoard(const S_BOARD* pos) {

	// mirroring for error handling
	int t_pceNum[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int t_bigPce[2] = { 0,0 };
	int t_majPce[2] = { 0,0 };
	int t_minPce[2] = { 0,0 };
	int t_material[2] = { 0,0 };

	int sq64, t_piece, t_pce_num, sq120, colour, pcount;

	U64 t_pawns[3] = { 0ULL,0ULL,0ULL };

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	for (t_piece = wP; t_piece <= bK; ++t_piece) {
		for (t_pce_num = 0; t_pce_num < pos->pceNum[t_piece]; ++t_pce_num) {
			sq120 = pos->pList[t_piece][t_pce_num];
			if (!(pos->pieces[sq120] == t_piece)) {
				printf("Position error. (pieces list)");
				return -1;
			}
		}
	}

	// check piece count and other counters
	for (sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = SQ120(sq64);
		t_piece = pos->pieces[sq120];
		t_pceNum[t_piece]++;
		colour = PieceCol[t_piece];
		if (PieceBig[t_piece] == TRUE) t_bigPce[colour]++;
		if (PieceMin[t_piece] == TRUE) t_minPce[colour]++;
		if (PieceMaj[t_piece] == TRUE) t_majPce[colour]++;

		t_material[colour] += PieceVal[t_piece];
	}

	for (t_piece = wP; t_piece <= bK; ++t_piece) {
		if (!(t_pceNum[t_piece] == pos->pceNum[t_piece])) {
			printf("Position error. (Number of pieces)");
			return -1;
		}
	}

	// check bitboards count
	pcount = CountBits(t_pawns[WHITE]);
	if (!(pcount == pos->pceNum[wP])) {
		printf("Position error. (Number of pawns)");
		return -1;
	}
	pcount = CountBits(t_pawns[BLACK]);
	if (!(pcount == pos->pceNum[bP])) {
		printf("Position error. (Number of pawns)");
		return -1;
	}
	pcount = CountBits(t_pawns[BOTH]);
	if (!(pcount == pos->pceNum[wP] + pos->pceNum[bP])) {
		printf("Position error. (Number of pawns)");
		return -1;
	}

	// check bitboards squares
	while (t_pawns[WHITE]) {
		sq64 = PopBit(&t_pawns[WHITE]);
		if (!(pos->pieces[SQ120(sq64)] == wP)) {
			printf("Position error. (Pawns squares)");
			return -1;
		}
	}

	while (t_pawns[BLACK]) {
		sq64 = PopBit(&t_pawns[BLACK]);
		if (!(pos->pieces[SQ120(sq64)] == bP)) {
			printf("Position error. (Pawns squares)");
			return -1;
		}
	}

	while (t_pawns[BOTH]) {
		sq64 = PopBit(&t_pawns[BOTH]);
		if (!(pos->pieces[SQ120(sq64)] == wP || pos->pieces[SQ120(sq64)])) {
			printf("Position error. (Pawns squares)");
			return -1;
		}
	}

	if (!(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK])) {
		printf("Position error. (Material)");
		return -1;
	}

	if (!(t_minPce[WHITE] == pos->minPce[WHITE] && t_minPce[BLACK] == pos->minPce[BLACK])) {
		printf("Position error. (Minor pieces)");
		return -1;
	}

	if (!(t_majPce[WHITE] == pos->majPce[WHITE] && t_majPce[BLACK] == pos->majPce[BLACK])) {
		printf("Position error. (Major pieces)");
		return -1;
	}

	if (!(t_bigPce[WHITE] == pos->bigPce[WHITE] && t_bigPce[BLACK] == pos->bigPce[BLACK])) {
		printf("Position error. (Big pieces)");
		return -1;
	}

	if (!(pos->side == WHITE || pos->side == BLACK)) {
		printf("Position error. (Side)");
		return -1;
	}

	if (!(GeneratePosKey(pos) == pos->posKey)) {
		printf("Position error. (Position Key)");
		return -1;
	}

	if (!(pos->enPas == NO_SQ || (RanksBoard[pos->enPas] == RANK_6 && pos->side == WHITE) || RanksBoard[pos->enPas] == RANK_3 && pos->side == BLACK)) {
		printf("Position error. (En passant)");
		return -1;
	}

	if (!(pos->pieces[pos->KingSq[WHITE]] == wK)) {
		printf("Position error. (King square)");
		return -1;
	}

	if (!(pos->pieces[pos->KingSq[BLACK]] == bK)) {
		printf("Position error. (King square)");
		return -1;
	}

	return TRUE;
}

void UpdateListsMaterial(S_BOARD* pos) {
	int piece, sq, i, colour;

	for (i = 0; i < BRD_SQ_NUM; ++i) {
		sq = i;
		piece = pos->pieces[i];
		if (piece != OFFBOARD && piece != EMPTY) {
			colour = PieceCol[piece];

			if (PieceBig[piece] == TRUE) pos->bigPce[colour]++;
			if (PieceMin[piece] == TRUE) pos->minPce[colour]++;
			if (PieceMaj[piece] == TRUE) pos->majPce[colour]++;

			pos->material[colour] += PieceVal[piece];

			// piece list
			// pList[Piece][PieceNumber]
			// pList[wP][0] = a1
			// pList[wP][1] = a2
			pos->pList[piece][pos->pceNum[piece]] = sq;
			pos->pceNum[piece]++;

			if (piece == wK) pos->KingSq[WHITE] = sq;
			if (piece == bK) pos->KingSq[BLACK] = sq; // kind of redundant, ill deal with these later

			if (piece == wP) {
				SetBit(pos->pawns[WHITE], SQ64(sq));
				SetBit(pos->pawns[BOTH], SQ64(sq));
			}
			else if (piece == bP) {
				SetBit(pos->pawns[BLACK], SQ64(sq));
				SetBit(pos->pawns[BOTH], SQ64(sq));
			}
		}
	}
}

int ParseFen(char* fen, S_BOARD* pos) {

	if (*fen == NULL) {
		printf("FEN error (StringIsNULL)\n");
		return 1;
	}

	if (pos == NULL) {
		printf("Board Structure error (BoardIsNULL)\n");
	}

	int rank = RANK_8;
	int file = FILE_A;
	int piece = EMPTY;
	int count = 0;
	int i = 0;
	int sq64 = 0;
	int sq120 = 0;

	ResetBoard(pos);

	while ((rank >= RANK_1) && *fen) {
		count = 1;  // Default count of squares to advance.

		switch (*fen) {
		case 'p': piece = bP; break;
		case 'r': piece = bR; break;
		case 'n': piece = bN; break;
		case 'b': piece = bB; break;
		case 'k': piece = bK; break;
		case 'q': piece = bQ; break;

		case 'P': piece = wP; break;
		case 'R': piece = wR; break;
		case 'N': piece = wN; break;
		case 'B': piece = wB; break;
		case 'K': piece = wK; break;
		case 'Q': piece = wQ; break;

		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			piece = EMPTY;  // No piece for numbers, just empty squares.
			count = *fen - '0'; // Convert ASCII numeral to int.
			break;

		case '/':
		case ' ':
			rank--;
			file = FILE_A;
			fen++;
			continue;

		default:
			printf("FEN error: invalid character '%c'\n", *fen);
			return -1;
		}

		// Loop over the number of squares to place the piece or advance.
		for (i = 0; i < count; i++) {
			if (file > FILE_H) {  // Ensure we don't overrun the file limits.
				printf("FEN error (file overflow)\n");
				return -1;
			}
			sq64 = rank * 8 + file;  // Convert rank/file to square index.
			sq120 = SQ120(sq64);  // Convert 64-based square to 120-based.

			if (piece != EMPTY) {
				pos->pieces[sq120] = piece;
			}

			file++;
		}

		fen++;  // Move to the next character in the FEN string.
	}

	// checking for errors
	if (*fen != 'w' && *fen != 'b') {
		printf("FEN error (side)\n");
		return -1;
	}

	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

	// castling perms
	for (int i = 0; i < 4; i++) {
		
		if (*fen != ' ' && *fen != 'K' && *fen != 'Q' && *fen != 'k' && *fen != 'q') {
			printf("Fen error (castling perms)");
			return - 1;
		}
		
		if (*fen == ' ') {
			break;
		}
		switch (*fen) {
		case 'K': pos->castlePerm |= WKCA; break;
		case 'Q': pos->castlePerm |= WQCA; break;
		case 'k': pos->castlePerm |= BKCA; break;
		case 'q': pos->castlePerm |= BQCA; break;
		default: break;
		}
		fen++;
	}
	fen++;

	// checking if castle perm is in bounds
	if (!(pos->castlePerm >= 0 && pos->castlePerm <= 15)) {
		printf("Castle Perm error ()outOfBounds");
		return -1;
	}

	// checking for enPas squares
	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		pos->enPas = FileRankToSQ(file, rank);
	}

	pos->posKey = GeneratePosKey(pos);

	UpdateListsMaterial(pos);

	return 0;
}

void ResetBoard(S_BOARD *pos) {

	int i = 0;

	for (i = 0; i < BRD_SQ_NUM; ++i) {
		pos->pieces[i] = OFFBOARD;
	}

	for (i = 0; i < 64; ++i) {
		pos->pieces[SQ120(i)] = EMPTY;
	}

	for (i = 0; i < 2; ++i) {
		pos->bigPce[i] = 0;
		pos->majPce[i] = 0;
		pos->minPce[i] = 0;
	}

	for (i = 0; i < 3; ++i) {
		pos->pawns[i] = 0ULL;
	}

	for (i = 0; i < 13; ++i) {
		pos->pceNum[i] = 0;
	}

	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side = BOTH;
	pos->enPas = NO_SQ;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->posKey = 0ULL;

}

void PrintBoard(const S_BOARD* pos) {

	int sq, file, rank, piece;

	printf("\nGameBoard:\n\n");

	for (rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d   ", rank + 1); // printing rank for readability
		for (file = FILE_A; file <= FILE_H; file++) {
			sq = FileRankToSQ(file, rank);
			piece = pos->pieces[sq]; // accesing piece for current sq
			printf("%3c", PceChar[piece]);
		}
		printf("\n");
	}

	printf("\n   ");
	for (file = FILE_A; file <= FILE_H; file++) {
		printf("%3c", 'a' + file); // printing file for readability
	}
	printf("\n");
	printf("side: %c\n", SideChar[pos->side]);
	printf("enPas: %d\n", pos->enPas);
	printf("castle perms: %c%c%c%c\n", pos->castlePerm & WKCA ? 'K' : '-',
		pos->castlePerm & WQCA ? 'Q' : '-',
		pos->castlePerm & BKCA ? 'k' : '-',
		pos->castlePerm & BQCA ? 'q' : '-');
	printf("PosKey: %llx\n", pos->posKey); // printing pos key in hexadecimal 
}
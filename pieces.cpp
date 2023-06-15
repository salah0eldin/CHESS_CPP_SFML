#include "pieces.h"

vector<Vector2i> pawnMoves(int board[][8], Vector2i indexs, bool isWhite) {
	vector<Vector2i> tempv, tempvfinal;
	Vector2i v;
	int direction = (isWhite ? -1 : 1);
	if (board[indexs.x + direction][indexs.y] == -1 && ((indexs.x == 1 && !isWhite) || (indexs.x == 6 && isWhite)))
	{
		v.x = indexs.x + 2 * direction;
		v.y = indexs.y;
		tempv.push_back(v);
	}
	v.x = indexs.x + 1 * direction;
	v.y = indexs.y;
	tempv.push_back(v);
	v.y = indexs.y + 1;
	tempv.push_back(v);
	v.y = indexs.y - 1;
	tempv.push_back(v);
	for (auto vv : tempv) {
		if (vv.y != indexs.y && board[vv.x][vv.y] != -1 && board[vv.x][vv.y] % 2 != isWhite % 2)
			tempvfinal.push_back(vv);
		else if (vv.y == indexs.y && board[vv.x][vv.y] == -1)
			tempvfinal.push_back(vv);

	}
	return tempvfinal;
}

vector<Vector2i> knightMoves(Vector2i indexs) {
	vector<Vector2i> tempv;
	Vector2i v;

	v.x = indexs.x - 2;
	v.y = indexs.y - 1;
	tempv.push_back(v);
	v.y = indexs.y + 1;
	tempv.push_back(v);
	v.x = indexs.x + 2;
	tempv.push_back(v);
	v.y = indexs.y - 1;
	tempv.push_back(v);
	v.y = indexs.y - 2;
	v.x = indexs.x - 1;
	tempv.push_back(v);
	v.x = indexs.x + 1;
	tempv.push_back(v);
	v.y = indexs.y + 2;
	tempv.push_back(v);
	v.x = indexs.x - 1;
	tempv.push_back(v);

	return tempv;
}

vector<Vector2i> bishopMoves(int board[][8], Vector2i indexs) {
	vector<Vector2i> tempv;
	Vector2i v;

	for (int i = 1; indexs.x + i < 8 && indexs.y + i < 8; i++)
	{
		v.x = indexs.x + i;
		v.y = indexs.y + i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}
	for (int i = 1; indexs.x - i > -1 && indexs.y + i < 8; i++)
	{
		v.x = indexs.x - i;
		v.y = indexs.y + i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}
	for (int i = 1; indexs.x + i < 8 && indexs.y - i > -1; i++)
	{
		v.x = indexs.x + i;
		v.y = indexs.y - i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}
	for (int i = 1; indexs.x - i > -1 && indexs.y - i > -1; i++)
	{
		v.x = indexs.x - i;
		v.y = indexs.y - i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}

	return tempv;
}

vector<Vector2i> castlMoves(int board[][8], Vector2i indexs) {
	vector<Vector2i> tempv;
	Vector2i v;

	v.y = indexs.y;
	for (int i = 1; indexs.x + i < 8; i++)
	{
		v.x = indexs.x + i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}
	for (int i = 1; indexs.x - i > -1; i++)
	{
		v.x = indexs.x - i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}
	v.x = indexs.x;
	for (int i = 1; indexs.y + i < 8; i++)
	{
		v.y = indexs.y + i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}
	for (int i = 1; indexs.y - i > -1; i++)
	{
		v.y = indexs.y - i;
		tempv.push_back(v);
		if (board[v.x][v.y] != -1)
			break;
	}

	return tempv;
}


vector<Vector2i> kingMoves(Vector2i indexs) {
	vector<Vector2i> tempv;
	Vector2i v;

	v.x = indexs.x - 1;
	v.y = indexs.y;
	tempv.push_back(v);
	v.y = indexs.y - 1;
	tempv.push_back(v);
	v.y = indexs.y + 1;
	tempv.push_back(v);
	v.x = indexs.x + 1;
	v.y = indexs.y;
	tempv.push_back(v);
	v.y = indexs.y - 1;
	tempv.push_back(v);
	v.y = indexs.y + 1;
	tempv.push_back(v);
	v.x = indexs.x;
	v.y = indexs.y - 1;
	tempv.push_back(v);
	v.y = indexs.y + 1;
	tempv.push_back(v);

	return tempv;
}

void pieces::getPossibleMoves(int board[][8]) {
	possibleMoves.clear();
	vector<Vector2i> pmtemp, pmtemp2;
	Vector2i v;
	switch (type) {
	case 'p':
		pmtemp = pawnMoves(board, indexs, isWhite);
		break;
	case 'n':
		pmtemp = knightMoves(indexs);
		break;
	case 'b':
		pmtemp = bishopMoves(board, indexs);
		break;
	case 'c':
		pmtemp = castlMoves(board, indexs);
		break;
	case 'q':
		pmtemp = bishopMoves(board, indexs);
		pmtemp2 = castlMoves(board, indexs);
		pmtemp.insert(pmtemp.end(), pmtemp2.begin(), pmtemp2.end());
		break;
	case 'k':
		pmtemp = kingMoves(indexs);
		break;
	}
	for (auto vv : pmtemp)
		if (vv.x > -1 && vv.x<8 && vv.y>-1 && vv.y < 8 && isWhite % 2 != board[vv.x][vv.y] % 2)
			possibleMoves.push_back(vv);
}

vector<Vector2i> pieces::checkMatePlaces(int board[][8], int isWhite) {
	vector<Vector2i> places;
	Vector2i tempplace;
	int direction = (isWhite ? -1 : 1);

	// pawns
	tempplace.x = indexs.x + direction;
	tempplace.y = indexs.y - 1;
	if (board[tempplace.x][tempplace.y] == (isWhite ? 0 : 1))
		places.push_back(tempplace);
	tempplace.y = indexs.y + 1;
	if (board[tempplace.x][tempplace.y] == (isWhite ? 0 : 1))
		places.push_back(tempplace);

	// knights
	vector<Vector2i> tempplaces = knightMoves(indexs);
	for (auto vv : tempplaces)
		if (board[vv.x][vv.y] == (isWhite ? 4 : 5))
			places.push_back(vv);

	// queens ,castls
	vector<Vector2i> tempv;
	Vector2i v;

	v.y = indexs.y;
	for (int i = 1; indexs.x + i < 8; i++)
	{
		v.x = indexs.x + i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 2 : 3) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();
	for (int i = 1; indexs.x - i > -1; i++)
	{
		v.x = indexs.x - i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 2 : 3) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();
	v.x = indexs.x;
	for (int i = 1; indexs.y + i < 8; i++)
	{
		v.y = indexs.y + i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 2 : 3) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();
	for (int i = 1; indexs.y - i > -1; i++)
	{
		v.y = indexs.y - i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 2 : 3) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();

	// queens , bishops
	for (int i = 1; indexs.x + i < 8 && indexs.y + i < 8; i++)
	{
		v.x = indexs.x + i;
		v.y = indexs.y + i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 6 : 7) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();
	for (int i = 1; indexs.x - i > -1 && indexs.y + i < 8; i++)
	{
		v.x = indexs.x - i;
		v.y = indexs.y + i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 6 : 7) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();
	for (int i = 1; indexs.x + i < 8 && indexs.y - i > -1; i++)
	{
		v.x = indexs.x + i;
		v.y = indexs.y - i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 6 : 7) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();
	for (int i = 1; indexs.x - i > -1 && indexs.y - i > -1; i++)
	{
		v.x = indexs.x - i;
		v.y = indexs.y - i;
		tempv.push_back(v);
		if (board[v.x][v.y] == (isWhite ? 6 : 7) || board[v.x][v.y] == (isWhite ? 8 : 9))
		{
			for (auto vv : tempv)
				places.push_back(vv);
			break;
		}
		if (board[v.x][v.y] != -1)
			break;
	}
	tempv.clear();


	return places;
}

void pieces::clearPiece() {
	type = ' ';
	possibleMoves.clear();
	isWhite = -1;
}
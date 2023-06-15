#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class pieces
{
public: 
	int isWhite=-1;
	char type;
	Vector2i indexs;
	vector<Vector2i> possibleMoves;
	void getPossibleMoves(int board[][8]);
	void clearPiece();
	vector<Vector2i> checkMatePlaces(int board[][8],int isWhite);
};


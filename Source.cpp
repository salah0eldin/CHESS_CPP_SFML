#include <SFML/Graphics.hpp>
#include <iostream>
#include "cellsClass.h"

using namespace sf;
using namespace std;


int main()
{
	int board[8][8] = {
	2,4,6,8,10,6,4,2,
	0,0,0,0,0,0,0,0,
	-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,
	1,1,1,1,1,1,1,1,
	3,5,7,9,11,7,5,3
	};

	int height = 700, width = 800;
	RenderWindow window(VideoMode(width, height), "CHESS Game");

	int sqsize = 70;
	bool cc = 0;
	// undo button
	RectangleShape undoButton;
	undoButton.setSize(Vector2f(2 * sqsize, sqsize / 2));
	undoButton.setPosition(width / 2 - sqsize, height - sqsize);
	undoButton.setFillColor(Color::Cyan);
	Font font;
	if (!font.loadFromFile("Roboto-Black.ttf"))
	{
		return -1;
	}
	Text undoButtonText;
	undoButtonText.setFont(font);
	undoButtonText.setString("Undo");
	undoButtonText.setCharacterSize(24);
	undoButtonText.setFillColor(Color::Black);
	undoButtonText.setPosition(undoButton.getPosition().x + undoButton.getSize().x / 2 - undoButtonText.getGlobalBounds().width / 2, undoButton.getPosition().y);
	// generate the cells
	cellsClass cells[8][8];
	cellsClass* celltemp;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			celltemp = &cells[i][j];
			celltemp->indexs = Vector2i(i, j);
			celltemp->piece.indexs = Vector2i(i, j);
			celltemp->square.setSize(Vector2f(sqsize, sqsize));
			celltemp->setCellPosition(width * 0.5 - 4 * (sqsize + 5) + (j % 8) * (sqsize + 5), height * 0.5 - 4 * (sqsize + 5) + (i % 8) * (sqsize + 5) - 35);
			if (cc = !cc)
				celltemp->square.setFillColor(Color(222, 184, 135));
			else
				celltemp->square.setFillColor(Color(139, 69, 19));
		}
		cc = !cc;

	}

	// generate the pices and its photos
	Texture texture[12];
	Sprite sprite[12];

	texture[0].loadFromFile("images/bpawn.png");
	sprite[0] = Sprite(texture[0]);

	texture[1].loadFromFile("images/wpawn.png");
	sprite[1] = Sprite(texture[1]);

	texture[2].loadFromFile("images/brook.png");
	sprite[2] = Sprite(texture[2]);

	texture[3].loadFromFile("images/wrook.png");
	sprite[3] = Sprite(texture[3]);

	texture[4].loadFromFile("images/bknight.png");
	sprite[4] = Sprite(texture[4]);

	texture[5].loadFromFile("images/wknight.png");
	sprite[5] = Sprite(texture[5]);

	texture[6].loadFromFile("images/bbishop.png");
	sprite[6] = Sprite(texture[6]);

	texture[7].loadFromFile("images/wbishop.png");
	sprite[7] = Sprite(texture[7]);

	texture[8].loadFromFile("images/bqueen.png");
	sprite[8] = Sprite(texture[8]);

	texture[9].loadFromFile("images/wqueen.png");
	sprite[9] = Sprite(texture[9]);

	texture[10].loadFromFile("images/bking.png");
	sprite[10] = Sprite(texture[10]);

	texture[11].loadFromFile("images/wking.png");
	sprite[11] = Sprite(texture[11]);

	Vector2f desiredSize(sqsize - 20, sqsize - 20);

	for (int i = 0; i < 12; i++)
		sprite[i].setScale(desiredSize.x / sprite[i].getLocalBounds().width,
			desiredSize.y / sprite[i].getLocalBounds().height);

	// black pawns
	for (int j = 0; j < 8; j++)
	{
		celltemp = &cells[1][j];
		celltemp->image = sprite[0];
		celltemp->piece.isWhite = 0;
		celltemp->piece.type = 'p';
	}
	for (int j = 0; j < 8; j++)
		cells[0][j].piece.isWhite = 0;

	// white pawns
	for (int j = 0; j < 8; j++)
	{
		celltemp = &cells[6][j];
		celltemp->image = sprite[1];
		celltemp->piece.isWhite = 1;
		celltemp->piece.type = 'p';
	}
	for (int j = 0; j < 8; j++)
		cells[7][j].piece.isWhite = 1;

	// black castls
	cells[0][0].image = cells[0][7].image = sprite[2];
	cells[0][0].piece.type = cells[0][7].piece.type = 'c';

	// white castls
	cells[7][0].image = cells[7][7].image = sprite[3];
	cells[7][0].piece.type = cells[7][7].piece.type = 'c';

	// black knights
	cells[0][1].image = cells[0][6].image = sprite[4];
	cells[0][1].piece.type = cells[0][6].piece.type = 'n';

	// white knights
	cells[7][1].image = cells[7][6].image = sprite[5];
	cells[7][1].piece.type = cells[7][6].piece.type = 'n';

	// black bishops
	cells[0][2].image = cells[0][5].image = sprite[6];
	cells[0][2].piece.type = cells[0][5].piece.type = 'b';

	// white bishops
	cells[7][2].image = cells[7][5].image = sprite[7];
	cells[7][2].piece.type = cells[7][5].piece.type = 'b';

	// black queen
	cells[0][3].image = sprite[8];
	cells[0][3].piece.type = 'q';
	// white queen
	cells[7][3].image = sprite[9];
	cells[7][3].piece.type = 'q';

	// black king
	cells[0][4].image = sprite[10];
	cells[0][4].piece.type = 'k';

	// white king
	cells[7][4].image = sprite[11];
	cells[7][4].piece.type = 'k';

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			cells[i][j].setPositions();

	bool isSelect = false;
	vector<Vector2i> possibleMoves;
	cellsClass* prev = &cells[0][0];
	int prevB = 0;
	cellsClass* kings[2] = { &cells[0][4],&cells[7][4] };

	cellsClass emptycell;

	bool whiteTurn = true;

	vector<Vector2i> checkMatePlaces;

	vector<pair<pair<cellsClass, int>, pair<cellsClass, int>>> moves;

	bool isPressed = false;

	while (window.isOpen())
	{
		window.clear(Color(255, 255, 255));
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				window.draw(cells[i][j].square);
				window.draw(cells[i][j].image);
			}
		window.draw(undoButton);
		window.draw(undoButtonText);
		window.display();

		// Handle events
		Event event;
		while (!window.pollEvent(event));

		if (event.type == Event::Closed)
			window.close();
		else if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				if (!isPressed)
				{
					isPressed = true;
					Vector2i mousePosition = Mouse::getPosition(window);
					Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
							if (cells[i][j].square.getGlobalBounds().contains(worldPosition))
							{
								celltemp = &cells[i][j];
								if (celltemp->image.getTexture() != nullptr && celltemp->piece.isWhite == (whiteTurn))
								{
									checkMatePlaces.clear();
									checkMatePlaces = kings[celltemp->piece.isWhite]->piece.checkMatePlaces(board, celltemp->piece.isWhite);
									isSelect = true;
									prev = celltemp;
									prevB = board[celltemp->indexs.x][celltemp->indexs.y];
									for (auto vv : possibleMoves)
										cells[vv.x][vv.y].unglow();
									possibleMoves.clear();
									celltemp->piece.getPossibleMoves(board);
									possibleMoves = celltemp->piece.possibleMoves;
									for (auto vv : possibleMoves)
									{
										bool found = false;
										for (auto cc : checkMatePlaces)
											if (vv == cc)
											{
												found = true;
												break;
											}
										if (celltemp->piece.type == 'k' && ((cells[vv.x][vv.y].image.getTexture() != nullptr && (abs(celltemp->indexs.x - vv.x) < 2 && abs(celltemp->indexs.y - vv.y) < 2))))
											cells[vv.x][vv.y].glow();
										else
										{
											int holder = board[vv.x][vv.y];
											board[vv.x][vv.y] = board[celltemp->indexs.x][celltemp->indexs.y];
											board[celltemp->indexs.x][celltemp->indexs.y] = -1;
											if (celltemp->piece.type == 'k' && cells[vv.x][vv.y].piece.checkMatePlaces(board, celltemp->piece.isWhite).empty())
												cells[vv.x][vv.y].glow();
											else if (celltemp->piece.type != 'k' && kings[celltemp->piece.isWhite]->piece.checkMatePlaces(board, celltemp->piece.isWhite).empty())
												cells[vv.x][vv.y].glow();
											board[celltemp->indexs.x][celltemp->indexs.y] = board[vv.x][vv.y];
											board[vv.x][vv.y] = holder;
										}
									}
								}
								else if (!celltemp->isGlow)
								{
									isSelect = false;
									prev = celltemp;
									prevB = board[celltemp->indexs.x][celltemp->indexs.y];
									for (auto vv : possibleMoves)
										cells[vv.x][vv.y].unglow();
									possibleMoves.clear();
								}
								else if (celltemp->isGlow)
								{
									isSelect = false;
									whiteTurn = !whiteTurn;
									for (auto vv : possibleMoves)
										cells[vv.x][vv.y].unglow();
									moves.push_back({ { *prev,board[prev->indexs.x][prev->indexs.y]},{*celltemp,board[celltemp->indexs.x][celltemp->indexs.y]} });
									possibleMoves.clear();
									celltemp->copyCell(prev);
									prev->clearCell();
									board[celltemp->indexs.x][celltemp->indexs.y] = prevB;
									board[prev->indexs.x][prev->indexs.y] = -1;
									prev = celltemp;
									if (celltemp->piece.type == 'k')
										kings[celltemp->piece.isWhite] = celltemp;
								}
							}
					if (undoButton.getGlobalBounds().contains(worldPosition) && !moves.empty())
					{
						whiteTurn = !whiteTurn;
						cells[moves.back().first.first.indexs.x][moves.back().first.first.indexs.y] = moves.back().first.first;
						cells[moves.back().second.first.indexs.x][moves.back().second.first.indexs.y] = moves.back().second.first;
						board[moves.back().first.first.indexs.x][moves.back().first.first.indexs.y] = moves.back().first.second;
						board[moves.back().second.first.indexs.x][moves.back().second.first.indexs.y] = moves.back().second.second;
						moves.pop_back();
					}
				}
			}
		}
		else if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				isPressed = false;
			}
		}
	}

	return 0;
}

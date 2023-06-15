#pragma once
#include <SFML/Graphics.hpp>
#include "pieces.h"

using namespace sf;

class cellsClass
{
public:
	Vector2f position;
	Vector2i indexs;
	RectangleShape square;
	Sprite image = Sprite();
	pieces piece;
	bool isGlow = false;
	void setCellPosition(float x, float y);
	void setPositions();
	void glow();
	void glowM();
	void unglow();
	void copyCell(cellsClass* prev);
	void clearCell();
};


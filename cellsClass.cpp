#include "cellsClass.h"

using namespace sf;

void cellsClass::setCellPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

void cellsClass::setPositions() {
	Vector2f pp = { 10,10 };
	square.setPosition(position);
	image.setPosition(position + pp);
}

void cellsClass::glow() {
	square.setOutlineThickness(5.f);
	square.setOutlineColor(sf::Color::Red);
	isGlow = true;
}

void cellsClass::glowM() {
	square.setOutlineThickness(5.f);
	square.setOutlineColor(sf::Color::Yellow);
	isGlow = true;
}

void cellsClass::unglow() {
	square.setOutlineThickness(0);
	square.setOutlineColor(sf::Color::White);
	isGlow = false;
}

void cellsClass::copyCell(cellsClass * prev) {
    image = prev->image;
	setPositions();
	piece = prev->piece;
	piece.indexs = indexs;
}

void cellsClass::clearCell() {
	Sprite sprite;
	image = sprite;
	piece.clearPiece();
}
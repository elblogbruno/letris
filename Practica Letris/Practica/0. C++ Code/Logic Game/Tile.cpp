#include "Tile.h"
#include <iostream>

Tile::Tile() {
	reachEnd = false;
}
Tile::Tile(string off, string on,string letterType): m_lletra(0, 0, TILE_WIDTH, TILE_HEIGHT, letterType, off.c_str(), on.c_str())
{
}

bool Tile::hasReachedEnd() {
	int posY = getLetterTargetRow() * (TILE_WIDTH + 1) + BOARD_INIT_X;
	//std::cout << posY << " " << getPosY() << endl;
	reachEnd = getPosY() == posY + 1 || getPosY() == posY - 1 || getPosY() == posY;
	return reachEnd;
}

void Tile::setLetterCoord(int column, int row) {
	setLetterColumn(column);
	setLetterRow(row);
	int posX = column * (TILE_WIDTH + 1) + BOARD_INIT_X;
	int posY = row * (TILE_HEIGHT + 1) + BOARD_INIT_Y;
	m_lletra.setButtonX(posX);
	m_lletra.setButtonY(posY);
}
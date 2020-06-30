#include "Tile.h"
#include <iostream>

Tile::Tile() {
	m_reachEnd = false;
}
Tile::Tile(string off, string on,string letterType): m_lletra(0, 0, TILE_WIDTH, TILE_HEIGHT, letterType, on.c_str(), off.c_str())
{
	m_aux_sprite.create(on.c_str()); //inicialitzem el sprite auxiliar per quan la lletra s'ha seleccionat.
}

bool Tile::hasReachedEnd() {
	int posY = getLetterRow() * (TILE_HEIGHT+0.5) + BOARD_INIT_Y;
	m_reachEnd = getPosY() > posY; //si la posicio de la lletra es mes gran que la posicio a la que ha de arribar , la lletra ha arribat al seu desti.
	if (m_reachEnd) {
		int diference = getPosY() - posY; //calculem la petita diferencia per que totes les lletres estiguin a la mateixa altura. Aixo fara que les lletres facin un petit "bounce(botin)" al arrivar al final.
		setPosY(getPosY() - diference);
	}
	return m_reachEnd;
}

void Tile::setActive(bool active) {
	m_active = active;
	m_lletra.setOn(active); //Podem controlar si el boto es interactuable o no.
	if (active) {
		m_lletra.setActive();
	}
	else {
		m_lletra.setNotActive();
	}
}
void Tile::setLetterCoord(int column, int row) {
	setLetterColumn(column);
	setLetterRow(row);

	int posX = column * (TILE_WIDTH + 0.5) + BOARD_INIT_X;
	int posY = 0 * (TILE_HEIGHT) + BOARD_INIT_Y;
	//Calculem la posicio i la transmitim al button.
	m_lletra.setButtonX(posX);
	m_lletra.setButtonY(posY);
}

Tile::Tile(const Tile& v) {
	m_row = v.m_row;
	m_column = v.m_column;
	m_lletra = v.m_lletra;
	m_reachEnd = v.m_reachEnd;
	m_aux_sprite = v.m_aux_sprite;
	m_hasBeenSelected = v.m_hasBeenSelected;
}
Tile& Tile::operator=(const Tile& v)
{
	if (this != &v)
	{
		m_row = v.m_row;
		m_column = v.m_column;
		m_lletra = v.m_lletra;
		m_reachEnd = v.m_reachEnd;
		m_aux_sprite = v.m_aux_sprite;
		m_hasBeenSelected = v.m_hasBeenSelected;
	}
	return *this;
}
bool Tile::operator==(Tile& v)
{
	return m_row == v.m_row && m_column == v.m_column && m_lletra.getButtonTag() == v.m_lletra.getButtonTag() && m_reachEnd == v.m_reachEnd;
}
void Tile::drawAuxiliar(int column) {
	int posX = column * (TILE_WIDTH) + BOARD_INIT_X;
	int posY = 12 * (TILE_HEIGHT) + BOARD_INIT_Y;

	if (m_active) {
		m_aux_sprite.draw(posX, posY);
	}
}
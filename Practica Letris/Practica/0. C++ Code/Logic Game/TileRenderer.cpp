#include "TileRenderer.h"


TileRenderer::TileRenderer() {
	
	for (int  i = 0; i < MAX_ALPHABET_ENGLISH; i++)
	{
		string nomFitxer = "./data/Letters/white_" + to_string(i) + ".png";
		m_aLetters_Normal[i].create(nomFitxer.c_str());
	}
}

void TileRenderer::Render(int column, int row) {

	for (int i = 0; i < column; i++) {
		for (int j = 0; j < row; j++) {
			int posX = 10 + (j*TILE_WIDTH + 30);
			int posY = 100 + (i*TILE_WIDTH + 50);
			m_aLetters_Normal[j].setScale(1);
			m_aLetters_Normal[j].draw(posX, posY);
		}
	}
}
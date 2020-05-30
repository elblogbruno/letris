#include "TileRenderer.h"
#include <iostream>

int TileRenderer::calculateNewLetter() {
	int randomIndex = 0;
	int randNumber = rand() % 100;
	if (randNumber < vowel_score) {
		randomIndex = rand() % MAX_ALPHABET_ENGLISH_VOWELS;
		std::cout << "USING VOWELS" << endl;
	}
	else {
		randomIndex = rand() % MAX_ALPHABET_ENGLISH_CONSONANTS;
		std::cout << "USING CONSONANTS" << endl;
	}
	return randomIndex;
}
int TileRenderer::calculateNewVelocity() {
	int result = (rand() % (1000 - 500)) + 500;
	return result;
}
TileRenderer::TileRenderer() {
	
	for (int  i = 0; i < MAX_ALPHABET_ENGLISH; i++)
	{
		string nomFitxer = "./data/Letters/white_" + to_string(i) + ".png";
		string nomFitxerYellow = "./data/Letters/yellow_" + to_string(i) + ".png";
		Tile tile = Tile(nomFitxer, nomFitxerYellow, abecedari[i]);
		int posX = 0 + (TILE_WIDTH + 1) + BOARD_INIT_X;
		int posY = 0 + (TILE_HEIGHT + 1) + BOARD_INIT_Y;
		tile.setPosX(posX);
		tile.setPosY(posY);
		m_aLetters_Normal[i] = tile;
	}

	std::cout << "Initializing first letter " << endl;

	randIndex = calculateNewLetter();
	velocity = calculateNewVelocity();
	column = rand() % 8 +1;
	row = 0;
	targetRow = 11;

	std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " IS THE FIRST LETTER ON THE BOARD WITH RANDINDEX: " << randIndex << endl;

	posX = column * (TILE_WIDTH + 1) + BOARD_INIT_X;
	posY = row * (TILE_HEIGHT + 1) + BOARD_INIT_Y;
	novaPosicioY = posY;
	m_aLetters_Random.resize(80);
	m_aLetters_Normal[randIndex].setLetterTargetRow(10);
	//m_aLetters_Normal[randIndex].setPosX(0);
	//m_aLetters_Normal[randIndex].setPosY(0);
	numOfLetters = 0;
}

void TileRenderer::Render( int mousePosX, int mousePosY, bool clicked, double& deltatime, bool stop) {


	if (m_aLetters_Normal[randIndex].hasReachedEnd()) {
		std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " HAS ARRIVED TO THE END WITH RANDINDEX: " << randIndex << endl;
		m_aLetters_Random.push_back(m_aLetters_Normal[randIndex]);

		novaPosicioY = 0;
		randIndex = calculateNewLetter();
		velocity = calculateNewVelocity();
		column = rand() % 8;
		
		/*for (int i = 0; i < m_aLetters_Random.size(); i++)
		{
			if (m_aLetters_Random[i].getLetterColumn() == m_aLetters_Normal[randIndex].getLetterColumn() && m_aLetters_Random[i].getLetterColumn() == m_aLetters_Normal[randIndex].getLetterColumn()) {
				std::cout << "THERE'S  A LETTER IN TEHE SAME ROW" << endl;
				//column--;
				targetRow--;
				row = targetRow;
				
			}
			else {
				
				targetRow = 11;
				row = targetRow;
			}
		}*/
		std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " IS A NEW LETTER ON THE BOARD WITH RANDINDEX: " << randIndex << endl;
		m_aLetters_Normal[randIndex].setLetterTargetRow(targetRow);
		//m_aLetters_Normal[randIndex].setPosX(0);
		//m_aLetters_Normal[randIndex].setPosY(0);
		std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetterTargetRow() << endl;
		std::cout << "Letter: " << m_aLetters_Random.size() << endl;
		m_aLetters_Normal[randIndex].setLetterCoord(column, row);
		numOfLetters++;
	}
	else {
		if (!stop) {
			novaPosicioY = novaPosicioY + deltatime * velocity;
			m_aLetters_Normal[randIndex].setPosY(novaPosicioY);
		}
		m_aLetters_Normal[randIndex].drawLetter();
	}
	//m_aLetters_Random[numOfLetters].drawLetter();
	if (m_aLetters_Random.size() > 0) {
		for (int i = 0; i < 1; i++)
		{
			//std::cout << "NUM OF LETTERS : " << numOfLetters << endl;
			std::cout << "Letter ON VECTOR : " << i + 1 << " " << m_aLetters_Random[i].getLetter() << endl;
			m_aLetters_Random[i].drawLetter();
			bool updating = m_aLetters_Random[i].updateLetterStatus(mousePosX, mousePosY, clicked);
			if (updating) {
				std::cout << m_aLetters_Random[i].getLetter();
			}
		}
	}
	
}

#include "TileRenderer.h"
#include <iostream>


TileRenderer::TileRenderer() {
	
	for (int  i = 0; i < MAX_ALPHABET_ENGLISH; i++)
	{
		string nomFitxer = "./data/Letters/white_" + to_string(i) + ".png";
		string nomFitxerYellow = "./data/Letters/yellow_" + to_string(i) + ".png";
		Tile tile = Tile(nomFitxer, nomFitxerYellow, abecedari[i]);
		int posX = 0 * (TILE_WIDTH - 0.5) + BOARD_INIT_X;
		int posY = 0 * (TILE_HEIGHT + 0.5) + BOARD_INIT_Y;
		tile.setPosX(posX);
		tile.setPosY(posY);
		m_aLetters_Normal[i] = tile;
	}

	//std::cout << "Initializing first letter " << endl;
	//lettersToFall.resize(8);
	m_rows.resize(8);
	wordIndex = 0;
	novaPosicioY = 1;
	randIndex = calculateNewLetter();
	velocity = calculateNewVelocity();

	//std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " IS THE FIRST LETTER ON THE BOARD WITH RANDINDEX: " << randIndex << endl;

	column = 0;
	columnAvailableIndex = 0;
	targetRow = 10;
	m_aLetters_Normal[randIndex].setLetterCoord(column, targetRow);

	posX = column * (TILE_WIDTH - 0.5) + BOARD_INIT_X;
	posY = targetRow * (TILE_HEIGHT + 0.5) + BOARD_INIT_Y;

	numOfLetters = 0;
	//lastIndex = randIndex;
}

void TileRenderer::Render( int mousePosX, int mousePosY, bool clicked, double& deltatime, bool stop) {
	if (numOfLetters != 80) {

		if (m_aLetters_Normal[randIndex].hasReachedEnd()) {
			//std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " HAS ARRIVED TO THE END WITH RANDINDEX: " << randIndex << " AND COLUMN " << column << endl;

			bool isFull = false;
			//lastIndex = randIndex;

			bool hasInserted = insertTile(column, isFull);
			
			if (hasInserted) {
				//std::cout << "HAS BEEN INSERTED ? : " << hasInserted  << endl;

				novaPosicioY = 1; //reseteja la posicio Y del tile.
				randIndex = calculateNewLetter(); //calcula una nova lletra al atzar
				velocity = calculateNewVelocity(); //calcula una nova velocitat al atzar de moment
				column = calculateNewColumn(); //Calcular una nova columna al atzar de la qual caura la nova lletra


				targetRow = calculateTargetRow(column, randIndex, isFull);
				m_aLetters_Normal[randIndex].setLetterCoord(column, targetRow); //Diem la columna i fila a la que la lletra anira a parar.

				numOfLetters++;
				std::cout << "NUM OF LETTERS SPAWNED: " << numOfLetters << endl;
			}
			else {
				std::cout << "ERROR INSERTANT TILE " << endl;
			}

		}
		else {
			if (!stop) {
				novaPosicioY = novaPosicioY + deltatime * velocity;
				m_aLetters_Normal[randIndex].setPosY(novaPosicioY-1);
			}
			m_aLetters_Normal[randIndex].drawLetter();
		}

	}
	else {
		std::cout << "MATRIX IS FULL " << endl;
	}
	
	if (numOfLetters > 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < m_rows[i].size(); j++) {
				m_rows[i][j].drawLetter();
				bool updating = m_rows[i][j].updateLetterStatus(mousePosX, mousePosY, clicked);
				if (updating && !m_rows[i][j].hasBeenSelected()) {
					possibleLetter.push_back(m_rows[i][j]);
					m_rows[i][j].setSelected(true);
					m_rows[i][j].setActive(true);
				}
				else if(!updating && m_rows[i][j].hasBeenSelected()){
					cout << "J IS " << j << endl;
					possibleLetter.erase(possibleLetter.begin() + (possibleLetter.size()-1));
					m_rows[i][j].setSelected(false);
					m_rows[i][j].setActive(false);
				}			
			}
		}
		for (int j = 0; j < possibleLetter.size(); j++) {
			possibleLetter[j].drawAuxiliar(j);
		}
	}

}

void TileRenderer::updateMatrixLetters(bool isCorrect, double& deltatime) {
	if (isCorrect) {
		for (int i = 0; i < possibleLetter.size(); i++)
		{
			int column = possibleLetter[i].getLetterColumn();
			for (int j = 0; j < m_rows[column].size(); j++)
			{
				if (m_rows[column][j].getLetter() == possibleLetter[i].getLetter() && m_rows[column][j].getLetterRow() == possibleLetter[i].getLetterRow()) {

					m_rows[column][j].setSelected(false);
					m_rows[column][j].setActive(false);

					if (j+1 < m_rows[column].size()) { //VOL DIR QUE HI HA UNA LLETRA PER SOBRE DEL INDEX DE LA LLETRA QUE ACABEM DE ELIMINAR
						int limit = 10 - j + 1;
						cout << "There are letters on top of remove one " << m_rows[column][j+1].getLetter() << endl;
						for (int c = j; c < limit; c++)
						{
							m_rows[column][c].setLetterRow(m_rows[column][c].getLetterRow() + 1);
							lettersToFallIndex.push_back(m_rows[column][c]);
						}
						numOfLetters--;
					}

					m_rows[column].erase(m_rows[column].begin() + j);

					

				}

			}	
		}
		for (int i = 0; i < lettersToFallIndex.size(); i++)
		{
			int column = lettersToFallIndex[i].getLetterColumn();
			if (m_rows[column][i].hasReachedEnd() == false)
			{
				novaPosicioY = novaPosicioY + deltatime * velocity;
				m_rows[column][i].setPosY(novaPosicioY - 1);
			}
		}
		possibleLetter.clear();
	}
	else {
		for (int i = 0; i < possibleLetter.size(); i++)
		{
			int column = possibleLetter[i].getLetterColumn();
			for (int j = 0; j < m_rows[column].size(); j++)
			{
				if (m_rows[column][j].getLetter() == possibleLetter[i].getLetter() && m_rows[column][j].getLetterRow() == possibleLetter[i].getLetterRow()) {
					m_rows[column][j].setSelected(false);
					m_rows[column][j].setActive(false);
					possibleLetter[i].setSelected(false);
					possibleLetter[i].setActive(false);
					//possibleLetter.erase(possibleLetter.begin() + i);
				}
			}
		}

		possibleLetter.clear();
	}

}
string TileRenderer::getPossibleWord() {
	string parcialWord;
	for (int i = 0; i < possibleLetter.size(); i++) {
		parcialWord += possibleLetter[i].getLetter(); //obtenim cada lletra del array de tiles possibles de ser una paraula correcta
	}
	return parcialWord;
}
bool TileRenderer::insertTile(int & column, bool& isFull){
	int columnSize = m_rows[column].size();
	bool inserted = false;
	//std::cout << "Column Size inserting: " << columnSize << " element column: " << column << endl;
	if (columnSize >= 0 && columnSize != 10 ) {
		m_rows[column].push_back(m_aLetters_Normal[randIndex]); //TODO: Fix this
		
		//std::cout << "Column Size after inserting: " << m_rows[column].size() << " element column: " << column << endl;
		inserted = true;
		isFull = false;
	}
	else {
		isFull = true;
	}
	return inserted;
}
int TileRenderer::calculateTargetRow(int& column, int& randIndex, bool isFull) {
	//std::cout << "Column : " << column << " RandIndex: " << randIndex << " Currrent target row: " << targetRow << "IS FULL ? : "<< isFull << endl;
	int columnSize = m_rows[column].size();
	if (columnSize == 10) {
		column = calculateNewColumn();
		int newColumnSize = m_rows[column].size();
		int lastIndex = newColumnSize - 1;
		int elementTargetRow = m_rows[column][lastIndex].getLetterRow();

		targetRow = elementTargetRow - 1;
	}
	else {
		if (columnSize > 0) {
			std::cout << lettersToFallIndex.size() << endl;
			/*if (lettersToFallIndex.size() != 0) {
				for (int i = 0; i < lettersToFallIndex.size(); i++)
				{
					if (lettersToFall[i].getLetterColumn() == column) {
						int elementTargetRow = lettersToFall[i].getLetterRow();

						targetRow = elementTargetRow - 1;
					}
				}
			}
			else {
				int lastIndex = columnSize - 1;
				int elementTargetRow = m_rows[column][lastIndex].getLetterRow();

				targetRow = elementTargetRow - 1;
			}*/
			int lastIndex = columnSize - 1;
			int elementTargetRow = m_rows[column][lastIndex].getLetterRow();

			targetRow = elementTargetRow - 1;

			//std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " ON THE SAME COLUMN " << "Column Size : " << columnSize << " Current target row: " << elementTargetRow << endl;
		}
		else {
			targetRow = 10;
			//std::cout << "Letter: " << m_aLetters_Normal[randIndex].getLetter() << " NOT ON THE SAME COLUMN " << "Column Size : " << columnSize << " Current target row: " << targetRow << endl;
		}
	}

	return targetRow;
}

int TileRenderer::calculateNewLetter() {
	int randomIndex = 0;
	int randNumber = rand() % 100;
	if (randNumber < vowel_score) {
		int randomVowel = rand() % MAX_ALPHABET_ENGLISH_VOWELS;
		randomIndex = vocalPosition[randomVowel];
		std::cout << "USING VOWELS" << endl;
	}
	else {
		int randomConsonant = rand() % MAX_ALPHABET_ENGLISH_CONSONANTS;
		randomIndex = consonantPosition[randomConsonant];
		std::cout << "USING CONSONANTS" << endl;
	}
	return randomIndex;
}
int TileRenderer::calculateNewVelocity() {
	int result = (rand() % (1000 - 600)) + 600;
	return result;
}
int TileRenderer::calculateNewColumn() {
	//TODO anar eliminant columnes ja plenes per obtenir mes probabililtat 
	int randomColumn = 0;

	//cout << "AVAILABLE ROWS: " << columnAvailable.size() << endl;
	/*for (int  i = 0; i < columnAvailable.size(); i++)
	{
		if (m_rows[columnAvailable[i]].size() == 10) {
			cout << "ERASING" << i << " COLUMN" << endl;
			columnErased.push_back(columnAvailable[i]);
			columnAvailable.erase(columnAvailable.begin() + i);
			break;
		}
	}*/
	if (columnAvailableIndex < 7) {
		//randomColumn = rand() % columnAvailable.size();
		//columnAvailableIndex = columnAvailable[columnAvailableIndex] + 1;
		columnAvailableIndex++;
		cout << "INDEX IS " << columnAvailableIndex << " COLUMN" << endl;
	}
	else {
		columnAvailableIndex = 0;
		//columnAvailableIndex = columnAvailable[columnAvailableIndex] + 1;
		cout << "INDEX IS RESET " << columnAvailableIndex << " COLUMN" << endl;
	}
	return columnAvailableIndex;
}
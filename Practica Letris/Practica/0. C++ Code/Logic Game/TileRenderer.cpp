#include "TileRenderer.h"
#include <iostream>
#include <list>


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

	m_rows.resize(8);
	m_novaPosicioY = 1; //Resetejem el incrementador de la lletra a 0 perque la seguent lletra caigui desde la posicio inicial i no la posicio ja incrementada
	m_randIndex = calculateNewLetter(); //Lletra a l'atzar inicial
	m_newVelocity = 600; //Velocitat inicial de la primera lletra

	m_columnAvailableIndex = 0;
	m_column = 0;
	m_targetRow = 10;
	m_aLetters_Normal[m_randIndex].setLetterCoord(m_column, m_targetRow);


	m_isFirstLetter = true;
	m_numOfLetters = 0;
	m_Points = 0;
}

void TileRenderer::Render( int mousePosX, int mousePosY, bool clicked, double& deltatime, bool stop,bool hasDicLoaded, float timerPartida) {
	if (m_numOfLetters != 80) {
		if (m_aLetters_Normal[m_randIndex].hasReachedEnd() ) { //Si la lletra ha arribat al seu desti, creem una de nova al atzar.

			bool isFull = false; //Retorna si la columna esta plena
			bool hasInserted = insertTile(m_column, isFull); //insereix la lletra en la matriu i retorna un bolea que ens avisa de si ha hagut algun error.
			
			if (hasInserted) {
				m_novaPosicioY = 1; //Resetejem el incrementador de la lletra a 0 perque la seguent lletra caigui desde la posicio inicial i no la posicio ja incrementada.
				m_randIndex = calculateNewLetter(); //calcula una nova lletra al atzar
				m_column = calculateNewColumn(); //Calcular una nova columna al atzar de la qual caura la nova lletra
				m_numOfLetters++; //incrementem el numero de lletres del tauler
			}
		}
		else {
			if (hasDicLoaded && m_isFirstLetter) {
				m_aLetters_Normal[m_randIndex].setLetterCoord(m_column, 0); //En la primera lletra ha de estar a dalt de tot i em de esperar a que el diccionari a carregat
				m_isFirstLetter = false;
			}
			else {
				if (!stop) {
					arrangeColumn(deltatime); // si s'han eliminat lletres em de mirar de arreglar cada columna abans de que la lletra caigui
					m_targetRow = calculateTargetRow(m_column); //recalculament frame a frame de la fila a la que anira a parar la lletra per si hi ha un canvi de ultima hora.
					m_aLetters_Normal[m_randIndex].setLetterCoord(m_column, m_targetRow); //modifiquem la columna i fila consequentment.

					int velocity = calculateNewVelocity(timerPartida); //calculem la nova velocitat amb el timerPartida
					m_novaPosicioY = m_novaPosicioY + deltatime * velocity; //augmentem aquesta posicio amb el deltatime i la velocitat
					m_aLetters_Normal[m_randIndex].setPosY(m_novaPosicioY); //canviem la posicio de la lletra que esta caient.
					m_aLetters_Normal[m_randIndex].drawLetter(); //dibuixem la lletra que esta caient.
				}

			}
			
		}
	}
	
	if (m_numOfLetters > 0) {
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < m_rows[i].size(); j++) {
				m_rows[i][j].drawLetter(); //dibuixa la lletra ja establerta
				if (!m_rows[i][j].hasBeenSelected()) {
					m_updating = m_rows[i][j].updateLetterStatus(mousePosX, mousePosY, clicked); //si ha estat seleccionada no podem interactuar amb ella i eliminem la nostra eleccio amb el boto x
				}
				
				if (m_updating && !m_rows[i][j].hasBeenSelected()) {
					possibleLetter.push_back(m_rows[i][j]); //si seleccionem una lletra la afegim al nostre array de possibles lletres que formen una paraula existent al diccionari
					m_rows[i][j].setSelected(true); //fiquem el bolea seleccionat a true com que ha estat seleccionada.
				}	
			}
		}
		if (possibleLetter.size() > 0) {
			for (int j = 0; j < possibleLetter.size(); j++) {
				possibleLetter[j].drawAuxiliar(j); // per cada lletra seleccionada dibuixem el seu sprite auxiliar a sota de tot que inicialitzem al inici al mateix temps que la lletra.
			}
		}
	}
	
}
void TileRenderer::resetPossibleWord() {
	int selectedColumn = 0;
	for (int i = 0; i < possibleLetter.size(); i++)
	{
		int index = findLetterOnMatrix(possibleLetter[i], selectedColumn);
		if (index != -1) {
			m_rows[selectedColumn][index].setSelected(false);
			m_rows[selectedColumn][index].setActive(false);
		}
	}
	possibleLetter.clear();
}

void TileRenderer::updateMatrixLetters(bool isCorrect, double& deltatime) {
	if (isCorrect) {
		int selectedColumn = 0;
		for (int i = 0; i < possibleLetter.size(); i++)
		{
			int index = findLetterOnMatrix(possibleLetter[i], selectedColumn);
			if (index != -1) {
				deleteTile(selectedColumn, index); //Eliminem la lletra seleccionada i aquesta funcio observara si hi ha una lletra per sobre de la eliminada, que al canviar la mida del array dinamic haura pres la seva posicio.
				m_numOfLetters--; //Disminuim en consequencia el numero de lletres en el tauler de joc.
				m_Points++; //incrementem el numero de punts
			}
		}
	}
	else {
		//La paraula no existeix en el diccionari,llavors la desselecionem.
		resetPossibleWord();
		if (m_Points >= 0) {
			m_Points--; //decrementem el numero de punts del jugador
		}
	}

}

void TileRenderer::deleteTile(int column, int row) {
	if ((row + 1) < m_rows[column].size() && (m_rows[column].size() > 0)) {
		m_rows[column][row + 1].setLetterRow(m_rows[column][row].getLetterRow());
		m_rows[column][row + 1].setPosY(m_rows[column][row].getPosY());
		m_rows[column][row + 1].setActive(false);
	}
	m_rows[column].erase(m_rows[column].begin() + row);

	columnFixed.push_back(column);
	rowFixed.push_back(row);
}


void TileRenderer::arrangeColumn(double &deltatime) {

	if (columnFixed.size() > 0) {
		for (int i = 0; i < columnFixed.size(); i++)
		{
			int row = rowFixed[i];
			int column = columnFixed[i];
			int columnSize = m_rows[column].size();
			cout << row << " / " << column << " " << m_rows[column].size() << " size " << endl;

			if (columnSize > 1 && columnSize < 10) { //te com a minim una lletra per sobre , llavors hem de recorrer per sobre de aquesta lletra i baixar les lletres superiors.

				for (int i = row; i <= columnSize; i++)
				{
					if ((i + 1) < columnSize) {

						cout << " There's still a letter on top " << m_rows[column][i + 1].getLetter() << " / " << m_rows[column][i + 1].getLetterRow() << endl;

						m_rows[column][i+1].setLetterRow(m_rows[column][i].getLetterRow()-1);
						
						m_rows[column][i+1].setPosY(m_rows[column][i].getPosY() - 51);

						cout << " There's still a letter on top modified " << m_rows[column][i + 1].getLetter() << " / " << m_rows[column][i + 1].getLetterRow() << endl;
					}
					else {
						if ((i + 1) > columnSize && i != row) {
							cout << " LAST LETTER OF THE ROW " << m_rows[column][i].getLetter() << " / " << m_rows[column][i].getLetterRow() << endl;

							m_rows[column][i].setLetterRow(m_rows[column][i].getLetterRow());

							m_rows[column][i].setPosY(m_rows[column][i].getPosY() - 51);

							cout << " There's still a letter on top modified " << m_rows[column][i].getLetter() << " / " << m_rows[column][i].getLetterRow() << endl;

						}
						else {
							cout << "THERE IS NO LETTER ON TOP" << endl;
						}
						break;
					}
				}
			}
		}
		/*columnFixed.clear();
		rowFixed.clear();
		possibleLetter.clear();*/
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
	if (columnSize >= 0 && columnSize != 10 ) {
		m_rows[column].push_back(m_aLetters_Normal[m_randIndex]);
		inserted = true;
		isFull = false;
	}
	else {
		isFull = true;
	}
	return inserted;
}
int TileRenderer::calculateTargetRow(int& column) {
	int columnSize = m_rows[column].size();

	if (columnSize == 10) {
		column = calculateNewColumn(); //si la fila esta plena calculem una nova fila per la lletra a caure.
		int newColumnSize = m_rows[column].size();
		int lastIndex = newColumnSize - 1;
		int elementTargetRow = m_rows[column][lastIndex].getLetterRow();
		m_targetRow = elementTargetRow - 1;
	}
	else {
		if (columnFixed.size() > 0) { //hi ha hagut modificacions en les columnes
			columnSize = m_rows[column].size();
			if (columnSize > 0) {
				int lastIndex = columnSize-1;
				int elementTargetRow = m_rows[column][lastIndex].getLetterRow();
				int diferencia = elementTargetRow - m_aLetters_Normal[m_randIndex].getLetterRow();
				m_targetRow = m_aLetters_Normal[m_randIndex].getLetterRow() + diferencia;
			}
			else {
				m_targetRow = 10; //No hi haura cap element a la columna, aleshores la lletra a de caure en la ultima fila.
			}
			columnFixed.clear();
			rowFixed.clear();
			possibleLetter.clear();
		}
		else {
			if (columnSize > 0) {
				int lastIndex = columnSize - 1; //agafem el index de la ultima lletra existent
				int elementTargetRow = m_rows[column][lastIndex].getLetterRow(); //agadem la seva fila

				m_targetRow = elementTargetRow - 1; //li diem a la lletra que anira a parar una fila per sobre.
			}
			else {
				m_targetRow = 10; //si no hi ha cap mes lletra a la fila la seva fila sera la ultima de totes.
			}
		}
	}

	return m_targetRow;
}

int TileRenderer::calculateNewLetter() {
	int randomIndex = 0;
	int randNumber = rand() % 100; //agafem un numero random del 1 al 100
	if (randNumber < vowel_score) { //observem si esta per sota del numero necesari per obtenir vocals
		int randomVowel = rand() % MAX_ALPHABET_ENGLISH_VOWELS;
		randomIndex = vocalPosition[randomVowel];
	}
	else {
		int randomConsonant = rand() % MAX_ALPHABET_ENGLISH_CONSONANTS;
		randomIndex = consonantPosition[randomConsonant];
	}
	return randomIndex;
}

int TileRenderer::calculateNewVelocity(float timerPartida) {
	int timerPartidaNew = timerPartida;
	if ((timerPartidaNew % 10) == 0) {
		if (timerPartida - timerPartidaNew < 0.05) {

			m_newVelocity = m_newVelocity + 2;
		}
	}
	return m_newVelocity;
}

int TileRenderer::calculateNewColumn() {
	//TODO anar eliminant columnes ja plenes per obtenir mes probabililtat 
	int randomColumn = 0;

	if (m_columnAvailableIndex < 7) {
		//randomColumn = rand() % smallerColumns.size();
		//columnAvailableIndex = smallerColumns[randomColumn];
		m_columnAvailableIndex++;
		//cout << "INDEX IS " << columnAvailableIndex << " COLUMN" << endl;
	}
	else {
		m_columnAvailableIndex = 0;
		//columnAvailableIndex = columnAvailable[columnAvailableIndex] + 1;
		//cout << "INDEX IS RESET " << columnAvailableIndex << " COLUMN" << endl;
	}
	return m_columnAvailableIndex;


}
int TileRenderer::findLetterOnMatrix(Tile tile,int &column) {
	int index = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < m_rows[i].size(); j++)
		{
			if (m_rows[i][j] == tile) {
				column = i;
				index = j;
				break;
			}
		}
	}
	return index;
}

bool TileRenderer::isFull()
{
	return m_numOfLetters == 80;
}
void TileRenderer::resetBoard()
{
	for (int i = 0; i < m_rows.size(); i++)
	{
		m_rows[i].clear();
	}

	m_numOfLetters = 0;
	possibleLetter.clear();
	m_isFirstLetter = true;

	m_novaPosicioY = 1;
	m_randIndex = calculateNewLetter();
	m_newVelocity = 600; //Velocitat inicial de la primera lletra

	m_column = 0;
	m_columnAvailableIndex = 0;
	m_targetRow = 10;
	m_Points = 0;
}
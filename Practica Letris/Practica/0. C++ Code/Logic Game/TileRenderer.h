#pragma once
#include "../Graphic Lib/libreria.h"
#include "joc.h"
#include <string>
#include "Tile.h"
#include <vector> 
using namespace std;


const int vowel_score = 30;
const int consonant_score = 60;
class TileRenderer
{
	public:
		TileRenderer();
		void Render(int mousePosX, int mousePosY, bool clicked, double &deltatime, bool stop, bool hasDicLoaded,float timerPartida);

		int calculateNewLetter();
		int calculateNewVelocity(float timerPartida);
		int calculateNewColumn();
		int calculateTargetRow(int &column);
		string getPossibleWord() ;
		bool insertTile(int& column, bool &isFull);

		void resetPossibleWord();
		void updateMatrixLetters( bool isCorrect, double& deltatime);
		int findLetterOnMatrix(Tile tile, int& column);
		void arrangeColumn(double& deltatime);

		void deleteTile(int column, int row);
		bool isFull();
		void resetBoard();
		int getPoints() { return m_Points; };
	private:
		Tile  m_aLetters_Normal[MAX_ALPHABET_ENGLISH];
		vector<vector<Tile>> m_rows;

		string abecedari[MAX_ALPHABET_ENGLISH] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
		int vocalPosition[MAX_ALPHABET_ENGLISH_VOWELS] = { 0,4,8,14,20 };
		int consonantPosition[MAX_ALPHABET_ENGLISH_CONSONANTS] = { 1,2,3,5,6,7,9,10,11,12,13,15,16,17,18,19,21,22,23,24,25};
		
		
		vector<Tile> possibleLetter;
		vector<int> columnFixed;
		vector<int> rowFixed;

		vector<int> smallerColumns;
		vector<int> columnAvailable = { 0,1,2,3,4,5,6,7 };
		vector<int> columnErased;

		int m_novaPosicioY;

		int m_column;
		int m_targetRow;

		int m_numOfLetters;
		int m_Points;
		int m_randIndex;

		int m_columnAvailableIndex = 0;
		
		bool m_updating;
		bool m_isFirstLetter;


		int m_newVelocity;
};


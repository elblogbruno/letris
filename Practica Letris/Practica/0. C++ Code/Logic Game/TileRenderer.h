#pragma once
#include "../Graphic Lib/libreria.h"
#include "joc.h"
#include <string>
#include "Tile.h"
#include <vector> 
using namespace std;


const int vowel_score = 60;
const int consonant_score = 30;
class TileRenderer
{
	public:
		TileRenderer();
		void Render(int mousePosX, int mousePosY, bool clicked, double &deltatime, bool stop);

		int calculateNewLetter();
		int calculateNewVelocity();
		int calculateNewColumn();
		int calculateTargetRow(int &column,int &randIndex, bool isFull);
		string getPossibleWord() ;
		bool insertTile(int& column, bool &isFull);

		void updateMatrixLetters( bool isCorrect, double& deltatime);
	private:
		Tile  m_aLetters_Normal[MAX_ALPHABET_ENGLISH];
		//vector<Tile>  m_aLetters_Random;
		vector<vector<Tile>> m_rows;

		string abecedari[MAX_ALPHABET_ENGLISH] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
		int vocalPosition[MAX_ALPHABET_ENGLISH_VOWELS] = { 0,4,8,14,20 };
		int consonantPosition[MAX_ALPHABET_ENGLISH_CONSONANTS] = { 1,2,3,5,6,7,9,10,11,12,13,15,16,17,18,19,21,22,23,24,25};
		vector<string> possibleWord;
		vector<Tile> possibleLetter;

		vector<Tile> lettersToFallIndex;
		//vector<int> columnAvailable = { 0,1,2,3,4,5,6,7 };
		//vector<int> columnErased;
		int novaPosicioY;

		int column;

		int targetRow;

		int posX;
		int posY;
		
		int numOfLetters;
		int randIndex;

		int columnAvailableIndex = 0;
		int velocity;
		int wordIndex;
};


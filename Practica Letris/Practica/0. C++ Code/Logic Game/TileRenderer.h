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
	private:
		Tile  m_aLetters_Normal[MAX_ALPHABET_ENGLISH];
		vector<Tile>  m_aLetters_Random;

		string abecedari[MAX_ALPHABET_ENGLISH] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

		int novaPosicioY;

		int column;
		int row;
		int targetRow;

		int posX;
		int posY;
		
		//int randNumber;
		int numOfLetters;
		int randIndex;
		//int lastIndex;

		int velocity;
};


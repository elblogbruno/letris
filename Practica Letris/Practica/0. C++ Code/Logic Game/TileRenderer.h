#pragma once
#include "../Graphic Lib/libreria.h"
#include "joc.h"
#include <string>
using namespace std;
class TileRenderer
{
	
	public:
		TileRenderer();
		void Render(int column, int row);
	private:
		Sprite m_aLetters_Normal[MAX_ALPHABET_ENGLISH];
		
};


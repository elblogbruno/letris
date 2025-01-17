#pragma once
#include "MainMenu.h"
#include "PlayingState.h"
#include "GameOverState.h"
class LetrisGame
{
	public:
		LetrisGame();
		void UpdateAndDraw(int mousePosX, int mousePosY, bool moousePressed,  double &deltaTime);
	private:
		GameOverState gameOverState;
		MainMenu mainMenuState;
		PlayingState playingState;
		DictionaryHandler dictionaryHandler;

		bool esGameOver;
		int m_estatActual;
		int m_currentLanguage;
};


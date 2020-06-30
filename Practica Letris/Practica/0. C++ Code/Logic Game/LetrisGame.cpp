#include "LetrisGame.h"
#include <iostream>
LetrisGame::LetrisGame()  {
	 mainMenuState = MainMenu();
	 playingState = PlayingState();
	 gameOverState = GameOverState();
	 dictionaryHandler = DictionaryHandler();
}
void LetrisGame::UpdateAndDraw(int mousePosX, int mousePosY, bool moousePressed,  double &deltaTime)
{
	switch (m_estatActual)
	{
		case MAIN_MENU:
			mainMenuState.drawMainMenu(mousePosX, mousePosY, moousePressed, m_estatActual, m_currentLanguage, dictionaryHandler);
			break;
		case PLAYING:
			if (mainMenuState.isDicOpen() && dictionaryHandler.hasBeenLoaded()) {
				esGameOver = playingState.drawPlayingState(mousePosX, mousePosY, moousePressed, m_estatActual, deltaTime, dictionaryHandler);
			}
			break;
		case GAME_OVER:
			gameOverState.drawGameOverState(m_estatActual, esGameOver, deltaTime);
			break;
		default:
			break;
	}
}
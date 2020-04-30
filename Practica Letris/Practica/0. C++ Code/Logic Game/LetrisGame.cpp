#include "LetrisGame.h"

LetrisGame::LetrisGame() {
	 mainMenuState = MainMenu();
	 playingState = PlayingState();
	 gameOverState = GameOverState();
}
void LetrisGame::UpdateAndDraw(int mousePosX, int mousePosY, bool moousePressed,  double &deltaTime)
{
	switch (m_estatActual)
	{
		case MAIN_MENU:
			mainMenuState.drawMainMenu(mousePosX, mousePosY, moousePressed, m_estatActual);
			break;
		case PLAYING:
			esGameOver = playingState.drawPlayingState(mousePosX, mousePosY, moousePressed, m_estatActual, deltaTime);
			break;
		case GAME_OVER:
			gameOverState.drawGameOverState(m_estatActual, esGameOver, deltaTime);
			break;
		default:
			break;
	}
}
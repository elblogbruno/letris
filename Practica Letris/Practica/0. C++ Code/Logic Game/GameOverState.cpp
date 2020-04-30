#include "GameOverState.h"

GameOverState::GameOverState() : fonsFinalPartida("./data/GUI/GameOver.png")
{
	//esGameOver = true;
	timerGameOver = 0;
}


void GameOverState::drawGameOverState(int &m_estatActual, bool &esGameOver,double &deltaTime)
{
	fonsFinalPartida.draw(0, 0);
	if (esGameOver) {
		timerGameOver += deltaTime;
		//fontNegra.draw(200, 50, NFont::Scale(0.85f), "%d", (int)timerGameOver);
	}
	if (timerGameOver > 5.0f) {
		esGameOver = false;
		timerGameOver = 0;
		m_estatActual = MAIN_MENU;
	}
}


#include "GameOverState.h"

GameOverState::GameOverState() : m_fonsFinalPartida("./data/GUI/GameOver.png")
{
	m_timerGameOver = 0;
}


void GameOverState::drawGameOverState(int &m_estatActual, bool &esGameOver,double &deltaTime)
{
	m_fonsFinalPartida.draw(0, 0);
	if (esGameOver) { //si hem perdut realment la partida inicia el contador de espera.
		m_timerGameOver += deltaTime;
	}
	if (m_timerGameOver > 5.0f) { //si han passat els 5 segons de espera,tornem al menu inicial
		esGameOver = false;
		m_timerGameOver = 0;
		m_estatActual = MAIN_MENU;
	}
}


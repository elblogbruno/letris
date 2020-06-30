#pragma once
#include "../Graphic Lib/NFont/NFont.h"
#include "joc.h"

class GameOverState
{
public:
	//Constructor del main menu
	GameOverState();
	void drawGameOverState(int &m_estatActual, bool &esGameOver, double &deltaTime);
private:
	Sprite m_fonsFinalPartida;
	float m_timerGameOver;
};


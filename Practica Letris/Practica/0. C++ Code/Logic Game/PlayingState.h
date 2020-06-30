#pragma once
#include "../Graphic Lib/NFont/NFont.h"
#include "Button.h"
#include "TileRenderer.h"
#include "DictionaryHandler.h"
#include "PauseMenu.h"
class PlayingState
{
public:
	//Constructor del main menu
	PlayingState();
	bool drawPlayingState(int mousePosX, int mousePosY, bool moousePressed, int &m_estatActual, double &deltaTime, DictionaryHandler& dic);
private:
	Sprite m_fonsPlaying;
	Sprite m_timeBar;
	//Botons creats amb la classe Button.
	NFont m_fontNegra;
	NFont m_fontBlanca;
	PauseMenu m_PauseMenu;
	//TileRenderer
	TileRenderer m_matriuLletres;
	//
	Button m_botoPausaPlayContador;
	Button m_botoEliminar;
	Button m_botoCheck;
	Button m_botoStart;
	float m_timerPartida;
	//PLAYING VARIABLES
	//GAME OVER VARIABLES
	bool m_esGameOver;
	bool m_drawMatrix;
	bool m_pausarContador;
	bool m_check;
	bool m_eliminarMatriu;
	bool m_drawTimer;
	bool m_shouldDrawPauseMenu;
	bool m_resetInPause;
};


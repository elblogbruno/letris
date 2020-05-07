#pragma once
#include "../Graphic Lib/NFont/NFont.h"
#include "Button.h"
#include "TileRenderer.h"
class PlayingState
{
public:
	//Constructor del main menu
	PlayingState();
	bool drawPlayingState(int mousePosX, int mousePosY, bool moousePressed, int &m_estatActual, double &deltaTime);
private:
	Sprite fonsPlaying;
	Sprite timeBar;
	//Botons creats amb la classe Button.
	NFont fontNegra;
	NFont fontBlanca;

	//TileRenderer
	TileRenderer matriuLletres;
	//
	Button botoPausaPlayContador;
	Button botoEliminar;
	Button botoCheck;
	Button botoStart;
	float timerPartida;
	//PLAYING VARIABLES
	//GAME OVER VARIABLES
	bool esGameOver;
	bool drawMatrix;
	bool pausarContador;
	bool check;
	bool eliminarMatriu;
	bool drawTimer;

};


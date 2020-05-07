#include "joc.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <iostream>
#include "LetrisGame.h"
#include "GameState.h"
using namespace std;



//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc()
{
	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(MIDA_X, MIDA_Y);
	//Mostrem la finestra grafica
	pantalla.show();

	
	LetrisGame game = LetrisGame();

	
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	bool esGameOver;
	do
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		// Captura tots els events de ratol� i teclat de l'ultim cicle
		pantalla.processEvents();

		bool mouseStatus = Mouse_getBtnLeft();
		bool moousePressed = Mouse_getButLeft();

		int mousePosX = Mouse_getX();
		int mousePosY = Mouse_getY();

		
		game.UpdateAndDraw(mousePosX, mousePosY, moousePressed, deltaTime);


		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}

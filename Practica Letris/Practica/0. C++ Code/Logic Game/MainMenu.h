#pragma once
#include "../Graphic Lib/NFont/NFont.h"
#include "Button.h"
#include "joc.h"
class MainMenu
{
public:
	//Constructor del main menu
	MainMenu();
	void drawMainMenu(int mousePosX, int mousePosY, bool moousePressed, int &m_estatActual);
private:
	Sprite fonsMenuInicial;
	//Botons creats amb la classe Button.
	NFont fontBlanca;
	/*Button botoCatala;
	Button botoCastella;
	Button botoAngles;*/
	Button botoStart;
	//MAIN_MENU VARIABLES
	bool drawCatala;
	bool drawCastella;
	bool drawAngles;
	bool startPresionat;
	Button idiomes[3];
	int currentLanguage;
};


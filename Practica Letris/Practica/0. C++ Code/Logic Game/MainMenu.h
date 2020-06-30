#pragma once
#include "../Graphic Lib/NFont/NFont.h"
#include "Button.h"
#include "joc.h"
#include "DictionaryHandler.h"
class MainMenu
{
public:
	//Constructor del main menu
	MainMenu();
	void drawMainMenu(int mousePosX, int mousePosY, bool moousePressed, int &m_estatActual, int& languageCode, DictionaryHandler &dic); //Dibuixa el main Menu i li passem el objecte encarregat del diccionari
	bool isDicOpen() { return m_DicOpen; }; //retorna si s'ha obert el diccionari seleccionat
private:
	Sprite m_fonsMenuInicial;
	
	NFont m_fontBlanca;

	Button m_botoStart;
	//MAIN_MENU VARIABLES
	bool m_drawCatala;
	bool m_drawCastella;
	bool m_drawAngles;
	bool m_startPresionat;
	//Botons creats amb la classe Button.
	Button m_idiomes[3]; //Sera un array llavors podrem obtenir el idioma escollit facilment.
	int m_currentLanguage;
	bool m_DicOpen = false; //Avisa de si el diccionari ha estat carregat ja i podem començar la partida.
};


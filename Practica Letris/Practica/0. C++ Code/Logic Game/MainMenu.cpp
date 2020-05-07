#include "MainMenu.h"


MainMenu::MainMenu() : fontBlanca("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255)), 
fonsMenuInicial("./data/GUI/MainMenu_BG.png")
{
	idiomes[0] = Button(100, 120, 30, 30,"cat", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png",0);
	idiomes[1] = Button(100, 170, 30, 30, "cast", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png",1);
	idiomes[2] = Button(100, 220, 30, 30, "ang", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png",2);

	botoStart = Button(150, 725,194,85, "start","./data/GUI/Button_Pressed.png", "./data/GUI/Button_Normal.png");
	//MAIN_MENU VARIABLES
	drawCatala = false;
	drawCastella = false;
	drawAngles = false;
	startPresionat = false;

	currentLanguage = 0;
	//idiomes[currentLanguage].setActive(true);
}


void MainMenu::drawMainMenu(int mousePosX, int mousePosY, bool moousePressed,int &m_estatActual) 
{
	//Dibuixa  el fons de pantalla.
	fonsMenuInicial.draw(0, 0);

	idiomes[0].drawButton();
	idiomes[1].drawButton();
	idiomes[2].drawButton();
	//Dibuixa el boto sense escollir per default
	fontBlanca.draw(150, idiomes[0].getButtonY() - 6, NFont::Scale(0.85f), "Catala");
	fontBlanca.draw(150, idiomes[1].getButtonY() - 6, NFont::Scale(0.85f), "Castella");
	fontBlanca.draw(150, idiomes[2].getButtonY() - 6, NFont::Scale(0.85f), "Angles");

	drawCatala = idiomes[0].updateButtonRadioButtonArray(mousePosX, mousePosY, moousePressed, currentLanguage);
	drawCastella = idiomes[1].updateButtonRadioButtonArray(mousePosX, mousePosY, moousePressed, currentLanguage);
	drawAngles = idiomes[2].updateButtonRadioButtonArray(mousePosX, mousePosY, moousePressed, currentLanguage);
	
	//currentlanguage es util per saber el identificador numeral del idioma escollit.
	for (int i = 0; i < 3; i++)
	{
		if (i == currentLanguage) {
			idiomes[i].setActive();
		}
		else {
			idiomes[i].setNotActive();
		}
	}
	

	botoStart.drawButton();
	fontBlanca.draw(botoStart.getButtonX() + 50, botoStart.getButtonY() + 20, NFont::Scale(0.85f), "START");
	startPresionat = botoStart.updateButton(mousePosX, mousePosY, moousePressed);
	if (startPresionat) {
		m_estatActual = PLAYING;
	}
}


#include "MainMenu.h"


MainMenu::MainMenu() : fontBlanca("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255)), 
fonsMenuInicial("./data/GUI/MainMenu_BG.png")
{
	botoCatala = Button(100, 120, 30, 30,"cat", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png");
	botoCastella = Button(100, 170, 30, 30, "cast", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png");
	botoAngles = Button(100, 220, 30, 30, "ang", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png");

	botoStart = Button(150, 725,194,85, "start","./data/GUI/Button_Pressed.png", "./data/GUI/Button_Normal.png");
	//MAIN_MENU VARIABLES
	drawCatala = false;
	drawCastella = false;
	drawAngles = false;
	startPresionat = false;
}


void MainMenu::drawMainMenu(int mousePosX, int mousePosY, bool moousePressed,int &m_estatActual) 
{
	//Dibuixa  el fons de pantalla.
	fonsMenuInicial.draw(0, 0);

	botoCatala.drawButton();
	botoCastella.drawButton();
	botoAngles.drawButton();
	//Dibuixa el boto sense escollir per default
	fontBlanca.draw(150, botoCatala.getButtonY() - 6, NFont::Scale(0.85f), "Catala");
	fontBlanca.draw(150, botoCastella.getButtonY() - 6, NFont::Scale(0.85f), "Castella");
	fontBlanca.draw(150, botoAngles.getButtonY() - 6, NFont::Scale(0.85f), "Angles");

	drawCatala = botoCatala.updateButtonRadioButton(mousePosX, mousePosY, moousePressed);
	drawCastella = botoCastella.updateButtonRadioButton(mousePosX, mousePosY, moousePressed);
	drawAngles = botoAngles.updateButtonRadioButton(mousePosX, mousePosY, moousePressed);

	botoStart.drawButton();
	fontBlanca.draw(botoStart.getButtonX() + 50, botoStart.getButtonY() + 20, NFont::Scale(0.85f), "START");
	startPresionat = botoStart.updateButton(mousePosX, mousePosY, moousePressed);
	if (startPresionat) {
		m_estatActual = PLAYING;
	}
}


#include "MainMenu.h"



MainMenu::MainMenu() : m_fontBlanca("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255)),
m_fonsMenuInicial("./data/GUI/MainMenu_BG.png")
{
	m_idiomes[0] = Button(100, 120, 30, 30,"cat", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png",0);
	m_idiomes[1] = Button(100, 170, 30, 30, "cast", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png",1);
	m_idiomes[2] = Button(100, 220, 30, 30, "ang", "./data/GUI/Checkbox_Enabled.png", "./data/GUI/Checkbox_Disabled.png",2);

	m_botoStart = Button(150, 725,200,90, "start","./data/GUI/Button_Pressed.png", "./data/GUI/Button_Normal.png");
	//MAIN_MENU VARIABLES
	m_drawCatala = false;
	m_drawCastella = false;
	m_drawAngles = false;
	m_startPresionat = false;
	m_currentLanguage = 0;
	//idiomes[currentLanguage].setActive(true);
}


void MainMenu::drawMainMenu(int mousePosX, int mousePosY, bool moousePressed,int &m_estatActual,int &languageCode, DictionaryHandler &dic)
{
	//Dibuixa  el fons de pantalla.
	m_fonsMenuInicial.draw(0, 0);

	m_idiomes[0].drawButton();
	m_idiomes[1].drawButton();
	m_idiomes[2].drawButton();
	//Dibuixa el boto sense escollir per default
	m_fontBlanca.draw(150, m_idiomes[0].getButtonY() - 6, NFont::Scale(0.85f), "Catala");
	m_fontBlanca.draw(150, m_idiomes[1].getButtonY() - 6, NFont::Scale(0.85f), "Castella");
	m_fontBlanca.draw(150, m_idiomes[2].getButtonY() - 6, NFont::Scale(0.85f), "Angles");

	m_drawCatala = m_idiomes[0].updateButtonRadioButtonArray(mousePosX, mousePosY, moousePressed, m_currentLanguage);
	m_drawCastella = m_idiomes[1].updateButtonRadioButtonArray(mousePosX, mousePosY, moousePressed, m_currentLanguage);
	m_drawAngles = m_idiomes[2].updateButtonRadioButtonArray(mousePosX, mousePosY, moousePressed, m_currentLanguage);
	
	//currentlanguage es util per saber el identificador numeral del idioma escollit.
	for (int i = 0; i < 3; i++)
	{
		if (i == m_currentLanguage) {
			m_idiomes[i].setActive();
		}
		else {
			m_idiomes[i].setNotActive();
		}
	}
	
	m_botoStart.drawButton();
	m_fontBlanca.draw(m_botoStart.getButtonX() + 50, m_botoStart.getButtonY() + 20, NFont::Scale(0.85f), "START");
	m_startPresionat = m_botoStart.updateButton(mousePosX, mousePosY, moousePressed);
	if (m_startPresionat) {
		languageCode = m_currentLanguage;
		m_DicOpen = dic.OpenDictionary(languageCode);
		if (m_DicOpen) {
			m_estatActual = PLAYING;
		}
	}
}


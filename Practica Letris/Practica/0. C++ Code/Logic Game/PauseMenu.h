#pragma once
#include "Button.h"
#include "joc.h"
class PauseMenu
{
	public:
		bool render(int mousePosX, int mousePosY, bool moousePressed, NFont font, bool& resetInPause, int& m_estatActual);
		PauseMenu();
		PauseMenu(string on, string off);
	private:
		Sprite backgroundSprite;
		Button returnButton;
		bool returnClicked;
		NFont m_fontBlanca;
};


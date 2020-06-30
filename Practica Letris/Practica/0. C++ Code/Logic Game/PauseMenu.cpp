#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	returnClicked = false;
}

PauseMenu::PauseMenu(string on, string off) 
{
	returnButton = Button(150, 300, 200, 90, "Return", "Go Back", on.c_str(), off.c_str());
	returnClicked = false;
}

bool PauseMenu::render(int mousePosX, int mousePosY, bool moousePressed, NFont font,bool &resetInPause,int& m_estatActual)
{
	font.draw(150,300, NFont::Scale(1.5f),"PAUSED");
	returnButton.drawButton();

	returnClicked = returnButton.updateButton(mousePosX, mousePosY, moousePressed);

	if (returnClicked) {
		resetInPause = true;
	}

	return resetInPause;
}


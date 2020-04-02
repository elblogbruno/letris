#include "..\..\0. C++ Code\Logic Game\Button.h"


bool Button::updateButtonRadioButton(int mousePosX, int mousePosY, bool mousePressed, int &id) {
	if (mousePosX > getButtonX() && mousePosX < getButtonX() + 90 &&
		mousePosY > getButtonY() && mousePosY < getButtonY() + 90 &&
		mousePressed)
	{
		setButtonStatus(!m_HasBeenClicked);
		id = getButtonIdNumber();
	}
	return getButtonStatus();
}
bool Button::updateButton(int mousePosX, int mousePosY, bool mousePressed) {
	if (mousePosX > getButtonX() && mousePosX < getButtonX() + 90 &&
		mousePosY > getButtonY() && mousePosY < getButtonY() + 90 &&
		mousePressed)
	{
		setButtonStatus(!m_HasBeenClicked);
	}
	return getButtonStatus();
}

int i = 0;
Button::Button(int x, int y, string id) {
	setButtonId(id);
	setButtonX(x);
	setButtonY(y);
	setButtonIdNumber(i);
	i++;
}
void Button::drawButton() {
	getButtonSprite().draw(getButtonX(), getButtonY());
}
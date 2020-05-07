#include "..\..\0. C++ Code\Logic Game\Button.h"
#include <iostream>
using namespace std;



bool Button::updateButtonRadioButton(int mousePosX, int mousePosY, bool mousePressed) {
	if (mousePosX > getButtonX() && mousePosX < getButtonX() + getWidth() &&
		mousePosY > getButtonY() && mousePosY < getButtonY() + getHeight() &&
		mousePressed) {
		
		
			if (isOn()) {
				setNotActive();
				m_IsButtonOn = false;
			}
			else {
				setActive();
				m_IsButtonOn = true;
			}
		

	}
	return m_IsButtonOn;
}
bool Button::updateButtonRadioButtonArray(int mousePosX, int mousePosY, bool mousePressed,int &id) {
	if (mousePosX > getButtonX() && mousePosX < getButtonX() + getWidth() &&
		mousePosY > getButtonY() && mousePosY < getButtonY() + getHeight() &&
		mousePressed) {

		
			if (isOn()) {
				setNotActive();
				m_IsButtonOn = false;
			}
			else {
				setActive();
				m_IsButtonOn = true;
				id = getButtonIdNumber();
			}
		
		
	}
	return m_IsButtonOn;
}

bool Button::updateButton(int mousePosX, int mousePosY, bool mousePressed) {
	bool m_shouldUpdate = false;
	if (mousePosX >= getButtonX() && mousePosX <= getButtonX() + getWidth() &&
		mousePosY >= getButtonY() && mousePosY <= getButtonY() + getHeight())
	{
		if (mousePressed) {
			setActive();
		}
		else {
			if (m_currentState == PRESSED) {
				m_shouldUpdate = true;
			}
			setNotActive();
		}
	}
	else 
	{
		setNotActive();
	}
	return m_shouldUpdate;
}


Button::Button() : currentFont("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255))
{
}
Button::Button(int x, int y, int width, int height, string tag, const string& pathOn, const string& pathOff,int id) {
	
	m_IsButtonOn = false;
	setButtonTag(tag);
	setButtonIdNumber(id);
	setButtonX(x);
	setButtonY(y);
	setNotActive();
	m_SpriteOff.create(pathOff.c_str());
	m_SpriteOn.create(pathOn.c_str());

	setWidth(width);
	setHeight(height);

	m_containsTitle = true;
}
Button::Button(int x, int y, int width, int height, string tag, string title, const string& pathOn, const string& pathOff) {
	
	m_IsButtonOn = false;
	setButtonTag(tag);
	setButtonTitle(title);

	setButtonX(x);
	setButtonY(y);
	setNotActive();
	m_SpriteOff.create(pathOff.c_str());
	m_SpriteOn.create(pathOn.c_str());

	setWidth(width);
	setHeight(height);

	m_containsTitle = true;
}
Button::Button(int x, int y,int width,int height,string tag,  const string& pathOn, const string& pathOff) {
	
	setButtonTag(tag);
	m_IsButtonOn = false;
	setButtonX(x);
	setButtonY(y);
	setNotActive();
	m_SpriteOff.create(pathOff.c_str());
	m_SpriteOn.create(pathOn.c_str());

	setWidth(width);
	setHeight(height);

	m_containsTitle = false;
}
void Button::drawButton() {
	switch (m_currentState)
	{
		case PRESSED:
			m_SpriteOn.draw(getButtonX(), getButtonY());
			break;
		case NORMAL:
			m_SpriteOff.draw(getButtonX(), getButtonY());
			break;
		default:
			break;
	}
	if (m_containsTitle) {
		currentFont.draw(getButtonX() / 2, getButtonY()/2, NFont::Scale(0.85f), getButtonTitle().c_str());
	}
}


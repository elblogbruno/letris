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

Button::Button() : m_currentFont("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255))
{
}
Button::Button(int x, int y, int width, int height, string tag, const string& pathOn, const string& pathOff,int id) {
	//Constructor per button en un array amb un titol o tag.

	m_IsButtonOn = false; //inicialitzem el button al seu estat normal
	setNotActive(); //inicialitzem el button al seu estat normal

	setButtonTag(tag); //inicialitzem el seu tag , que en el cas del tile sera la lletra que conte aquest button
	setButtonIdNumber(id); //li donem la seva identificacio numeral, molt util per quan tenim un array de RadioButtons distingibles (menu de seleccionar idioma)
	setButtonX(x); //inicialitzem la seva posicio en el eix x
	setButtonY(y); //inicialitzem la seva posicio en el eix y

	m_SpriteOff.create(pathOff.c_str()); //creem el sprite per l'estat off del button
	m_SpriteOn.create(pathOn.c_str()); //creem el sprite per l'estat on del button

	setWidth(width); //inicialitzem la seva width del button
	setHeight(height); //inicialitzem la seva height(altura) del button

	m_containsTitle = true;
}
Button::Button(int x, int y, int width, int height, string tag, string title, const string& pathOn, const string& pathOff) {
	//Constructor per button amb un titol o tag.

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
	
	//Constructor per button normal amb un  tag.

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
	if (m_containsTitle) { //si el boto conte un titol el dibuixem. 
		m_currentFont.draw(getButtonX() + 35, getButtonY()+10, NFont::Scale(1.0f), getButtonTitle().c_str());
	}
}


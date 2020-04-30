#pragma once
#include "../Graphic Lib/libreria.h"
#include <string>
#include "../Graphic Lib/NFont/NFont.h"
const int PRESSED = 0;
const int NORMAL = 1;

using namespace std;
class Button
{
public:
	typedef enum {
		NORMAL = 0,
		PRESSED,
		NONE
	} ButtonState;

	//Constructors del boto
	Button();
	Button(int x, int y, int width, int height, string tag, string title, const string& pathOn, const string& pathOff);
	Button(int x, int y, int width, int height, string tag,const string& pathOn, const string& pathOff);
	//Identificacio del boto, per exemple ficar que es el boto de start, el de sortir etc...
	void getButtonIdAsChar() {}; //retornar en char per escriure en la font.
	string getButtonTag() { return m_ButtonTag; };
	void setButtonTag(string id) { m_ButtonTag = id; };
	//Getters i settters de la posicio del boto en la pantalla...
	int getButtonX() { return posButton_X; };
	int getButtonY() { return posButton_Y; };
	void setButtonX(int x) {  posButton_X = x; };
	void setButtonY(int y) {  posButton_Y = y; };

	int getWidth() { return m_buttonWidth; };
	int getHeight() { return m_buttonHeight; };
	void setWidth(int width) { m_buttonWidth = width; };
	void setHeight(int height) { m_buttonHeight = height; };
	//Getter i setter del sprite del boto.
	//void setCurrentSprite(Sprite sprite) { m_CurrentSprite = sprite; };
	//Sprite getCurrentSprite() { return m_CurrentSprite; };

	bool isOn() { return m_IsButtonOn; };
	void setOn(bool isOn) { m_IsButtonOn = isOn; };
	//Getter i setter del titol del boto.
	void setButtonTitle(string title) { m_ButtonTitle = title; };
	string getButtonTitle() { return m_ButtonTitle; };
	//Actualitza el objecte button amb el seu estat del ratoli per saber si s'ha clicat o no. Aleshores actualitza l'estat del boto que podem accedir.
	bool updateButtonRadioButton(int mousePosX,int mousePosY, bool moousePressed);
	bool updateButton(int mousePosX, int mousePosY, bool moousePressed);

	void drawButton();

	//Getter i setter del status del boto.

private:
	string m_ButtonTag;
	string m_ButtonTitle;
	bool m_containsTitle;
	bool m_IsButtonOn;

	int posButton_X;
	int posButton_Y;
	int m_buttonWidth;
	int m_buttonHeight;

	ButtonState m_currentState;
	Sprite m_SpriteOn;
	Sprite m_SpriteOff;
	NFont currentFont;
};


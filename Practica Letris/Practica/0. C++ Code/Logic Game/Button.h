#pragma once
#include "../Graphic Lib/libreria.h"
#include <string>
#include "../Graphic Lib/NFont/NFont.h"

using namespace std;
class Button
{
public:
	typedef enum {
		NORMAL = 0,
		PRESSED,
		NONE
	} ButtonState; //Differents esttats possibles de un button.

	//Constructors del boto
	Button();
	Button(int x, int y, int width, int height, string tag, string title, const string& pathOn, const string& pathOff);
	Button(int x, int y, int width, int height, string tag,const string& pathOn, const string& pathOff);
	Button(int x, int y, int width, int height, string tag, const string& pathOn, const string& pathOff,int id);

	//Identificacio del boto, per exemple ficar que es el boto de start, el de sortir etc... o en el cas del tile la lletra que conte.
	void getButtonIdAsChar() {}; //retornar en char per escriure en la font.
	string getButtonTag() { return m_ButtonTag; };
	void setButtonTag(string id) { m_ButtonTag = id; };

	//Getters i settters de la posicio del boto en la pantalla...
	int getButtonX() { return m_posButton_X; };
	int getButtonY() { return m_posButton_Y; };
	void setButtonX(int x) { m_posButton_X = x; };
	void setButtonY(int y) { m_posButton_Y = y; };

	//Getters i setters de la width i la altura del button, utilitzar per calcular la area interactuable del button(hitbox)
	int getWidth() { return m_buttonWidth; };
	int getHeight() { return m_buttonHeight; };
	void setWidth(int width) { m_buttonWidth = width; };
	void setHeight(int height) { m_buttonHeight = height; };
	
	//Getter i setter del identificador numeral del boto. Util per a crear un arrray de buttons.
	int getButtonIdNumber() { return m_id; };
	void setButtonIdNumber(int id) { m_id = id; };

	void setActive() { m_currentState = PRESSED; };
	void setNotActive() { m_currentState = NORMAL; };


	bool isOn() { return m_IsButtonOn; };
	void setOn(bool isOn) { m_IsButtonOn = isOn; };
	//Getter i setter del titol del boto.
	void setButtonTitle(string title) { m_ButtonTitle = title; };
	string getButtonTitle() { return m_ButtonTitle; };
	//Actualitza el objecte button amb el seu estat del ratoli per saber si s'ha clicat o no. Aleshores actualitza l'estat del boto que podem accedir.
	bool updateButtonRadioButtonArray(int mousePosX, int mousePosY, bool moousePressed,int &id); //en aquest obtenim per parametre el seu identificador.
	bool updateButtonRadioButton(int mousePosX,int mousePosY, bool moousePressed);
	bool updateButton(int mousePosX, int mousePosY, bool moousePressed);

	//Funcio encarregada de dibuixar el sprite que porta aquest button i actualitzar el sprite depenent del estat del button.
	void drawButton();

	

private:
	string m_ButtonTag;
	string m_ButtonTitle;
	bool m_containsTitle;
	bool m_IsButtonOn;

	int m_posButton_X;
	int m_posButton_Y;
	int m_buttonWidth;
	int m_buttonHeight;
	int m_id;

	ButtonState m_currentState;
	Sprite m_SpriteOn;
	Sprite m_SpriteOff;
	NFont m_currentFont;
};


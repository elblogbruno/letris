#pragma once
#include "../Graphic Lib/libreria.h"

#include <string>
using namespace std;
class Button
{
public:
	//Constructors del boto
	Button() {};
	Button(int x, int y, string id);

	//Identificacio del boto, per exemple ficar que es el boto de start, el de sortir etc...
	void getButtonIdAsChar() {}; //retornar en char per escriure en la font.
	string getButtonId() { return m_ButtonId; };
	void setButtonId(string id) { m_ButtonId = id; };
	//Getters i settters de la posicio del boto en la pantalla...
	int getButtonX() { return posButton_X; };
	int getButtonY() { return posButton_Y; };
	void setButtonX(int x) {  posButton_X = x; };
	void setButtonY(int y) {  posButton_Y = y; };
	//Getter i setter del sprite del boto.
	void setButtonSprite(Sprite sprite) { m_CurrentSprite = sprite; };
	Sprite getButtonSprite() { return m_CurrentSprite; };
	//Actualitza el objecte button amb el seu estat del ratoli per saber si s'ha clicat o no. Aleshores actualitza l'estat del boto que podem accedir.
	bool updateButtonRadioButton(int mousePosX,int mousePosY, bool moousePressed, int &id);
	bool updateButton(int mousePosX, int mousePosY, bool moousePressed);
	void drawButton();
	//
	int getButtonIdNumber() { return m_id; };
	void setButtonIdNumber(int id) { m_id = id; };
	//Getter i setter del status del boto.
	void setButtonStatus(bool status) { m_HasBeenClicked = status; };
	bool getButtonStatus() { return m_HasBeenClicked; };
private:
	string m_ButtonId;
	bool m_HasBeenClicked;
	int m_id;
	int posButton_X;
	int posButton_Y;
	Sprite m_CurrentSprite;
};


#pragma once
#include "Button.h"
#include "joc.h"
class Tile
{
	public:
		Tile();
		Tile(string off, string on, string letterType);
		
		string getLetter() { return m_lletra.getButtonTag(); }; //Al crear el button li hem passat la seva lletra que es un "tag" del button.
		void drawLetter() { m_lletra.drawButton(); }; //cridem a la funcio dibuixar del button
		void setPosX(int x) { m_lletra.setButtonX(x); }; //canviem la posicio en l'eix x del button associat al tile
		void setPosY(int y) { m_lletra.setButtonY(y); }; //canviem la posicio en l'eix y del button associat al tile
		int getPosX() { return m_lletra.getButtonX(); }; //obtenim la posicio en l'eix x del button associat al tile
		int getPosY() { return m_lletra.getButtonY(); }; //obtenim la posicio en l'eix y del button associat al tile

		Tile(const Tile& v);
		Tile& operator=(const Tile& v); //Creacio del operador de assignació per arreglar possibles problemes al fer push_back en el vector i la copia dels sprites.



		int getLetterRow() { return m_row; }; //getter de la fila de la lletra
		int getLetterColumn() { return m_column; }; //getter de la columna de la lletra

		void setLetterRow(int row) { m_row = row; }; //setter de la fila de la lletra
		void setLetterColumn(int column) { m_column = column; }; //setter de la columna de la lletra

		void setLetterCoord(int column,int row); //Setter universal de les coordenades ( columna i fila) 

		bool hasReachedEnd(); //funció que retorna true si el tile ha arribat a la seva fila desti, que obtenim amb el getLetterRow()

		bool updateLetterStatus(int mousePosX, int mousePosY, bool clicked) { return m_lletra.updateButtonRadioButton(mousePosX, mousePosY, clicked); }; //crida a la funcio del button associat al tile que permet trobar si ha estat clickat o no

		/*string getPathOn() { return m_pathOn; };
		string getPathOff() { return m_pathOff; };*/

		void drawAuxiliar(int column); //em creat un sprite auxiliar per a dibuixar en la part inferior de la taula i aquesta funció ajuda a que li diguem la seva columna i ho dibuixi, la fila ja la coneixem sera sempre la mateixa.

		bool hasBeenSelected() { return m_hasBeenSelected; }; //Aquest bolea retorna si ha estat seleccuionat el tile cosa, que fa que el tile no arribi a funcionar exactament com un radiobutton que sempre estaria a true, si no que es torna true nomes quan ja sigut seleccionat.
		void setSelected(bool selected) { m_hasBeenSelected = selected; }; //setter del bolea anterior.

		void setActive(bool active);

	private:
		Button m_lletra;
		bool m_reachEnd;
		bool m_hasBeenSelected;
		
		//string m_pathOn;
		//string m_pathOff;

		Sprite m_aux_sprite;
		int m_row;
		int m_column;
		bool m_active;
};


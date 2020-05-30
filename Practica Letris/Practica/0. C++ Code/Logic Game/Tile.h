#pragma once
#include "Button.h"
#include "joc.h"
class Tile
{
	public:
		Tile();
		Tile(string off, string on, string letterType);
		
		string getLetter() { return m_lletra.getButtonTag(); };
		void drawLetter() { m_lletra.drawButton(); };
		void setPosX(int x) { m_lletra.setButtonX(x); };
		void setPosY(int y) { m_lletra.setButtonY(y); };

		int getLetterTargetRow() { return m_targetRow; };
		void setLetterTargetRow(int target) { m_targetRow = target; };

		int getLetterRow() { return m_row; };
		int getLetterColumn() { return m_column; };
		void setLetterRow(int row) { m_row = row; };
		void setLetterColumn(int column) { m_column = column; };


		void setLetterCoord(int column,int row);
		bool hasReachedEnd();
		int getPosX() { return m_lletra.getButtonX(); };
		int getPosY() { return m_lletra.getButtonY(); };
		bool updateLetterStatus(int mousePosX, int mousePosY, bool clicked) { return m_lletra.updateButtonRadioButton(mousePosX, mousePosY, clicked); };

	private:
		Button m_lletra;
		bool reachEnd;

		int m_row;
		int m_targetRow;
		int m_column;
		
};


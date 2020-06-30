#pragma once
#include ""
class PauseMenu
{
	public:
		void render(bool& isPaused, int&, int& m_estatActual);

	private:
		Button returnButton;
		Button resumeButton;

};


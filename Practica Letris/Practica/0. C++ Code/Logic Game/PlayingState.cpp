#include "PlayingState.h"

PlayingState::PlayingState() : fontBlanca("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255)),fontNegra("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255)),
fonsPlaying("./data/GUI/background_play.png"), timeBar("./data/GUI/Time_Bar.png")
{
	
	 botoPausaPlayContador = Button(375, 40, 90, 90, "contador",  "./data/GUI/Btn_Circle_Play_1_Normal.png", "./data/GUI/Btn_Circle_Pause_1_Normal.png");
	 botoEliminar = Button(375, 760, 194, 85, "eliminar",  "./data/GUI/Btn_Circle_Close_3_Pressed.png", "./data/GUI/Btn_Circle_Close_1_Normal.png");
	 botoCheck = Button(160, 760, 90, 90, "check",  "./data/GUI/Button_Pressed.png", "./data/GUI/Button_Normal.png");
	 //PLAYING VARIABLES
	 esGameOver = false;
	 drawMatrix = true;
	 pausarContador = false;
	 check = false;
	 eliminarMatriu = false;
	 drawTimer = true;
	 timerPartida = 0.0f;
	 matriuLletres = TileRenderer();

}



bool PlayingState::drawPlayingState(int mousePosX, int mousePosY, bool moousePressed, int &m_estatActual, double &deltaTime)
{
	//matriuLletres.Render(10, 8);
	fonsPlaying.draw(0, 0);
	timeBar.draw(120, 40);

	botoPausaPlayContador.drawButton();
	pausarContador = botoPausaPlayContador.updateButtonRadioButton(mousePosX, mousePosY, moousePressed);
	if (!pausarContador) {
		timerPartida += deltaTime; // Va sumant els segons
	}
	if (drawTimer) {
		fontNegra.draw(200, 50, NFont::Scale(0.85f), "%d", (int)timerPartida);
	}
	if (timerPartida > 10) {
		timerPartida = 0;
		drawTimer = true;
		esGameOver = true;
		m_estatActual = GAME_OVER; //Han passat 10 segons, llavors canvia a la pantalla de GameOver
	}
	
	botoCheck.drawButton();
	fontBlanca.draw(botoCheck.getButtonX() + 10, botoCheck.getButtonY(), NFont::Scale(1.5f), "CHECK");
	check = botoCheck.updateButton(mousePosX, mousePosY, moousePressed);


	botoEliminar.drawButton();
	eliminarMatriu = botoEliminar.updateButton(mousePosX, mousePosY, moousePressed);

	if (eliminarMatriu) {
		drawMatrix = false;
	}
	if (check) {
		drawMatrix = true;
	}

	if (drawMatrix) {
		matriuLletres.Render(10, 8);
	}
	
	
	return esGameOver;
}


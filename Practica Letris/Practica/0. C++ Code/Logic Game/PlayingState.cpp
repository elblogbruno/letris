#include "PlayingState.h"
#include <iostream>
PlayingState::PlayingState() : m_fontBlanca("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255)), m_fontNegra("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255)),
m_fonsPlaying("./data/GUI/background_play.png"), m_timeBar("./data/GUI/Time_Bar.png")
{
	//Inicialitzem els buttons necesaris pel joc.
	m_botoPausaPlayContador = Button(375, 40, 90, 90, "contador",  "./data/GUI/Btn_Circle_Play_1_Normal.png", "./data/GUI/Btn_Circle_Pause_1_Normal.png");
	m_botoEliminar = Button(375, 760, 194, 85, "eliminar",  "./data/GUI/Btn_Circle_Close_3_Pressed.png", "./data/GUI/Btn_Circle_Close_1_Normal.png");
	m_botoCheck = Button(160, 760, 200, 90, "check",  "./data/GUI/Button_Pressed.png", "./data/GUI/Button_Normal.png");
	 //PLAYING VARIABLES
	m_resetInPause = false;
	m_esGameOver = false;
	m_drawMatrix = true;
	m_pausarContador = false;
	m_check = false;
	m_eliminarMatriu = false;
	m_drawTimer = true;
	m_timerPartida = 0.0f;
	//Tile renderer
	m_matriuLletres = TileRenderer(); // inicialitzem la matriu de lletres.
	//PAUSE MENU
	m_PauseMenu = PauseMenu("./data/GUI/Button_Pressed.png", "./data/GUI/Button_Normal.png"); //Inicialitzem el menu de pausa

}



bool PlayingState::drawPlayingState(int mousePosX, int mousePosY, bool moousePressed, int &m_estatActual, double &deltaTime, DictionaryHandler& dictionaryHandler)
{
		m_fonsPlaying.draw(0, 0);
		m_timeBar.draw(120, 40);

		m_botoPausaPlayContador.drawButton();
		m_pausarContador = m_botoPausaPlayContador.updateButtonRadioButton(mousePosX, mousePosY, moousePressed);

		m_matriuLletres.Render(mousePosX, mousePosY, moousePressed, deltaTime, m_pausarContador, dictionaryHandler.hasBeenLoaded(), m_timerPartida);
		if (!m_pausarContador && !m_resetInPause) {
			m_botoCheck.drawButton();
			m_fontBlanca.draw(m_botoCheck.getButtonX() + 10, m_botoCheck.getButtonY(), NFont::Scale(1.5f), "CHECK");
			m_botoEliminar.drawButton();

			m_timerPartida += deltaTime; // Va sumant els segons que van passant i li passaem aquesta variable a la matriu per calcular la velocitat basant-nos en el temps.
			m_check = m_botoCheck.updateButton(mousePosX, mousePosY, moousePressed);
			m_eliminarMatriu = m_botoEliminar.updateButton(mousePosX, mousePosY, moousePressed);

			if (m_eliminarMatriu) {
				m_matriuLletres.resetPossibleWord(); //Si cliquem la X resetejem la paraula seleccionada
			}
			if (m_check) {
				string word = m_matriuLletres.getPossibleWord();
				cout << word << endl;
				bool existOnDictionary = dictionaryHandler.checkWordOnDictionary(word);
				m_matriuLletres.updateMatrixLetters(existOnDictionary, deltaTime);
			}
		}
		else {
			m_resetInPause = m_PauseMenu.render(mousePosX, mousePosY, moousePressed, m_fontBlanca, m_resetInPause,m_estatActual);
			if (m_resetInPause) {
				m_matriuLletres.resetBoard();
				dictionaryHandler.resetDictionary();
				m_timerPartida = 0;
				m_pausarContador = false;
				m_resetInPause = false;
				m_botoPausaPlayContador.setOn(false);
				m_botoPausaPlayContador.setNotActive();
				m_estatActual = MAIN_MENU;
				//resetejem tot el estat de cada boto del menu per quan tornem a entrar comenci tot de nou.
			}
		}


		
		if (m_drawTimer) {
			m_fontNegra.draw(200, 55, NFont::Scale(0.85f), "%d", (int)m_timerPartida);
			if (m_matriuLletres.getPoints() >= 0) {
				m_fontNegra.draw(235, 55, NFont::Scale(0.85f), "Punts: %d", m_matriuLletres.getPoints());
			}
		}

		if (m_matriuLletres.isFull()) { //si el tauler esta ple em perdut la partida.
			m_matriuLletres.resetBoard(); //resetejem el tauler
			dictionaryHandler.resetDictionary(); //resetejem el diccionari de aquesta manera l'usuari pot escollir un nou idioma
			m_timerPartida = 0; //Resetejem el timer
			m_esGameOver = true;
			m_estatActual = GAME_OVER; //Han passat 10 segons, llavors canvia a la pantalla de GameOver
		}

		

	return m_esGameOver;
}



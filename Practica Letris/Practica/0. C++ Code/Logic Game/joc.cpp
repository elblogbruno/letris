#include "joc.h"
#include "../Graphic Lib/NFont/NFont.h"
#include "Button.h"
#include <iostream>
using namespace std;



//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc()
{
	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(MIDA_X, MIDA_Y);
	//Mostrem la finestra grafica
	pantalla.show();

	//------------------------------------
	//-----Introducci� a la pr�ctica -----
	//
	//  TODO:   Aqu� heu de crear els sprites/fonts i
	//          totes les variables necess�ries per
	//          treballar en el bucle principal de
	//          sota (do...while).
	//
	//------------------------------------

	//-----TODO 1
	//Crear un timer i mostrar per pantalla el temps passat
	
	NFont fontBlanca("data/Fonts/FreeSans.ttf", 30, NFont::Color(255, 255, 255, 255));
	NFont fontNegra("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255));
	
	//-----TODO 1


	//-----TODO 2
	//-Pintar una matriu de 4x4 amb el sprite de la lletra 'a' de letris
	//-Pintar un sprite de bot� i cada cop que es clica pintar o deixar de pintar el bot�

	//MAIN_MENU VARIABLES
	bool drawCatala = false;
	bool drawCastella = false;
	bool drawAngles = false;
	bool startPresionat = false;
	//PLAYING VARIABLES
	bool drawMatrix = false;
	bool pausarContador = false;
	bool check = false;
	bool eliminarMatriu = false;
	bool drawTimer = true;
	//GAME OVER VARIABLES
	bool esGameOver = false;


	// Variables per els diferents timers.
	float timerPartida = 0.0f; 
	float timerBoto = 0.0f; //aquest timer estava pensat per la animacio del boto quan es fa click en ell.
	float timerGameOver = 0.0f;
	//
	int estatMatriu = 0; //Variable que guarda l'estat de la matriu de lletres MOSTRA_MATRIU = 0 i AMAGAR_MATRIU = 1;
	int m_estatActual = 0; //Variable que guarda l'estat del menu de lletres MAIN_MENU = 0, PLAYING = 1,PAUSE = 2 i GAME_OVER = 3;
	int m_llenguatjeActual = 0; //Variable que guarda el llenguatje actual del menu CATALA = 0, CASTELLA = 1 i ANGLES = 2;
	//
	//sprite dels radio-buttons
	Sprite botoEscollirIdiomaNoEscollit("./data/GUI/Checkbox_Disabled.png");
	Sprite botoEscollirIdiomaEscollit("./data/GUI/Checkbox_Enabled.png");

	//start
	Sprite botoStartPresionat("./data/GUI/Button_Pressed.png");
	Sprite botoStartNoPresionar("./data/GUI/Button_Normal.png");

	//contador
	Sprite timeBar("./data/GUI/Time_Bar.png");
	Sprite botoContadorPausa("./data/GUI/Btn_Circle_Pause_1_Normal.png");
	Sprite botoContadorPlay("./data/GUI/Btn_Circle_Play_1_Normal.png");

	Sprite botoEliminarPresionat("./data/GUI/Btn_Circle_Close_3_Pressed.png");
	Sprite botoEliminarNoPresionat("./data/GUI/Btn_Circle_Close_1_Normal.png");

	Sprite botoCheckPresionat("./data/GUI/Button_Pressed.png");
	Sprite botoCheckNoPresionat("./data/GUI/Button_Normal.png");

	//fons de cada menu
	Sprite fonsMenuInicial("./data/GUI/MainMenu_BG.png");
	Sprite fonsPlaying("./data/GUI/background_play.png");
	Sprite fonsFinalPartida("./data/GUI/GameOver.png");
	
	//sprite de les lletres
	Sprite lletraA("./data/Letters/white_0.png");
	Sprite lletraB("./data/Letters/white_1.png");
	Sprite lletraC("./data/Letters/white_2.png");
	Sprite lletraD("./data/Letters/white_3.png");
	Sprite lletraE("./data/Letters/white_4.png");
	Sprite lletraF("./data/Letters/white_5.png");
	Sprite lletraG("./data/Letters/white_6.png");
	Sprite lletraH("./data/Letters/white_7.png");

	Sprite lletres[8] = { lletraA,lletraB,lletraC,lletraD,lletraE,lletraF,lletraG,lletraH};
	
	/*string idiomesDisponiblesPosicioTitol[3] = { "Catala", "Castella","Angles" };
	int idiomesDisponiblesPosicio[3]= { 100,130,160 };
	Button idiomesDisponiblesButtons[3];*/
	/*for (int i = 0; i < 3; i++)
	{
		idiomesDisponiblesButtons[i] = Button(100, idiomesDisponiblesPosicio[i], idiomesDisponiblesPosicioTitol[i]);
	}*/
	
	//Botons creats amb la classe Button.
	Button botoCatala = Button(100, 120, "Catala");
	Button botoCastella = Button(100, 170, "Castella");
	Button botoAngles = Button(100, 220, "Angles");
	Button botoStart = Button(150,725, "START");
	Button botoPausaPlayContador = Button(375, 40, "Contador");
	Button botoEliminar = Button(375, 760, "Eliminar");
	Button botoCheck = Button(160, 760, "CHECK");

	
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;




	do
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		// Captura tots els events de ratol� i teclat de l'ultim cicle
		pantalla.processEvents();

		bool mouseStatus = Mouse_getBtnLeft();
		bool moousePressed = Mouse_getButLeft();

		int mousePosX = Mouse_getX();
		int mousePosY = Mouse_getY();

		
		switch (m_estatActual)
		{
			case MAIN_MENU:

				//Dibuixa  el fons de pantalla.
				fonsMenuInicial.draw(0,0);
				//Dibuixa el boto sense escollir per default
				botoEscollirIdiomaNoEscollit.draw(botoCatala.getButtonX(), botoCatala.getButtonY());
				botoEscollirIdiomaNoEscollit.draw(botoCastella.getButtonX(), botoCastella.getButtonY());
				botoEscollirIdiomaNoEscollit.draw(botoAngles.getButtonX(), botoAngles.getButtonY());
				//Dibuixa el text a costat de cada boto. TODO : En lloc de hardcoded, demanar com escriure char o string en NFONT
				fontBlanca.draw(150, botoCatala.getButtonY() - 6, NFont::Scale(0.85f),"Catala");
				fontBlanca.draw(150, botoCastella.getButtonY() - 6, NFont::Scale(0.85f), "Castella");
				fontBlanca.draw(150,botoAngles.getButtonY() - 6, NFont::Scale(0.85f), "Angles");
				//
				drawCatala = botoCatala.updateButtonRadioButton(mousePosX, mousePosY, moousePressed, m_llenguatjeActual);
				drawCastella = botoCastella.updateButtonRadioButton(mousePosX, mousePosY, moousePressed, m_llenguatjeActual);
				drawAngles = botoAngles.updateButtonRadioButton(mousePosX, mousePosY, moousePressed, m_llenguatjeActual);
				switch (m_llenguatjeActual)
				{
					case CATALA:
						botoEscollirIdiomaEscollit.draw(botoCatala.getButtonX(), botoCatala.getButtonY());
						break;
					case CASTELLA:
						botoEscollirIdiomaEscollit.draw(botoCastella.getButtonX(), botoCastella.getButtonY());
						break;
					case ANGLES:
						botoEscollirIdiomaEscollit.draw(botoAngles.getButtonX(), botoAngles.getButtonY());
						break;
				default:
					break;
				}
				botoStartNoPresionar.draw(botoStart.getButtonX(), botoStart.getButtonY());
				fontBlanca.draw(botoStart.getButtonX()+50, botoStart.getButtonY()+20, NFont::Scale(0.85f), "START");
				startPresionat = botoStart.updateButton(mousePosX, mousePosY, moousePressed);
				if (startPresionat) {
					botoStartPresionat.draw(botoStart.getButtonX(), botoStart.getButtonY());
					m_estatActual = PLAYING;
				}
				break;
			case PLAYING:
				fonsPlaying.draw(0, 0);
				timeBar.draw(120,40);
				
				pausarContador = botoPausaPlayContador.updateButton(mousePosX, mousePosY, moousePressed);
				if (!pausarContador) {
					timerPartida += deltaTime; // Va sumant els segons
					botoContadorPausa.draw(botoPausaPlayContador.getButtonX(), botoPausaPlayContador.getButtonY());
				}
				else {
					botoContadorPlay.draw(botoPausaPlayContador.getButtonX(), botoPausaPlayContador.getButtonY());			
				}
				
				if (drawTimer) {
					fontNegra.draw(200, 50, NFont::Scale(0.85f), "%d", (int)timerPartida);
				}
				if (timerPartida > 10) {
					drawTimer = false;
					m_estatActual = GAME_OVER; //Han passat 10 segons, llavors canvia a la pantalla de GameOver
					esGameOver = true;
				}
				
				check = botoCheck.updateButton(mousePosX, mousePosY, moousePressed);

				eliminarMatriu = botoEliminar.updateButton(mousePosX, mousePosY, moousePressed);
				
				if (eliminarMatriu) {
					botoEliminarNoPresionat.draw(botoEliminar.getButtonX(), botoEliminar.getButtonY());
					estatMatriu = AMAGAR_MATRIU;
				}
				else {
					botoEliminarPresionat.draw(botoEliminar.getButtonX(), botoEliminar.getButtonY());
				}
				if (check) {
					botoCheckNoPresionat.draw(botoCheck.getButtonX(), botoCheck.getButtonY());
					estatMatriu = MOSTRA_MATRIU;
				}
				else {
					botoCheckPresionat.draw(botoCheck.getButtonX(), botoCheck.getButtonY());
				}
				fontBlanca.draw(botoCheck.getButtonX() + 10, botoCheck.getButtonY(), NFont::Scale(1.5f), "CHECK");
				switch (estatMatriu)
				{
					case MOSTRA_MATRIU:
						drawMatrix = true;
						break;
					case AMAGAR_MATRIU:
						drawMatrix = false;
						break;
				}
				
				//cout << "CHECK: " << check << "Eliminar Matriu: " << eliminarMatriu << "Draw Matriu: " << drawMatrix;
				if (drawMatrix) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 8; j++) {
							int posX = 10 + (j*TILE_WIDTH + 30);
							int posY = 100 + (i*TILE_WIDTH + 50);
							lletres[j].setScale(1);
							lletres[j].draw(posX, posY);
						}
					}
				}
				break;
			case GAME_OVER:
				//NO SABEM PER QUINA RAO, SI FEM QUE COMENÇI EL JOC AMB LA PANTALLA DE GAME OVER, FUNCIONA CORRECTAMENT, A DIFERENCIA DE INICIALITZARLA QUAN TOCA
				// ON TROBEM QUE LA PANTALLA TORNA AL MAIN MENU PER UNA MILESIMA DE SEGON I RETORNA A GAME OVER.
				fonsFinalPartida.draw(0, 0);
				if (esGameOver) {
					timerGameOver += deltaTime;
					//fontNegra.draw(200, 50, NFont::Scale(0.85f), "%d", (int)timerGameOver);
				}	
				if (timerGameOver > 5.0f) {
					esGameOver = false;
					timerGameOver = 0;
					m_estatActual = MAIN_MENU;
				}
				break;
			default:
				break;
		}


		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

}

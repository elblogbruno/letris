#ifndef GAMESTATE_H
#define GAMESTATE_H
class GameState
{
public:
	typedef enum {
		ENGLISH = 0,
		SPANISH,
		CATALAN
	} Language;
	enum LetrisGameState {
		MAIN_MENU = 0,
		PLAYING = 1,
		PAUSE = 2,
		GAME_OVER = 3
	};
private:

};
#endif

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include "GameScreen.h"
#include "MenuScreen.h"

class ScreenManager
{
private:
	int gameState;
	bool exitState;
	bool newGame = false;
	GameScreen *game;
	MenuScreen *menu;
	ScreenManager();

public:
	enum GAMESTATE{ MENU, PLAYING, DIED, HIGHSCORES};
	static ScreenManager & getInstance();
	~ScreenManager();
	void changeGameState(int newState);

	void addGameScreen(GameScreen *gameScreen) { game = gameScreen; }
	void addMenuScreen(MenuScreen *menuScreen) { menu = menuScreen; }
	//void addGameScreen(GameScreen *gameScreen) { game = gameScreen; }

	void update();
	void draw();

	void setNewGame() { newGame = true; }
	int getScreenState() { return gameState; }
	bool getExitState(){ return exitState; }

	//Can't use these methods to accidentally copy the input manager.
	ScreenManager(ScreenManager const&) = delete;
	void operator=(ScreenManager const&) = delete;
};
#endif
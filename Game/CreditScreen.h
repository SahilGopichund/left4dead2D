#ifndef CREDITSCREEN_H
#define CREDITSCREEN_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "InputManager.h"

class CreditScreen
{
private:
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font24 = NULL;
	ALLEGRO_FONT *font72 = NULL;
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	bool returnToMenu;
public:
	CreditScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~CreditScreen();
	void update();
	void draw();
	bool getReturnToMenu() { return returnToMenu; }
	void setReturnToMenu() { returnToMenu = false; }
};
#endif


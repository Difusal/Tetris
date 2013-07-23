#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Tetris.h"
#include "MenuButton.h"

class GameOverState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	unsigned int score;

	vector<MenuButton*> buttons;
	MenuButton *screenTitle;
	MenuButton *playAgainButton;
	MenuButton *mainMenuButton;

	ALLEGRO_BITMAP *background;
};
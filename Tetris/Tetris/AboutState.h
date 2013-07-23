#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Tetris.h"
#include "MenuButton.h"

class AboutState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	vector<MenuButton*> buttons;
	MenuButton *screenTitle;
	MenuButton *mainMenuButton;

	ALLEGRO_BITMAP *background;
};
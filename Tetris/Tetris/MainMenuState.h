#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Tetris.h"
#include "MenuButton.h"

class MainMenuState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	double backgroundSourceX;

	vector<MenuButton*> buttons;
	MenuButton *menuTitle;
	MenuButton *playButton;
	MenuButton *howToPlayButton;
	MenuButton *optionsButton;
	MenuButton *aboutButton;

	ALLEGRO_BITMAP *background;
};
#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Tetris.h"
#include "Button.h"

class PlayingState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	Button *exitButton;
	vector<Button*> buttons;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_BITMAP *background;
};
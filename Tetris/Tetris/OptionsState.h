#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Tetris.h"
#include "MenuButton.h"

class OptionsState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

private:
	bool newKeyHasBeenSet;
	int *ptrToKeyBeingSet;

	vector<MenuButton*> buttons;
	MenuButton *screenTitle;
	MenuButton *setKeyToMoveLeftButton;
	MenuButton *setKeyToMoveRightButton;
	MenuButton *setKeyToRotateLeftButton;
	MenuButton *setKeyToRotateRightButton;
	MenuButton *setKeyToSoftDropButton;
	MenuButton *setKeyToHardDropButton;
	MenuButton *setKeyToHoldPieceButton;
	MenuButton *loadDefaultsButton;
	MenuButton *mainMenuButton;

	ALLEGRO_BITMAP *background;
};
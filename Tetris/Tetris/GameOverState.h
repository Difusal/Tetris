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

	bool fileExists(const string &filename);
	vector<unsigned int> readTop5FromFile();
	void addDataToTop5AndWriteItToFile(unsigned int Data);

private:
	unsigned int score;
	vector<unsigned int> top5;

	vector<MenuButton*> buttons;
	MenuButton *screenTitle;
	MenuButton *playAgainButton;
	MenuButton *mainMenuButton;

	ALLEGRO_BITMAP *background;
};
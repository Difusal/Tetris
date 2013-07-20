#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Tetris.h"
#include "Button.h"
#include "Piece.h"
#include "Board.h"

class PlayingState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

	void UpdatePiecePosition(ALLEGRO_EVENT * ev);

private:
	bool pieceLocked;
	int lockDelayCounter;

	Board *board;

	Piece *nextPiece;
	Piece *fallingPiece;
	Piece *holdPiece;
	Piece *tempPiece;

	Button *exitButton;
	vector<Button*> buttons;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_BITMAP *background;
};
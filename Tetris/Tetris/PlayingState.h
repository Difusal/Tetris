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

	void PositionPiecesCorrectlyOnEachBox();
	void PositionFallingPieceOnBoardTop();
	void ComputePlayerInput(ALLEGRO_EVENT * ev);

	void MovePieceRightIfPossible();
	void MovePieceLeftIfPossible();

	unsigned int score;
	unsigned int level;

private:
	bool pieceLocked;
	bool pieceAlreadyHolded;
	bool pieceMovementDelayAfterPressingKeyContinuouslyOver;
	bool rightArrowPressedContinuously;
	bool leftArrowPressedContinuously;
	int softDropSpeedCounter;
	int lockDelayCounter;
	int pieceSidewaysMovementDelayCounter;

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
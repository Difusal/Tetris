#pragma once

#include "stdIncludes.h"
#include "Tetris.h"
#include "Piece.h"

struct AnimElement {
	int y1;
	int frame;
};

class Board
{
public:
	Board();

	bool GameOver();
	bool PieceCanMoveRight(Piece *piece);
	bool PieceCanMoveLeft(Piece *piece);
	bool PieceIsInsideMainMatrixAfterRotating(Piece *piece);
	void Update(unsigned int &Score, unsigned int &Level, bool &LeveledUp, bool &FirstPieceLocked);
	bool UpdatePieceLockedState(Piece *piece);
	void MergePiece(Piece *piece);
	void Draw();

	~Board();

private:
	vector<vector<Cell> > matrix;
	vector<AnimElement> clearedLineAnimationCoords;

	ALLEGRO_BITMAP *yellow_cell;
	ALLEGRO_BITMAP *blue_cell;
	ALLEGRO_BITMAP *green_cell;
	ALLEGRO_BITMAP *red_cell;
	ALLEGRO_BITMAP *purple_cell;
};
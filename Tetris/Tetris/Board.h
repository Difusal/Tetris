#pragma once

#include "stdIncludes.h"
#include "Tetris.h"
#include "Piece.h"

class Board
{
public:
	Board();

	bool GameOver();
	bool PieceCanMoveRight(Piece *piece);
	bool PieceCanMoveLeft(Piece *piece);
	bool PieceIsInsideMainMatrixAfterRotating(Piece *piece);
	void Update(unsigned int &Score, unsigned int &Level);
	bool UpdatePieceLockedState(Piece *piece);
	void MergePiece(Piece *piece);
	void Draw();

	~Board();

private:
	vector<vector<Cell> > matrix;

	ALLEGRO_BITMAP *yellow_cell;
	ALLEGRO_BITMAP *blue_cell;
	ALLEGRO_BITMAP *green_cell;
	ALLEGRO_BITMAP *red_cell;
	ALLEGRO_BITMAP *purple_cell;
};
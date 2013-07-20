#pragma once

#include "stdIncludes.h"

class Piece
{
public:
	Piece();
	Piece(int PieceType);

	void RotateRight();
	void RotateLeft();

	void PositionOnBoardTop();
	void PositionOnNextPieceBox();
	void PositionOnHoldBox();

	void Draw();

	~Piece();

	int type;
	int color;
	int x_pos, y_pos;
	int width, height;

	vector<vector<int> > matrix;

private:
	ALLEGRO_BITMAP *pattern;
};
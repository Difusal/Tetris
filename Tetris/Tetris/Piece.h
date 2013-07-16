#pragma once

#include "stdIncludes.h"

class Piece
{
public:
	Piece();
	Piece(int PieceType);

	void Update();
	void Draw();

	~Piece();

private:
	int type;
	vector<vector<int> > matrix;

	int x_pos, y_pos;

	ALLEGRO_BITMAP *pattern;
};
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

	int x_pos, y_pos;
	int width, height;

private:
	int type;
	vector<vector<int> > matrix;
	
	ALLEGRO_BITMAP *pattern;
};
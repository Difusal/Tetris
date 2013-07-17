#include "Piece.h"
#include "Tetris.h"

Piece::Piece()
{
	type = random_number(0, 6);

	switch (type)
	{
	default:
	case I:
		{
			/* making piece matrix */
			vector<int> temp (1, 1);
			matrix.push_back(temp);
			matrix.push_back(temp);
			matrix.push_back(temp);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = BlueCell;
			pattern = al_load_bitmap(BluePattern);

			break;
		}
	case J:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(1);
			temp.push_back(0);
			temp.push_back(0);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = GreenCell;
			pattern = al_load_bitmap(GreenPattern);

			break;
		}
	case L:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(0);
			temp.push_back(0);
			temp.push_back(1);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = GreenCell;
			pattern = al_load_bitmap(GreenPattern);

			break;
		}
	case O:
		{
			/* making piece matrix */
			vector<int> temp (2, 1);
			matrix.push_back(temp);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = YellowCell;
			pattern = al_load_bitmap(YellowPattern);

			break;
		}
	case S:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(0);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(0);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = RedCell;
			pattern = al_load_bitmap(RedPattern);

			break;
		}
	case T:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(0);
			temp.push_back(1);
			temp.push_back(0);
			matrix.push_back(temp);

			temp.clear();
			for (unsigned int i = 0; i < 3; i++)
				temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = PurpleCell;
			pattern = al_load_bitmap(PurplePattern);

			break;
		}
	case Z:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(0);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(0);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = RedCell;
			pattern = al_load_bitmap(RedPattern);

			break;
		} 
	}

	x_pos = 4;
	y_pos = -(int)matrix.size();

	width = matrix[0].size();
	height = matrix.size();
}

Piece::Piece(int PieceType)
{
	type = PieceType;

	switch (type)
	{
	default:
	case I:
		{
			/* making piece matrix */
			vector<int> temp (1, 1);
			matrix.push_back(temp);
			matrix.push_back(temp);
			matrix.push_back(temp);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = BlueCell;
			pattern = al_load_bitmap(BluePattern);

			break;
		}
	case J:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(1);
			temp.push_back(0);
			temp.push_back(0);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = GreenCell;
			pattern = al_load_bitmap(GreenPattern);

			break;
		}
	case L:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(0);
			temp.push_back(0);
			temp.push_back(1);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = GreenCell;
			pattern = al_load_bitmap(GreenPattern);

			break;
		}
	case O:
		{
			/* making piece matrix */
			vector<int> temp (2, 1);
			matrix.push_back(temp);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = YellowCell;
			pattern = al_load_bitmap(YellowPattern);

			break;
		}
	case S:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(0);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(0);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = RedCell;
			pattern = al_load_bitmap(RedPattern);

			break;
		}
	case T:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(0);
			temp.push_back(1);
			temp.push_back(0);
			matrix.push_back(temp);

			temp.clear();
			for (unsigned int i = 0; i < 3; i++)
				temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = PurpleCell;
			pattern = al_load_bitmap(PurplePattern);

			break;
		}
	case Z:
		{
			/* making piece matrix */
			vector<int> temp;
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(0);
			matrix.push_back(temp);

			temp.clear();
			temp.push_back(0);
			temp.push_back(1);
			temp.push_back(1);
			matrix.push_back(temp);

			/* setting piece pattern */
			color = RedCell;
			pattern = al_load_bitmap(RedPattern);

			break;
		} 
	}

	x_pos = 4;
	y_pos = -(int)matrix.size();

	width = matrix[0].size();
	height = matrix.size();
}


void Piece::Update()
{
	
}

void Piece::Draw()
{
	int x_correction = 275;

	if (x_pos > 9)
		x_correction = 265;
	else if (x_pos < 0)
		x_correction = 285;

	for (unsigned int i = 0; i < matrix.size(); i++)
		for (unsigned int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] == 1 && 50 <= 50 + y_pos*25 + i*25)
				al_draw_bitmap(pattern, x_correction + x_pos*25 + j*25, 50 + y_pos*25 + i*25, NULL);
}


void Piece::PositionOnBoardTop()
{
	x_pos = 4;
	y_pos = -(int)matrix.size();
}

void Piece::PositionOnHoldBox()
{
	switch (type)
	{
	default:
	case I:
		x_pos = -7;
		y_pos = 0;
		break;
	case O:
	case J:
	case Z:
		x_pos = -7;
		y_pos = 1;
		break;
	case L:
	case S:
	case T:
		x_pos = -8;
		y_pos = 1;
		break;
	}
}

void Piece::PositionOnNextPieceBox()
{
	switch (type)
	{
	default:
	case I:
		x_pos = 15;
		y_pos = 0;
		break;
	case O:
	case J:
	case Z:
		x_pos = 15;
		y_pos = 1;
		break;
	case L:
	case S:
	case T:
		x_pos = 14;
		y_pos = 1;
		break;
	}
}


Piece::~Piece()
{
	al_destroy_bitmap(pattern);
}
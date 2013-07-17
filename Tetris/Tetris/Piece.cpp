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
	for (unsigned int i = 0; i < matrix.size(); i++)
		for (unsigned int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] == 1 && 50 <= 50 + y_pos*25 + i*25)
				al_draw_bitmap(pattern, 275 + x_pos*25 + j*25, 50 + y_pos*25 + i*25, NULL);
}

Piece::~Piece()
{
}
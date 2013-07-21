#include "Board.h"
#include "PlayingState.h"

Board::Board() {
	/* loading cell bitmaps */
	yellow_cell = al_load_bitmap(YellowPattern);
	purple_cell = al_load_bitmap(PurplePattern);
	green_cell = al_load_bitmap(GreenPattern);
	blue_cell = al_load_bitmap(BluePattern);
	red_cell = al_load_bitmap(RedPattern);

	vector<Cell> temp;
	Cell tempCell = { 0, YellowCell };
	for (unsigned int i = 0; i < 10; i++)
		temp.push_back(tempCell);
	for (unsigned int i = 0; i < 22; i++)
		matrix.push_back(temp);
}


bool Board::GameOver()
{
	for (unsigned int i = 0; i < 2; i++)
		for (unsigned int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j].isOccupied)
				return true;

	return false;
}

bool Board::PieceCanMoveRight(Piece *piece) {
	for (unsigned int line = 0; line < piece->matrix.size(); line++) {
		int scan_row = piece->matrix[line].size()-1;
		while (scan_row >= 0) {
			if (piece->matrix[line][scan_row] &&
				matrix[piece->y_pos + line][piece->x_pos + scan_row + 1].isOccupied)
				return false;
			else
				scan_row--;
		}
	}

	return true;
}

bool Board::PieceCanMoveLeft(Piece *piece) {
	for (unsigned int line = 0; line < piece->matrix.size(); line++) {
		unsigned int scan_row = 0;
		while (scan_row < piece->matrix[0].size()) {
			if (piece->matrix[line][scan_row] &&
				matrix[piece->y_pos + line][piece->x_pos + scan_row - 1].isOccupied)
				return false;
			else
				scan_row++;
		}
	}

	return true;
}

bool Board::PieceIsInsideMainMatrixAfterRotating( Piece *piece ) {
	for (unsigned int line = 0; line < piece->matrix.size(); line++) {
		int scan_row = piece->matrix[line].size()-1;
		while (scan_row >= 0) {
			if (piece->matrix[line][scan_row] &&
				matrix[piece->y_pos + line][piece->x_pos + scan_row].isOccupied)
				return true;
			else
				scan_row--;
		}
	}

	return false;
}


void Board::Update(unsigned int &Score, unsigned int &Level, bool &LeveledUp) {
	int lines_cleared = 0;

	for (unsigned int i = 0; i < matrix.size(); i++) {
		for (unsigned int j = 0; j < matrix[i].size(); j++) {
			if (!matrix[i][j].isOccupied)
				break;
			else if (matrix[i][j].isOccupied && j == matrix[i].size()-1) {
				/* incrementing number of lines cleared */
				lines_cleared++;

				/* erasing full line */
				matrix.erase(matrix.begin()+i);

				/* saving details to play line cleared animation */
				AnimElement tempAnimElem = { i*25, 0 };
				clearedLineAnimationCoords.push_back(tempAnimElem);

				/* making up to the erased lines */
				vector<Cell> temp;
				Cell tempCell = { 0, YellowCell };
				for (unsigned int i = 0; i < 10; i++)
					temp.push_back(tempCell);
				matrix.insert(matrix.begin(), temp);
			}
		}
	}

	if (lines_cleared != 0)
		cout << "! " << lines_cleared << " cleared !" << endl;

	int points_for_x_lines = 0;
	switch (lines_cleared)
	{
	default:
	case 0:
		points_for_x_lines = 0;
		break;
	case 1:
		points_for_x_lines = 40;
		break;
	case 2:
		points_for_x_lines = 100;
		break;
	case 3:
		points_for_x_lines = 300;
		break;
	case 4:
		points_for_x_lines = 1200;
		break;
	}

	/* updating score */
	Score += points_for_x_lines * (Level + 1);

	/* updating level */
	int prevLevel = Level;
	Level = Score/500;
	if (prevLevel != Level)
		LeveledUp = true;
}

bool Board::UpdatePieceLockedState(Piece *piece) {
	// piece reached bottom
	if (piece->y_pos + piece->height == matrix.size())
		return true;

	// piece collided with main matrix
	for (unsigned int i = 0; i < piece->matrix[0].size(); i++) {
		int scan_line = piece->matrix.size()-1;
		while (scan_line >= 0) {
			if (piece->matrix[scan_line][i] &&
				matrix[piece->y_pos + scan_line + 1][piece->x_pos + i].isOccupied)
					return true;
			else
				scan_line--;
		}
	}

	return false;
}

void Board::MergePiece(Piece *piece) {
	Cell tempCell = { 1, piece->color };

	for (unsigned int i = 0; i < piece->matrix.size(); i++)
		for (unsigned int j = 0; j < piece->matrix[i].size(); j++)
			if (piece->matrix[i][j])
				matrix[piece->y_pos + i][piece->x_pos + j] = tempCell;
}

void Board::Draw() {
	/* drawing main matrix */
	for (unsigned int i = 2; i < matrix.size(); i++) {
		for (unsigned int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j].isOccupied)
				switch (matrix[i][j].color) {
				default:
				case YellowCell:
					al_draw_bitmap(yellow_cell, 275 + j*25, i*25, NULL);
					break;
				case BlueCell:
					al_draw_bitmap(blue_cell, 275 + j*25, i*25, NULL);
					break;
				case PurpleCell:
					al_draw_bitmap(purple_cell, 275 + j*25, i*25, NULL);
					break;
				case GreenCell:
					al_draw_bitmap(green_cell, 275 + j*25, i*25, NULL);
					break;
				case RedCell:
					al_draw_bitmap(red_cell, 275 + j*25, i*25, NULL);
					break;
			}
		}
	}

	/* drawing animations */
	int animationFrames = 20;
	for (unsigned int i = 0; i < clearedLineAnimationCoords.size(); i++) {
		/* if animation ended... */
		if (clearedLineAnimationCoords[i].frame == animationFrames) {
			/* ...delete AnimElem and...*/
			clearedLineAnimationCoords.erase(clearedLineAnimationCoords.begin()+i);

			/* ...decrement i to make up to the increment after break */
			i--;
			break;
		}
		else {
			/* processing vector info */
			double y1 = clearedLineAnimationCoords[i].y1;
			double y2 = clearedLineAnimationCoords[i].y1 + 25;
			double yEffectDispersion = 20 + sqrt(clearedLineAnimationCoords[i].frame * 10);
			double alpha = (int)(clearedLineAnimationCoords[i].frame * 255.0 / animationFrames);
			cout << alpha << endl;
			ALLEGRO_COLOR effectColor = al_map_rgba(255*alpha, 255*alpha, 0*alpha, alpha);

			/* drawing frame */
			al_draw_filled_rectangle(0, y1 - yEffectDispersion, ScreenWidth, y2 + yEffectDispersion, effectColor);

			/* incrementing frame to play next */
			clearedLineAnimationCoords[i].frame++;
		}
	}
}


Board::~Board() {
	al_destroy_bitmap(yellow_cell);
	al_destroy_bitmap(blue_cell);
	al_destroy_bitmap(green_cell);
	al_destroy_bitmap(red_cell);
	al_destroy_bitmap(purple_cell);
}
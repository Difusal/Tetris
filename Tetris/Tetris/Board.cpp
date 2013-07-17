#include "Board.h"

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

void Board::Update() {
	int lines_cleared = 0;

	for (unsigned int i = 0; i < matrix.size(); i++) {
		for (unsigned int j = 0; j < matrix[i].size(); j++) {
			if (!matrix[i][j].isOccupied)
				break;
			else if (matrix[i][j].isOccupied && j == matrix[i].size()-1) {
				lines_cleared++;

				matrix.erase(matrix.begin()+i);

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
	for (unsigned int i = 2; i < matrix.size(); i++)
		for (unsigned int j = 0; j < matrix[i].size(); j++)
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


Board::~Board() {

}
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
	for (unsigned int i = 0; i < 20; i++)
		matrix.push_back(temp);
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
	for (unsigned int i = 0; i < matrix.size(); i++)
		for (unsigned int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j].isOccupied)
				switch (matrix[i][j].color) {
				default:
				case YellowCell:
					al_draw_bitmap(yellow_cell, 275 + j*25, 50 + i*25, NULL);
					break;
				case BlueCell:
					al_draw_bitmap(blue_cell, 275 + j*25, 50 + i*25, NULL);
					break;
				case PurpleCell:
					al_draw_bitmap(purple_cell, 275 + j*25, 50 + i*25, NULL);
					break;
				case GreenCell:
					al_draw_bitmap(green_cell, 275 + j*25, 50 + i*25, NULL);
					break;
				case RedCell:
					al_draw_bitmap(red_cell, 275 + j*25, 50 + i*25, NULL);
					break;
			}
}


Board::~Board() {

}
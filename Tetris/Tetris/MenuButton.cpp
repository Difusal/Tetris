#include "MenuButton.h"
#include "Tetris.h"

MenuButton::MenuButton(const char *Label, bool IsThisTheTitle, int YPos) {
	label = Label;

	isTitle = IsThisTheTitle;

	if (isTitle)
		font = *Tetris::GetInstance()->big_font;
	else
		font = *Tetris::GetInstance()->regular_font;

	int y_margin = 5;
	if (isTitle)
		y_margin = 18;

	y_pos = YPos;
	p1_x = 1;
	p1_y = y_pos - y_margin;
	p2_x = ScreenWidth;
	p2_y = y_pos + font.height;

	button_color = Yellow;
}

void MenuButton::setYPos(int YPos) {
	if (isTitle)
		font = *Tetris::GetInstance()->big_font;
	else
		font = *Tetris::GetInstance()->regular_font;

	int y_margin = 5;
	if (isTitle)
		y_margin = 18;

	y_pos = 80+YPos;
	p1_x = 1;
	p1_y = y_pos - y_margin;
	p2_x = ScreenWidth;
	p2_y = y_pos + font.height;
}

bool MenuButton::isBeingHovered() {
	if ((p1_x < Tetris::GetInstance()->mouse_x && Tetris::GetInstance()->mouse_x < p2_x) &&
		(p1_y < Tetris::GetInstance()->mouse_y && Tetris::GetInstance()->mouse_y < p2_y))
		return true;

	return false;
}

bool MenuButton::wasPressed() {
	if ((p1_x < Tetris::GetInstance()->mouse_x && Tetris::GetInstance()->mouse_x < p2_x) &&
		(p1_y < Tetris::GetInstance()->mouse_y && Tetris::GetInstance()->mouse_y < p2_y) &&
		Tetris::GetInstance()->left_mouse_button_released && !isTitle) {
			cout << "! Button pressed !" << endl;
			Tetris::GetInstance()->left_mouse_button_released = false;
			return true;
	}

	return false;
}

void MenuButton::drawButton() {
	/* drawing button background */
	unsigned int alpha = 96;
	al_draw_filled_rectangle(p1_x, p1_y, p2_x, p2_y, al_map_rgba(32*alpha, 32*alpha, 32*alpha, alpha));
	
	/* printing label */
	al_draw_text(&font, Black, ScreenWidth/2 + 1, y_pos + 2, ALLEGRO_ALIGN_CENTRE, label);
	al_draw_text(&font, White, ScreenWidth/2, y_pos, ALLEGRO_ALIGN_CENTRE, label);

	/* drawing button borders */
	if (this->isBeingHovered() && !isTitle)
		al_draw_rectangle(p1_x, p1_y, p2_x, p2_y, button_color, 1.0);
}

MenuButton::~MenuButton() {
}
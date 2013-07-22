#include "Button.h"
#include "Tetris.h"

Button::Button(int X1, int Y1, int X2, int Y2, ALLEGRO_COLOR Color) {
	p1_x = X1;
	p1_y = Y1;
	p2_x = X2;
	p2_y = Y2;

	button_color = Color;
}

bool Button::isBeingHovered() {
	if ((p1_x < Tetris::GetInstance()->mouse_x && Tetris::GetInstance()->mouse_x < p2_x) &&
		(p1_y < Tetris::GetInstance()->mouse_y && Tetris::GetInstance()->mouse_y < p2_y))
		return true;

	return false;
}

bool Button::wasPressed() {
	if ((p1_x < Tetris::GetInstance()->mouse_x && Tetris::GetInstance()->mouse_x < p2_x) &&
		(p1_y < Tetris::GetInstance()->mouse_y && Tetris::GetInstance()->mouse_y < p2_y) &&
		Tetris::GetInstance()->left_mouse_button_released) {
			Tetris::GetInstance()->left_mouse_button_released = false;
			return true;
	}

	return false;
}

void Button::drawButton() {
	al_draw_rectangle(p1_x, p1_y, p2_x, p2_y, button_color, 1.0);
}

Button::~Button(void) {
}
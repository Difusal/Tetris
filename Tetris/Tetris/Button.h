#pragma once

#include "stdIncludes.h"

class Button
{
public:
	Button(int X1, int Y1, int X2, int Y2, ALLEGRO_COLOR Color = Yellow);

	bool isBeingHovered();
	bool wasPressed();

	void drawButton();

	~Button(void);

private:
	int p1_x, p1_y;
	int p2_x, p2_y;

	bool hovered;
	bool pressed;

	ALLEGRO_COLOR button_color;
};
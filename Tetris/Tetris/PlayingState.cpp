#include "PlayingState.h"

void PlayingState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(PlayingBackground);
	if (!background)
	{
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* defining buttons */
	exitButton = new Button(630, 462, 700, 494);
	buttons.push_back(exitButton);

	fallingPiece = new Piece();
}

bool PlayingState::Update(ALLEGRO_EVENT * ev)
{
	al_get_keyboard_state(&keyState);

	if (ev->timer.source == Tetris::GetInstance()->GetTimer()) {
		/* moving piece sideways */
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
			fallingPiece->x_pos++;
			if (fallingPiece->x_pos + fallingPiece->width > 10)
				fallingPiece->x_pos = 10 - fallingPiece->width;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
			fallingPiece->x_pos--;
			if (fallingPiece->x_pos < 0)
				fallingPiece->x_pos = 0;
		}
		/* rotating piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_D)) {

		}
		if (al_key_down(&keyState, ALLEGRO_KEY_A)) {

		}
		/* soft dropping piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
			fallingPiece->y_pos++;
		}
		/* hard dropping piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_UP) ||
			al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {

		}
		/* holding piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_LSHIFT)) {

		}
	}

	/* dropping piece */
	if (Tetris::GetInstance()->pieceCanFall) {
		Tetris::GetInstance()->pieceCanFall = false;
		fallingPiece->y_pos++;
	}

	/* checking if any button was pressed */
	if (exitButton->wasPressed()) {
		Tetris::GetInstance()->setDoneState(true);
		return true;
	}

	return false;
}

void PlayingState::Draw()
{
	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);

	/* drawing falling piece */
	fallingPiece->Draw();

	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		if (buttons[i]->isBeingHovered())
			buttons[i]->drawButton();
}

void PlayingState::Terminate()
{
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];

	al_destroy_bitmap(background);
}
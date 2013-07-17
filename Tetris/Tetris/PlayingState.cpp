#include "PlayingState.h"

void PlayingState::UpdatePiecePosition(ALLEGRO_EVENT * ev)
{
	/* moving piece sideways */
	if (ev->type == ALLEGRO_EVENT_TIMER) {
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
			if (fallingPiece->y_pos < 0)
				fallingPiece->y_pos = 0;
		}
	}	


	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		/* holding piece */
		if (ev->keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
			if (!holdPiece) {
				holdPiece = fallingPiece;
				fallingPiece = nextPiece;
				nextPiece = new Piece();

				fallingPiece->PositionOnBoardTop();
			}
			else if (holdPiece) {
				tempPiece = fallingPiece;
				fallingPiece = holdPiece;
				holdPiece = tempPiece;

				fallingPiece->PositionOnBoardTop();
			}
		}
		/* hard dropping piece */
		if (ev->keyboard.keycode == ALLEGRO_KEY_UP ||
			ev->keyboard.keycode == ALLEGRO_KEY_SPACE) {

		}
	}
}


void PlayingState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(PlayingBackground);
	if (!background)
	{
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	pieceLocked = false;

	/* starting game matrix */
	board = new Board();

	/* create falling piece */
	fallingPiece = new Piece();
	/* create next piece */
	nextPiece = new Piece();
	/* defining hold piece */
	holdPiece = nullptr;
	/* defining temp piece */
	tempPiece = nullptr;

	/* defining buttons */
	exitButton = new Button(630, 462, 700, 494);
	buttons.push_back(exitButton);
}

bool PlayingState::Update(ALLEGRO_EVENT *ev) {
	al_get_keyboard_state(&keyState);
	pieceLocked = board->UpdatePieceLockedState(fallingPiece);

	/* if line is full, delete it and move down matrix */
	board->Update();

	/* if piece settled, releasing next */
	if (pieceLocked) {
		board->MergePiece(fallingPiece);

		fallingPiece = nextPiece;
		nextPiece = new Piece();

		fallingPiece->PositionOnBoardTop();
	}

	/* updating position  */
	//if (ev->timer.source == Tetris::GetInstance()->GetTimer() || ev->type == ALLEGRO_EVENT_KEY_DOWN)
	UpdatePiecePosition(ev);

	/* dropping piece */
	if (Tetris::GetInstance()->pieceCanFall) {
		Tetris::GetInstance()->pieceCanFall = false;
		if (!pieceLocked)
			fallingPiece->y_pos++;
		if (fallingPiece->y_pos < 0)
			fallingPiece->y_pos = 0;
	}

	/* positioning next piece */
	nextPiece->PositionOnNextPieceBox();

	/* positioning hold piece */
	if (holdPiece)
		holdPiece->PositionOnHoldBox();

	/* checking if any button was pressed */
	if (exitButton->wasPressed()) {
		Tetris::GetInstance()->setDoneState(true);
		return true;
	}

	return false;
}

void PlayingState::Draw() {
	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);

	/* drawing board matrix */
	board->Draw();

	/* drawing falling piece */
	fallingPiece->Draw();

	/* drawing next piece */
	nextPiece->Draw();

	/* drawing hold piece */
	if (holdPiece)
		holdPiece->Draw();

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
#include "PlayingState.h"

void PlayingState::UpdatePiecePosition(ALLEGRO_EVENT * ev)
{
	if (ev->type == ALLEGRO_EVENT_TIMER) {
		/* moving piece right or left */
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
			if (fallingPiece->x_pos + fallingPiece->width + 1 <= 10)
				if (board->PieceCanMoveRight(fallingPiece))
					fallingPiece->x_pos++;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
			if (fallingPiece->x_pos - 1 >= 0)
				if (board->PieceCanMoveLeft(fallingPiece))
					fallingPiece->x_pos--;
		}

		/* soft dropping piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
			if (!board->UpdatePieceLockedState(fallingPiece))
				fallingPiece->y_pos++;
			if (fallingPiece->y_pos < 0)
				fallingPiece->y_pos = 0;
		}
	}	
	
	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		/* rotating piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_D)) {
			fallingPiece->RotateRight();
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_A)) {
			fallingPiece->RotateLeft();
		}
		while (board->PieceIsInsideMainMatrixAfterRotating(fallingPiece)) {
			fallingPiece->x_pos--;
			if (fallingPiece->x_pos < 0) {
				fallingPiece->RotateRight();
				fallingPiece->x_pos = 0;
			}
		}

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
				// stuff here
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

	/* checking if any button was pressed */
	if (exitButton->wasPressed()) {
		Tetris::GetInstance()->setDoneState(true);
		return true;
	}

	/* if line is full, delete it and move down matrix */
	board->Update();

	pieceLocked = board->UpdatePieceLockedState(fallingPiece);
	/* dropping piece */
	if (Tetris::GetInstance()->pieceCanFall) {
		Tetris::GetInstance()->pieceCanFall = false;
		if (!pieceLocked)
			fallingPiece->y_pos++;
		if (fallingPiece->y_pos < 0)
			fallingPiece->y_pos = 0;

		return true;
	}

	/* if piece settled, releasing next */
	if (pieceLocked) {
		board->MergePiece(fallingPiece);

		fallingPiece = nextPiece;
		nextPiece = new Piece();

		fallingPiece->PositionOnBoardTop();

		/* positioning next piece */
		nextPiece->PositionOnNextPieceBox();

		return true;
	}

	/* updating position  */
	UpdatePiecePosition(ev);

	/* positioning hold piece */
	if (holdPiece)
		holdPiece->PositionOnHoldBox();

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
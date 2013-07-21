#include "PlayingState.h"

void PlayingState::UpdateSpeeds() {
	/* this timer is the one that speeds up */
	al_set_timer_speed(Tetris::GetInstance()->GetGravityTimer(), 30.0 / PlayingFPS);

	/* these timers should use FPS denominator to stay constant during the game */
	al_set_timer_speed(Tetris::GetInstance()->GetSoftDropTimer(), 2.5 / FPS);
	al_set_timer_speed(Tetris::GetInstance()->GetSidewaysMovementTimer(), 1.5 / FPS);
	// EDIT THIS TO USE A LOCK TIMER!
	lockDelay = FPS;
}


void PlayingState::PositionPiecesCorrectlyOnEachBox()
{
	nextPiece->PositionOnNextPieceBox();
	if (holdPiece)
		holdPiece->PositionOnHoldBox();
}

void PlayingState::PositionFallingPieceOnBoardTop()
{
	fallingPiece->PositionOnBoardTop();
}

void PlayingState::ComputePlayerInput(ALLEGRO_EVENT * ev)
{
	if (ev->type == ALLEGRO_EVENT_KEY_UP) {
		if (ev->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				/* restarting counter */
				pieceSidewaysMovementDelayCounter = 0;

				pieceMovementDelayAfterPressingKeyContinuouslyOver = false;
				rightArrowPressedContinuously = false;
		}
		if (ev->keyboard.keycode == ALLEGRO_KEY_LEFT) {
			/* restarting counter */
			pieceSidewaysMovementDelayCounter = 0;

			pieceMovementDelayAfterPressingKeyContinuouslyOver = false;
			leftArrowPressedContinuously = false;
		}
	}

	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		/* moving piece sideways ONCE */
		if (!rightArrowPressedContinuously &&
			ev->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				rightArrowPressedContinuously = true;
				MovePieceRightIfPossible();
		}
		if (!leftArrowPressedContinuously &&
			ev->keyboard.keycode == ALLEGRO_KEY_LEFT) {
				leftArrowPressedContinuously = true;
				MovePieceLeftIfPossible();
		}

		/* rotating piece */
		if (ev->keyboard.keycode == ALLEGRO_KEY_D) {
			fallingPiece->RotateRight();
		}
		if (ev->keyboard.keycode == ALLEGRO_KEY_A) {
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
		if (ev->keyboard.keycode == ALLEGRO_KEY_LSHIFT &&
			!pieceAlreadyHolded)
		{
			pieceAlreadyHolded = true;

			if (!holdPiece) {
				holdPiece = fallingPiece;
				fallingPiece = nextPiece;
				nextPiece = new Piece();

				PositionPiecesCorrectlyOnEachBox();
				PositionFallingPieceOnBoardTop();
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

	if (ev->type == ALLEGRO_EVENT_TIMER &&
		ev->timer.source == Tetris::GetInstance()->GetSidewaysMovementTimer()) {
		if ((rightArrowPressedContinuously || leftArrowPressedContinuously) &&
			!pieceMovementDelayAfterPressingKeyContinuouslyOver) {
			pieceSidewaysMovementDelayCounter++;

			if (pieceSidewaysMovementDelayCounter == pieceSidewaysMovementDelay) {
				/* enabling sideways movement */
				pieceMovementDelayAfterPressingKeyContinuouslyOver = true;
			}
		}

		/* moving piece right or left CONTINUOUSLY */
		if (pieceMovementDelayAfterPressingKeyContinuouslyOver) {
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) &&
				rightArrowPressedContinuously) {
				MovePieceRightIfPossible();
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) &&
				leftArrowPressedContinuously) {
				MovePieceLeftIfPossible();
			}
		}
	}

	if (ev->type == ALLEGRO_EVENT_TIMER &&
		ev->timer.source == Tetris::GetInstance()->GetSoftDropTimer()) {
		/* soft dropping piece */
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
			if (!board->UpdatePieceLockedState(fallingPiece))
				fallingPiece->y_pos++;
			if (fallingPiece->y_pos < 0)
				fallingPiece->y_pos = 0;
		}
	}
}


void PlayingState::MovePieceRightIfPossible() {
	if (fallingPiece->x_pos + fallingPiece->width + 1 <= 10)
		if (board->PieceCanMoveRight(fallingPiece))
			fallingPiece->x_pos++;
}

void PlayingState::MovePieceLeftIfPossible() {
	if (fallingPiece->x_pos - 1 >= 0)
		if (board->PieceCanMoveLeft(fallingPiece))
			fallingPiece->x_pos--;
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

	/* initializing variables */
	score = 0;
	level = 0;
	leveledUp = false;
	PlayingFPS = FPS;
	pieceSidewaysMovementDelay = 5;

	UpdateSpeeds();

	pieceLocked = false;
	pieceAlreadyHolded = false;
	pieceMovementDelayAfterPressingKeyContinuouslyOver = false;
	rightArrowPressedContinuously = false;
	leftArrowPressedContinuously = false;
	lockDelayCounter = 0;
	pieceSidewaysMovementDelayCounter = 0;

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

	PositionPiecesCorrectlyOnEachBox();
	PositionFallingPieceOnBoardTop();

	/* defining buttons */
	exitButton = new Button(630, 462, 700, 494);
	buttons.push_back(exitButton);
}

bool PlayingState::Update(ALLEGRO_EVENT *ev) {
	al_get_keyboard_state(&keyState);

	/* checking if game over */
	if (board->GameOver()) {
		exit(-1);
		return true;
	}

	/* updating speed if level up */
	if (leveledUp) {
		cout << "Level Up!" << endl;
		leveledUp = false;
		PlayingFPS += 2;
		al_set_timer_speed(Tetris::GetInstance()->GetTimer(), 1 / PlayingFPS);
		UpdateSpeeds();
	}

	/* checking if any button was pressed */
	if (exitButton->wasPressed()) {
		Tetris::GetInstance()->setDoneState(true);
		return true;
	}

	/* if line is full, delete it and move down matrix */
	board->Update(score, level, leveledUp);

	/* dropping piece */
	pieceLocked = board->UpdatePieceLockedState(fallingPiece);
	if (ev->type == ALLEGRO_EVENT_TIMER &&
		ev->timer.source == Tetris::GetInstance()->GetGravityTimer()) {
			if (!pieceLocked)
				fallingPiece->y_pos++;
			if (fallingPiece->y_pos < 0)
				fallingPiece->y_pos = 0;

			return true;
	}

	/* if piece settled, releasing next */
	if (pieceLocked) {
		lockDelayCounter++;
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) ||
			lockDelayCounter == lockDelay) {
			/* restarting counter */
			lockDelayCounter = 0;

			/* enabling piece switch with piece in hold box */
			pieceAlreadyHolded = false;

			/* merging piece with main matrix */
			board->MergePiece(fallingPiece);

			fallingPiece = nextPiece;
			nextPiece = new Piece();

			PositionPiecesCorrectlyOnEachBox();
			PositionFallingPieceOnBoardTop();

			return true;
		}
	}

	/* updating position  */
	ComputePlayerInput(ev);

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

	/* printing score */
	stringstream ss;
	ss << score;
	al_draw_text(Tetris::GetInstance()->font, Yellow, 665, 300, ALLEGRO_ALIGN_CENTER, ss.str().c_str());

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
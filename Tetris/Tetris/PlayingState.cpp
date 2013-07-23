#include "PlayingState.h"

void PlayingState::StartTimers() {
	/* these timers should use FPS denominator to stay constant during the game */
	al_set_timer_speed(Tetris::GetInstance()->GetSoftDropTimer(), 2.5 / FPS);
	al_set_timer_speed(Tetris::GetInstance()->GetSidewaysMovementTimer(), 1.5 / FPS);
	lockDelay = FPS;
}

void PlayingState::UpdateTimers() {
	/* this timer is the one that speeds up */
	al_set_timer_speed(Tetris::GetInstance()->GetGravityTimer(), 30.0 / PlayingFPS);
}


void PlayingState::PositionPiecesCorrectlyOnEachBox() {
	nextPiece->PositionOnNextPieceBox();
	if (holdPiece)
		holdPiece->PositionOnHoldBox();
}

void PlayingState::PositionFallingPieceOnBoardTop() {
	fallingPiece->PositionOnBoardTop();
}

void PlayingState::ComputePlayerInput(ALLEGRO_EVENT * ev) {
	if (ev->type == ALLEGRO_EVENT_KEY_UP) {		
		/* right arrow key released */
		if (ev->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				/* restarting counter */
				pieceSidewaysMovementDelayCounter = 0;

				pieceMovementDelayAfterPressingKeyContinuouslyOver = false;
				rightArrowPressedContinuously = false;
		}
		/* left arrow key released */
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
				while (!board->UpdatePieceLockedState(fallingPiece)) {
					/* incrementing score by 2*/
					score += 2;

					/* incrementing piece y position */					
					fallingPiece->y_pos++;
				}
				if (fallingPiece->y_pos < 0)
					fallingPiece->y_pos = 0;
		}
	}

	if (ev->type == ALLEGRO_EVENT_TIMER &&
		ev->timer.source == Tetris::GetInstance()->GetSidewaysMovementTimer()) {
			/* if right or left arrow key still pressed and piece movement delay isn't over... (...long if :P) */
			if ((rightArrowPressedContinuously || leftArrowPressedContinuously) &&
				!pieceMovementDelayAfterPressingKeyContinuouslyOver) {
					/* ...increment counter */
					pieceSidewaysMovementDelayCounter++;

					/* if counter is over... */
					if (pieceSidewaysMovementDelayCounter == pieceSidewaysMovementDelay) {
						/* ...enabling sideways movement */
						pieceMovementDelayAfterPressingKeyContinuouslyOver = true;
					}
			}

			/* moving falling piece right or left CONTINUOUSLY */
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
			/* if down arrow key is pressed... */
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
				/* ...soft dropping piece */
				if (!board->UpdatePieceLockedState(fallingPiece)) {
					/* incrementing score by 1*/
					score++;

					/* incrementing piece y position */
					fallingPiece->y_pos++;
				}
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
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	forbidden = al_load_bitmap(ForbiddenIcon);
	if (!forbidden) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load forbidden bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */
	score = 0;
	level = 0;
	leveledUp = false;
	PlayingFPS = FPS;
	pieceSidewaysMovementDelay = 5;

	StartTimers();
	UpdateTimers();

	gamePaused = false;
	pausingMusic = false;
	resumingMusic = false;
	firstPieceLocked = false;
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
	soundsButton = new Button(618, 380, 658, 420);
	buttons.push_back(soundsButton);
	musicsButton = new Button(670, 380, 710, 420);
	buttons.push_back(musicsButton);
	exitButton = new Button(630, 462, 700, 494);
	buttons.push_back(exitButton);

	if (Tetris::GetInstance()->musics_on) {
		/* setting play mode */
		themeSongInstance = al_create_sample_instance(Tetris::GetInstance()->themeSong);
		al_set_sample_instance_playmode(themeSongInstance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(themeSongInstance, al_get_default_mixer());
		/* start playing song */
		al_play_sample_instance(themeSongInstance);
	}
}

bool PlayingState::Update(ALLEGRO_EVENT *ev) {
	al_get_keyboard_state(&keyState);

	/* pausing/resuming music */
	if (pausingMusic) {
		pausingMusic = false;
		cout << "Saving sample instance current position..." << endl;
		themeSongInstancePosition = al_get_sample_instance_position(themeSongInstance);
		al_stop_sample_instance(themeSongInstance);
	}
	else if (Tetris::GetInstance()->musics_on && resumingMusic) {
		resumingMusic = false;
		al_set_sample_instance_position(themeSongInstance, themeSongInstancePosition);
		al_play_sample_instance(themeSongInstance);
	}

	/* pausing/resuming game */
	if ((Tetris::GetInstance()->left_mouse_button_released && gamePaused) ||
		(ev->type == ALLEGRO_EVENT_KEY_DOWN && gamePaused) ||
		(ev->type == ALLEGRO_EVENT_KEY_DOWN &&
		(ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE || ev->keyboard.keycode == ALLEGRO_KEY_ENTER))) {
			switch (gamePaused)
			{
			case 0:
				gamePaused = true;
				pausingMusic = true;
				break;
			case 1:
				gamePaused = false;
				resumingMusic = true;
				Tetris::GetInstance()->left_mouse_button_released = false;
				return true;
				break;
			}
	}
	if (gamePaused)
		return true;

	/* checking if game over */
	if (board->GameOver()) {
		cout << "! Game Over !" << endl;
		cout << "Score: " << score << endl;
		exit(-1);
		return true;
	}

	/* updating speed if level up */
	if (leveledUp) {
		cout << "Level Up!" << endl;
		leveledUp = false;
		PlayingFPS += 15;
		UpdateTimers();
	}

	/* checking if any button was pressed */
	if (exitButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(MainMenu);
		return true;
	}
	if (musicsButton->wasPressed()) {
		switch (Tetris::GetInstance()->musics_on)
		{
		case 0:
			cout << "Music: On" << endl;
			resumingMusic = true;
			Tetris::GetInstance()->musics_on = true;
			break;
		case 1:
			cout << "Music: Off" << endl;
			pausingMusic = true;
			Tetris::GetInstance()->musics_on = false;
			break;
		}
		return true;
	}
	if (soundsButton->wasPressed()) {
		switch (Tetris::GetInstance()->sounds_on)
		{
		case 0:
			cout << "Sounds Effects: On" << endl;
			Tetris::GetInstance()->sounds_on = true;
			break;
		case 1:
			cout << "Sounds Effects: Off" << endl;
			Tetris::GetInstance()->sounds_on = false;
			break;
		}
		return true;
	}

	/* if line is full, delete it and move down matrix */
	board->Update(score, level, leveledUp, firstPieceLocked);

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
		if (al_key_down(&keyState, ALLEGRO_KEY_UP) ||
			lockDelayCounter == lockDelay) {
			/* restarting counter */
			lockDelayCounter = 0;

			/* enabling piece switch with piece in hold box */
			pieceAlreadyHolded = false;

			/* merging piece with main matrix */
			board->MergePiece(fallingPiece);

			if (!firstPieceLocked)
				firstPieceLocked = true;

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

	/* printing score */
	stringstream ss;
	ss << score;
	al_draw_text(Tetris::GetInstance()->regular_font, Yellow, 665, 300, ALLEGRO_ALIGN_CENTER, ss.str().c_str());

	/* if game paused */
	if (gamePaused) {
		unsigned int alpha = 200;
		al_draw_filled_rectangle(0, 0, ScreenWidth, ScreenHeight, al_map_rgba(32*alpha, 32*alpha, 32*alpha, alpha));
		int x = ScreenWidth/2.0;
		int y1 = ScreenHeight/2.0 - Tetris::GetInstance()->regular_font->height*2;
		int y2 = ScreenHeight/2.0 + Tetris::GetInstance()->regular_font->height;
		al_draw_text(Tetris::GetInstance()->regular_font, Yellow, x, y1, ALLEGRO_ALIGN_CENTRE, "Game Paused");
		al_draw_text(Tetris::GetInstance()->regular_font, White, x, y2, ALLEGRO_ALIGN_CENTRE, "Press any key or click the screen to resume");
		return;
	}

	/* drawing board matrix */
	board->Draw();

	/* drawing falling piece */
	fallingPiece->Draw();

	/* drawing next piece */
	nextPiece->Draw();

	/* drawing hold piece */
	if (holdPiece)
		holdPiece->Draw();

	/* drawing forbidden above icons */
	if (!Tetris::GetInstance()->sounds_on)
		al_draw_bitmap(forbidden, soundsButton->getX(), soundsButton->getY(), NULL);
	if (!Tetris::GetInstance()->musics_on)
		al_draw_bitmap(forbidden, musicsButton->getX(), musicsButton->getY(), NULL);

	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		if (buttons[i]->isBeingHovered())
			buttons[i]->drawButton();
}

void PlayingState::Terminate() {
	al_destroy_bitmap(background);

	if (Tetris::GetInstance()->musics_on)
		al_destroy_sample_instance(themeSongInstance);

	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();

	delete nextPiece;
	delete fallingPiece;
	delete holdPiece;

	delete board;
}
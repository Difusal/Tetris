#include "OptionsState.h"

void OptionsState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(MainMenuAlternativeBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */
	// stuff here

	/* pushing buttons */
	screenTitle = new MenuButton("OPTIONS", true);
	buttons.push_back(screenTitle);
	setKeyToMoveLeftButton = new MenuButton("Move Left: ");
	buttons.push_back(setKeyToMoveLeftButton);
	setKeyToMoveRightButton = new MenuButton("Move Right: ");
	buttons.push_back(setKeyToMoveRightButton);
	setKeyToRotateLeftButton = new MenuButton("Rotate Left: ");
	buttons.push_back(setKeyToRotateLeftButton);
	setKeyToRotateRightButton = new MenuButton("Rotate Right: ");
	buttons.push_back(setKeyToRotateRightButton);
	setKeyToSoftDropButton = new MenuButton("Soft Drop: ");
	buttons.push_back(setKeyToSoftDropButton);
	setKeyToHardDropButton = new MenuButton("Hard Drop: ");
	buttons.push_back(setKeyToHardDropButton);
	setKeyToHoldPieceButton = new MenuButton("Hold Piece: ");
	buttons.push_back(setKeyToHoldPieceButton);
	loadDefaultsButton = new MenuButton("Load Defaults");
	buttons.push_back(loadDefaultsButton);
	mainMenuButton = new MenuButton("Main Menu");
	buttons.push_back(mainMenuButton);

	/* formatting button positions according to buttons vector size */
	int spaceBetweenButtons = 0.9 * (ScreenHeight-screenTitle->getYPos()) / buttons.size();
	if (buttons.size() > 1)
		for (unsigned int i = 1; i < buttons.size(); i++)
			buttons[i]->setYPos(i*spaceBetweenButtons + 0.08*(ScreenHeight-screenTitle->getYPos()));
}

bool OptionsState::Update(ALLEGRO_EVENT *ev) {
	/* setting key */
	if (!newKeyHasBeenSet && ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		*ptrToKeyBeingSet = ev->keyboard.keycode;
		cout << "New control key set." << endl;
		newKeyHasBeenSet = true;
	}

	/* checking if any button was pressed */
	if (setKeyToMoveLeftButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->movePieceLeftKey;
	}
	else if (setKeyToMoveRightButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->movePieceRightKey;
	}
	else if (setKeyToRotateLeftButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->rotatePieceLeftKey;
	}
	else if (setKeyToRotateRightButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->rotatePieceRightKey;
	}
	else if (setKeyToSoftDropButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->softDropPieceKey;
	}
	else if (setKeyToHardDropButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->hardDropPieceKey;
	}
	else if (setKeyToHoldPieceButton->wasPressed()) {
		newKeyHasBeenSet = false;
		ptrToKeyBeingSet = &Tetris::GetInstance()->holdPieceKey;
	}
	else if (loadDefaultsButton->wasPressed()) {
		// restoring default control keys
		Tetris::GetInstance()->movePieceLeftKey = MoveLeftDefaultKey;
		Tetris::GetInstance()->movePieceRightKey = MoveRightDefaultKey;
		Tetris::GetInstance()->rotatePieceLeftKey = RotateLeftDefaultKey;
		Tetris::GetInstance()->rotatePieceRightKey = RotateRightDefaultKey;
		Tetris::GetInstance()->softDropPieceKey = SoftDropDefaultKey;
		Tetris::GetInstance()->hardDropPieceKey = HardDropDefaultKey;
		Tetris::GetInstance()->holdPieceKey = HoldPieceDefaultKey;
		cout << "Default control keys loaded." << endl;
	}
	else if (mainMenuButton->wasPressed()) {
		// returning to main menu
		Tetris::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void OptionsState::Draw() {
	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);
	
	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

void OptionsState::Terminate() {
	/* destroying background bitmap */
	al_destroy_bitmap(background);

	/* deleting buttons */
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();
}
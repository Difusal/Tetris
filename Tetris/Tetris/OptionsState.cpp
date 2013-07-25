#include "OptionsState.h"

void OptionsState::UpdateButtonBindings() {
	// Move Left Control
	ss.str(string());
	ss << "Move Left: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->movePieceLeftKey);
	setKeyToMoveLeftButton->setLabel(ss.str());

	// Move Right Control
	ss.str(string());
	ss << "Move Right: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->movePieceRightKey);
	setKeyToMoveRightButton->setLabel(ss.str());

	// Rotate Left Control
	ss.str(string());
	ss << "Rotate Left: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->rotatePieceLeftKey);
	setKeyToRotateLeftButton->setLabel(ss.str());

	// Rotate Right Control
	ss.str(string());
	ss << "Rotate Right: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->rotatePieceRightKey);
	setKeyToRotateRightButton->setLabel(ss.str());

	// Soft Drop Control
	ss.str(string());
	ss << "Soft Drop: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->softDropPieceKey);
	setKeyToSoftDropButton->setLabel(ss.str());

	// Hard Drop Control
	ss.str(string());
	ss << "Hard Drop: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->hardDropPieceKey);
	setKeyToHardDropButton->setLabel(ss.str());

	// Hold Piece Control
	ss.str(string());
	ss << "Hold Piece: " << getKeyBasedOnAllegroKeyCode(Tetris::GetInstance()->holdPieceKey);
	setKeyToHoldPieceButton->setLabel(ss.str());
}

void OptionsState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(MainMenuAlternativeBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* pushing buttons */
	screenTitle = new MenuButton("CONTROLS", true);
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
	loadDefaultsButton = new MenuButton("Load Defaults", false, Yellow);
	buttons.push_back(loadDefaultsButton);
	mainMenuButton = new MenuButton("Main Menu");
	buttons.push_back(mainMenuButton);

	/* initializing variables */
	UpdateButtonBindings();

	/* formatting button positions according to buttons vector size */
	int spaceBetweenButtons = 0.9 * (ScreenHeight-screenTitle->getYPos()) / buttons.size();
	if (buttons.size() > 1)
		for (unsigned int i = 1; i < buttons.size(); i++)
			buttons[i]->setYPos(i*spaceBetweenButtons + 0.08*(ScreenHeight-screenTitle->getYPos()));
}

bool OptionsState::Update(ALLEGRO_EVENT *ev) {
	/* setting new control key */
	if (!newKeyHasBeenSet && ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		/* setting new custom control key */
		*ptrToKeyBeingSet = ev->keyboard.keycode;

		cout << "New control key set." << endl;
		newKeyHasBeenSet = true;

		/* updating button bindings */
		UpdateButtonBindings();
	}

	/* checking if any button was pressed */
	if (setKeyToMoveLeftButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToMoveLeftButton->setLabel("Move Left: <press a key>");
		ptrToKeyBeingSet = &Tetris::GetInstance()->movePieceLeftKey;
	}
	else if (setKeyToMoveRightButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToMoveRightButton->setLabel("Move Right: <press a key>");
		ptrToKeyBeingSet = &Tetris::GetInstance()->movePieceRightKey;
	}
	else if (setKeyToRotateLeftButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToRotateLeftButton->setLabel("Rotate Left: <press a key>");
		ptrToKeyBeingSet = &Tetris::GetInstance()->rotatePieceLeftKey;
	}
	else if (setKeyToRotateRightButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToRotateRightButton->setLabel("Rotate Right: <press a key>");
		ptrToKeyBeingSet = &Tetris::GetInstance()->rotatePieceRightKey;
	}
	else if (setKeyToSoftDropButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToSoftDropButton->setLabel("Soft Drop: <press a key>");
		ptrToKeyBeingSet = &Tetris::GetInstance()->softDropPieceKey;
	}
	else if (setKeyToHardDropButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToHardDropButton->setLabel("Hard Drop: <press a key>");
		ptrToKeyBeingSet = &Tetris::GetInstance()->hardDropPieceKey;
	}
	else if (setKeyToHoldPieceButton->wasPressed()) {
		newKeyHasBeenSet = false;
		UpdateButtonBindings();
		setKeyToHoldPieceButton->setLabel("Hold Piece: <press a key>");
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
		UpdateButtonBindings();
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
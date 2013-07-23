#include "HowToPlayState.h"

void HowToPlayState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(MainMenuAlternativeBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */


	/* pushing buttons */
	screenTitle = new MenuButton("HOW TO PLAY", true);
	buttons.push_back(screenTitle);
	mainMenuButton = new MenuButton("Main Menu");
	buttons.push_back(mainMenuButton);

	/* formatting button positions according to buttons vector size */
	int spaceBetweenButtons = 0.3 * (ScreenHeight-screenTitle->getYPos()) / buttons.size();
	if (buttons.size() > 1)
		for (unsigned int i = 1; i < buttons.size(); i++)
			buttons[i]->setYPos(i*spaceBetweenButtons + 0.65*(ScreenHeight-screenTitle->getYPos()));
}

bool HowToPlayState::Update(ALLEGRO_EVENT *ev) {
	/* checking if any button was pressed */
	if (mainMenuButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void HowToPlayState::Draw() {
	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);

	/* printing text with info about the game */


	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

void HowToPlayState::Terminate() {
	/* destroying background bitmap */
	al_destroy_bitmap(background);

	/* deleting buttons */
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();
}
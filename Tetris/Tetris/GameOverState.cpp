#include "GameOverState.h"

void GameOverState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(MainMenuAlternativeBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */


	/* pushing buttons */
	screenTitle = new MenuButton("GAME OVER", true);
	buttons.push_back(screenTitle);
	playAgainButton = new MenuButton("Play Again");
	buttons.push_back(playAgainButton);
	mainMenuButton = new MenuButton("Main Menu");
	buttons.push_back(mainMenuButton);

	/* formatting button positions according to buttons vector size */
	int spaceBetweenButtons = 0.3 * (ScreenHeight-screenTitle->getYPos()) / buttons.size();
	if (buttons.size() > 1)
		for (unsigned int i = 1; i < buttons.size(); i++)
			buttons[i]->setYPos(i*spaceBetweenButtons + 0.65*(ScreenHeight-screenTitle->getYPos()));
}

bool GameOverState::Update(ALLEGRO_EVENT *ev) {
	/* checking if any button was pressed */
	if (playAgainButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(Playing);
		return true;
	}
	else if (mainMenuButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void GameOverState::Draw() {
	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);

	/* printing score */
	stringstream ss;
	ss << score;
	al_draw_text(Tetris::GetInstance()->regular_font, Yellow, 665, 300, ALLEGRO_ALIGN_CENTER, ss.str().c_str());

	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

void GameOverState::Terminate() {
	/* destroying background bitmap */
	al_destroy_bitmap(background);

	/* deleting buttons */
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();
}
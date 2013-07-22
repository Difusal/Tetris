#include "MainMenuState.h"

void MainMenuState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(MainMenuScrollingBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */
	backgroundSourceX = 0;

	/* pushing buttons */
	menuTitle = new MenuButton("TETRIS", true);
	buttons.push_back(menuTitle);
	playButton = new MenuButton("PLAY");
	buttons.push_back(playButton);
	howToPlayButton = new MenuButton("HOW TO PLAY");
	buttons.push_back(howToPlayButton);
	optionsButton = new MenuButton("OPTIONS");
	buttons.push_back(optionsButton);
	aboutButton = new MenuButton("ABOUT");
	buttons.push_back(aboutButton);

	/* formatting button positions according to buttons vector size */
	int spaceBetweenButtons = (ScreenHeight-menuTitle->getYPos()) / buttons.size();
	cout << spaceBetweenButtons;
	if (buttons.size() > 1)
		for (unsigned int i = 1; i < buttons.size(); i++)
			buttons[i]->setYPos(i*spaceBetweenButtons);
}

bool MainMenuState::Update(ALLEGRO_EVENT *ev) {
	/* updating scrolling background position */
	if (ev->type == ALLEGRO_EVENT_TIMER &&
		ev->timer.source == Tetris::GetInstance()->GetTimer()) {
			backgroundSourceX += 1;
			if (backgroundSourceX + ScreenWidth > al_get_bitmap_width(background))
				backgroundSourceX = 0;
	}

	/* checking if any button was pressed */
	if (playButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(Playing);
		return true;
	}

	return false;
}

void MainMenuState::Draw() {
	/* drawing background */
	al_draw_bitmap_region(background, backgroundSourceX, 0, ScreenWidth, ScreenHeight, 0, 0, NULL);

	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

void MainMenuState::Terminate() {
	al_destroy_bitmap(background);

	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
}
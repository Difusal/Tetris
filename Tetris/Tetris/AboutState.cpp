#include "AboutState.h"

void AboutState::Initialize() {
	/* loading background */
	background = al_load_bitmap(MainMenuAlternativeBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */
	text.push_back("Tetris v1.0");
	text.push_back("Date: July, 2013");
	text.push_back("Author: Henrique Ferrolho");
	text.push_back("");
	text.push_back("This game was made for educational purposes only.");
	text.push_back("It was programmed using C++ language.");
	text.push_back("Allegro 5 2D graphical library was used as well.");

	/* pushing buttons */
	screenTitle = new MenuButton("ABOUT", true);
	buttons.push_back(screenTitle);
	mainMenuButton = new MenuButton("Main Menu");
	buttons.push_back(mainMenuButton);

	/* formatting button positions according to buttons vector size */
	int spaceBetweenButtons = 0.3 * (ScreenHeight-screenTitle->getYPos()) / buttons.size();
	if (buttons.size() > 1)
		for (unsigned int i = 1; i < buttons.size(); i++)
			buttons[i]->setYPos(i*spaceBetweenButtons + 0.65*(ScreenHeight-screenTitle->getYPos()));
}

bool AboutState::Update(ALLEGRO_EVENT *ev) {
	/* checking if any button was pressed */
	if (mainMenuButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void AboutState::Draw() {
	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);

	/* defining some variables... */
	int spaceBetweenLines = 30;
	int boxYMargin = 15;
	unsigned int alpha = 96;
	int textYPos = screenTitle->getP2_Y()+(mainMenuButton->getP1_Y()-screenTitle->getP2_Y())/2 - text.size()*spaceBetweenLines/2;

	/* drawing text dark transparent background */
	int y = textYPos + text.size()*spaceBetweenLines;
	al_draw_filled_rectangle(0, textYPos-3-boxYMargin, ScreenWidth, y+boxYMargin, al_map_rgba(32*alpha, 32*alpha, 32*alpha, alpha));

	/* printing text with info about the game */
	for (unsigned int i = 0; i < text.size(); i++) {
		al_draw_text(Tetris::GetInstance()->regular_font, Black, 20+1, textYPos + i*spaceBetweenLines + 2, ALLEGRO_ALIGN_LEFT, text[i]);
		al_draw_text(Tetris::GetInstance()->regular_font, White, 20, textYPos + i*spaceBetweenLines, ALLEGRO_ALIGN_LEFT, text[i]);
	}

	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

void AboutState::Terminate() {
	/* destroying background bitmap */
	al_destroy_bitmap(background);

	/* clearing text */
	text.clear();

	/* deleting buttons */
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();
}
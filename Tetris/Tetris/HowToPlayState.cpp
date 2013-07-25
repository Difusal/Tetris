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
	text.push_back("Have you never played tetris before..?");
	text.push_back("");
	text.push_back("Goal:");
	text.push_back("Clear lines and get the highest score as possible.");
	text.push_back("");
	text.push_back("Pieces can be moved left and right. They can be");
	text.push_back("rotated as well.");
	text.push_back("If the game board is full, the game is over.");
	text.push_back("");
	text.push_back("You can customize the controls in Controls menu.");

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

	/* defining some variables... */
	int spaceBetweenLines = 30;
	int boxYMargin = 15;
	unsigned int alpha = 96;
	int textYPos = screenTitle->getP2_Y()+(mainMenuButton->getP1_Y()-screenTitle->getP2_Y())/2 - text.size()*spaceBetweenLines/2;

	/* drawing text dark transparent background */
	int y = textYPos + text.size()*spaceBetweenLines;
	al_draw_filled_rectangle(0, textYPos-3-boxYMargin, ScreenWidth, y+boxYMargin, al_map_rgba(32*alpha, 32*alpha, 32*alpha, alpha));

	/* printing text with info on how to play tetris */
	for (unsigned int i = 0; i < text.size(); i++) {
		al_draw_text(Tetris::GetInstance()->regular_font, Black, 20+1, textYPos + i*spaceBetweenLines + 2, ALLEGRO_ALIGN_LEFT, text[i]);
		al_draw_text(Tetris::GetInstance()->regular_font, White, 20, textYPos + i*spaceBetweenLines, ALLEGRO_ALIGN_LEFT, text[i]);
	}

	/* checking if any button is being hovered */
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->drawButton();
}

void HowToPlayState::Terminate() {
	/* destroying background bitmap */
	al_destroy_bitmap(background);

	/* clearing text */
	text.clear();

	/* deleting buttons */
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();
}
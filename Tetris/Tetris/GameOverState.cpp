#include "GameOverState.h"

bool GameOverState::fileExists(const string &filename) {
	/* trying to open input file stream */
	ifstream infile (filename);

	return infile.good();
}

vector<unsigned int> GameOverState::readTop5FromFile() {
	vector<unsigned int> vec;
	unsigned int data;

	/* opening input stream */
	ifstream myFile (top5FilePath);

	/* storing data to a vector */
	while (myFile.good()) {
		myFile >> data;
		vec.push_back(data);
	}

	return vec;
}

void GameOverState::addDataToTop5AndWriteItToFile(unsigned int Data) {
	/* getting current Top 5 */
	vector<unsigned int> currentTop5 = readTop5FromFile();

	bool dataHasBeenInsertedToVector = false;
	/* scanning entire Top 5 */
	for (unsigned int i = 0; i < currentTop5.size(); i++) {
		/* if Data is greater than the element currently being scanned... */
		if (Data > currentTop5[i]) {
			/* ...insert Data to that position */
			currentTop5.insert(currentTop5.begin()+i, Data);
			dataHasBeenInsertedToVector = true;
			break;
		}
	}
	/* if Data hasn't yet been inserted to the vector, push it back now */
	if (!dataHasBeenInsertedToVector)
		currentTop5.push_back(Data);

	/* opening output stream */
	ofstream myFile (top5FilePath);

	/* rewriting data to file */
	for (unsigned int i = 0; i < currentTop5.size() && i < 5; i++) {
		myFile << currentTop5[i];
		if (i != currentTop5.size()-1 && i != 4)
			myFile << endl;
	}
}

void GameOverState::Initialize()
{
	/* loading background */
	background = al_load_bitmap(MainMenuAlternativeBackground);
	if (!background) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing variables */
	score = Tetris::GetInstance()->tempScore;
	addDataToTop5AndWriteItToFile(score);
	top5 = readTop5FromFile();

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
		Tetris::GetInstance()->ChangeState(Play);
		return true;
	}
	else if (mainMenuButton->wasPressed()) {
		Tetris::GetInstance()->ChangeState(MainMenu);
		return true;
	}

	return false;
}

void GameOverState::Draw() {
	stringstream ss;
	unsigned int i;
	int y;

	/* drawing background */
	al_draw_bitmap(background, 0, 0, NULL);

	/* defining some variables... */
	int top5YPos = 181;
	int spaceBetweenTitleAndTop5 = 10;
	int spaceBetweenLines = 30;
	int personalScoreYCorrection = 60;

	/* drawing top 5 dark transparent background */
	unsigned int alpha = 96;
	int boxMargin = 15;
	y = top5YPos + (top5.size()+1)*spaceBetweenLines + personalScoreYCorrection + spaceBetweenTitleAndTop5;
	al_draw_filled_rectangle(0, top5YPos-8-boxMargin, ScreenWidth, y+boxMargin, al_map_rgba(32*alpha, 32*alpha, 32*alpha, alpha));

	/* printing Top 5 */
	al_draw_text(Tetris::GetInstance()->regular_font, Black, ScreenWidth/2+1, top5YPos+2, ALLEGRO_ALIGN_RIGHT, "Top 5:");
	al_draw_text(Tetris::GetInstance()->regular_font, White, ScreenWidth/2, top5YPos, ALLEGRO_ALIGN_RIGHT, "Top 5:");
	for (i = 0; i < top5.size(); i++) {
		/* cleaning string stream */
		ss.str(string());

		/* printing current line */
		ss << i+1 << "- " << top5[i];
		y = top5YPos + (i+1)*spaceBetweenLines + spaceBetweenTitleAndTop5;
		al_draw_text(Tetris::GetInstance()->regular_font, Black, ScreenWidth/2+1, y+2, ALLEGRO_ALIGN_CENTER, ss.str().c_str());
		al_draw_text(Tetris::GetInstance()->regular_font, White, ScreenWidth/2, y, ALLEGRO_ALIGN_CENTER, ss.str().c_str());
	}

	/* cleaning string stream */
	ss.str(string());
	/* printing personal score */
	ss << "Your score: " << score;
	y = top5YPos + i*spaceBetweenLines + personalScoreYCorrection + spaceBetweenTitleAndTop5;
	al_draw_text(Tetris::GetInstance()->regular_font, Black, ScreenWidth/2+1, y+2, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
	al_draw_text(Tetris::GetInstance()->regular_font, White, ScreenWidth/2, y, ALLEGRO_ALIGN_LEFT, ss.str().c_str());

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
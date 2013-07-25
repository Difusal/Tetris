#include "Tetris.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "HowToPlayState.h"
#include "OptionsState.h"
#include "AboutState.h"

/* generates random numbers */
int random_number (int min, int max) {
	max++;

	return ((rand() % (max-min)) + min);
}

string getKeyBasedOnAllegroKeyCode(int Code) {
	switch (Code)
	{
	default:
	case 1: { return "A"; break; }
	case 2: { return "B"; break; }
	case 3: { return "C"; break; }
	case 4: { return "D"; break; }
	case 5: { return "E"; break; }
	case 6: { return "F"; break; }
	case 7: { return "G"; break; }
	case 8: { return "H"; break; }
	case 9: { return "I"; break; }
	case 10: { return "J"; break; }
	case 11: { return "K"; break; }
	case 12: { return "L"; break; }
	case 13: { return "M"; break; }
	case 14: { return "N"; break; }
	case 15: { return "O"; break; }
	case 16: { return "P"; break; }
	case 17: { return "Q"; break; }
	case 18: { return "R"; break; }
	case 19: { return "S"; break; }
	case 20: { return "T"; break; }
	case 21: { return "U"; break; }
	case 22: { return "V"; break; }
	case 23: { return "W"; break; }
	case 24: { return "X"; break; }
	case 25: { return "Y"; break; }
	case 26: { return "Z"; break; }
	case 27: case 37: { return "0"; break; }
	case 28: case 38: { return "1"; break; }
	case 29: case 39: { return "2"; break; }
	case 30: case 40: { return "3"; break; }
	case 31: case 41: { return "4"; break; }
	case 32: case 42: { return "5"; break; }
	case 33: case 43: { return "6"; break; }
	case 34: case 44: { return "7"; break; }
	case 35: case 45: { return "8"; break; }
	case 36: case 46: { return "9"; break; }
	case 75: { return "Space"; break; }
	case 82: { return "Left"; break; }
	case 83: { return "Right"; break; }
	case 84: { return "Up"; break; }
	case 85: { return "Down"; break; }
	case 215: { return "Left Shift"; break; }
	case 216: { return "Right Shift"; break; }
	case 217: { return "Left Control"; break; }
	case 218: { return "Right Control"; break; }
	}
}

Tetris *Tetris::instance = nullptr;

Tetris *Tetris::GetInstance()
{
	if (!instance)
	{
		instance = new Tetris();
	}

	return instance;
}

void Tetris::ChangeState (int newState)
{
	if (state != -1) {
		states[state]->Terminate();
	}

	state = newState;

	states[state]->Initialize();
}


void Tetris::CreateAllegroDisplay()
{
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(ScreenWidth, ScreenHeight);
	if (!display)
	{
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	/* setting new window title */
	al_set_window_title(display, ProgramTitle);
}

void Tetris::LoadFonts()
{
	regular_font = al_load_font(ConsolaTTF, 25, NULL);
	big_font = al_load_font(ConsolaTTF, 50, NULL);
	if (!regular_font)
	{
		al_show_native_message_box(Tetris::GetInstance()->display, "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}

void Tetris::Initialize()
{
	cout << endl;
	cout << "##############################" << endl;
	cout << "##                          ##" << endl;
	cout << "##     STARTING  TETRIS     ##" << endl;
	cout << "##                          ##" << endl;
	cout << "##############################" << endl;
	cout << endl;
	cout << "-------------" << endl;
	cout << "Activity Log:" << endl;
	cout << "-------------" << endl;

	cout << "Getting time seed for random numbers..." << endl;
	srand ((unsigned int) time(NULL));

	cout << "Starting Allegro 5..." << endl;
	if (!al_init())
	{ al_show_native_message_box(NULL, NULL, "Could not initialize Allegro 5", NULL, NULL, NULL); }

	cout << "Initializing add ons..." << endl;
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	cout << "Installing devices..." << endl;
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();

	cout << "Creating display..." << endl;
	CreateAllegroDisplay();

	cout << "Displaying loading game background..." << endl;
	loading_background = al_load_bitmap(LoadingGameBackground);
	if (!loading_background) {
		al_show_native_message_box(display, "Error", "Could not load loading game background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	al_draw_bitmap(loading_background, 0, 0, NULL);
	al_flip_display();

	cout << "Hiding windows mouse cursor..." << endl;
	al_hide_mouse_cursor(display);

	cout << "Loading fonts..." << endl;
	LoadFonts();

	cout << "Creating timers..." << endl;
	timer = al_create_timer(1.0 / FPS);
	/* edit these timers on PlayingState::UpdateSpeeds(); */
	gravityTimer = al_create_timer(1.0 / FPS);
	softDropTimer = al_create_timer(1.0 / FPS);
	sidewaysMovementTimer = al_create_timer(1.0 / FPS);

	cout << "Creating event queues..." << endl;
	event_queue = al_create_event_queue();

	cout << "Registering event sources..." << endl;
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(gravityTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(softDropTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(sidewaysMovementTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());	

	cout << "Stating how many sounds can play simultaneously..." << endl;
	al_reserve_samples(3);

	cout << "Loading audio samples..." << endl;
	lineClearSound = al_load_sample(LineClearSound);
	explosionSound = al_load_sample(ExplosionSound);
	themeSong = al_load_sample(ThemeSong);
	if (!themeSong) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load Tetris theme song.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	cout << "Initializing variables..." << endl;
	mouse = al_load_bitmap(MouseCursor);
	mouse_x = ScreenWidth;
	mouse_y = ScreenHeight;
	left_mouse_button_pressed = false;
	left_mouse_button_released = false;
	musics_on = true;
	sounds_on = true;

	movePieceLeftKey = MoveLeftDefaultKey;
	movePieceRightKey = MoveRightDefaultKey;
	rotatePieceLeftKey = RotateLeftDefaultKey;
	rotatePieceRightKey = RotateRightDefaultKey;
	softDropPieceKey = SoftDropDefaultKey;
	hardDropPieceKey = HardDropDefaultKey;
	holdPieceKey = HoldPieceDefaultKey;

	done = false;
	draw = true;

	cout << "Starting timers..." << endl;
	al_start_timer(timer);
	al_start_timer(gravityTimer);
	al_start_timer(softDropTimer);
	al_start_timer(sidewaysMovementTimer);
}

void Tetris::TrackMouse()
{
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouse_x = ev.mouse.x;
		mouse_y = ev.mouse.y;

		draw = true;
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if (ev.mouse.button & 1)
		{
			//cout << "* Left mouse button pressed *" << endl;
			left_mouse_button_pressed = true;
			left_mouse_button_released = false;
			draw = true;
		}
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if (ev.mouse.button & 1)
		{
			cout << "* Left mouse button released *" << endl;
			left_mouse_button_pressed = false;
			left_mouse_button_released = true;
			draw = true;
		}
	}
}

void Tetris::StartTetris()
{
	Initialize();

	states.push_back(new MainMenuState());
	states.push_back(new PlayingState());
	states.push_back(new GameOverState());
	states.push_back(new HowToPlayState());
	states.push_back(new OptionsState());
	states.push_back(new AboutState());
	state = -1;
	ChangeState(MainMenu);

	cout << "Starting control cycle..." << endl;
	while (!done)
	{
		al_wait_for_event(event_queue, & ev);

		TrackMouse();

		/* --- UPDATING --- */
		states[state]->Update(&ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			left_mouse_button_released = false;

			draw = true;
		}

		/* --- DRAWING --- */
		if (draw && al_event_queue_is_empty(event_queue))
		{
			states[state]->Draw();

			/* -- mouse cursor -- */
			al_draw_bitmap(mouse, mouse_x, mouse_y, NULL);

			/*
			// mouse temp coords
			stringstream ss;
			ss << mouse_x << " " << mouse_y;
			al_draw_text(font, Yellow, 0, 0, NULL, ss.str().c_str());
			//cout << ss.str() << endl;
			// -----------------
			*/

			al_flip_display();
			al_clear_to_color(Black);
			draw = false;
		}

		/* if window is closed */
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			cout << "Close button pressed..." << endl;
			done = true;
		}
	}
	cout << "* done = true; *" << endl;

	Terminate();
}

void Tetris::Terminate()
{
	cout << "Deallocating memory and quitting..." << endl;

	al_destroy_font(big_font);
	al_destroy_font(regular_font);

	al_destroy_sample(lineClearSound);
	al_destroy_sample(explosionSound);
	al_destroy_sample(themeSong);

	al_destroy_event_queue(event_queue);
	al_destroy_timer(sidewaysMovementTimer);
	al_destroy_timer(softDropTimer);
	al_destroy_timer(gravityTimer);
	al_destroy_timer(timer);
	al_destroy_display(display);

	al_destroy_bitmap(mouse);

	delete instance;
}
#pragma once

/* Allegro 5 stuff */
#include "allegro5\allegro5.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

/* standard includes */
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

/* user friendly names */
#define Black al_map_rgb(0, 0, 0)
#define DarkGray al_map_rgb(64, 64, 64)
#define Gray al_map_rgb(128, 128, 128)
#define LightGray al_map_rgb(192, 192, 192)
#define Blue al_map_rgb(0, 0, 255)
#define Green al_map_rgb(0, 255, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)

/* global variables */
#define ProgramTitle "Tetris"
#define ScreenWidth 800
#define ScreenHeight 600
const double FPS = 30.0;

/* fonts */
#define ConsolaTTF "res//fonts//consola.ttf"

/* images */
#define PlayingBackground "res//images//playing_bg.png"
#define MouseCursor "res//images//mouse_cursor.png"
#define ForbiddenIcon "res//images//forbidden.png"

/* piece patterns */
#define YellowPattern "res//images//yellow-cell.png"
#define PurplePattern "res//images//purple-cell.png"
#define RedPattern "res//images//red-cell.png"
#define GreenPattern "res//images//green-cell.png"
#define BluePattern "res//images//blue-cell.png"

/* musics */
#define ThemeSong "res//musics//tetris_theme.ogg"

/* sounds */
#define LineClearSound "res//sounds//line_clear.wav"
#define ExplosionSound "res//sounds//explosion.wav"
#define OverButton "res//sounds//over_button.wav"
#define PressedButton "res//sounds//pressed_button.wav"

enum _Sound {OverButtonSound, PressedButtonSound};
#pragma once
#include "rebelle_VS\stdafx.h"

/*
	RebelleApp.h

	This file contains setup data for making the game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const int		VIEWPORT_OFFSET_X		= 0;
static const int		VIEWPORT_OFFSET_Y		= 210;
static const int		TOGGLE_OFFSET_Y			= 160;

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	YELLOW_CURSOR_PATH = L"data/gui/cursors/yellow_cursor.png";
static const wstring	RED_CURSOR_PATH = L"data/gui/cursors/red_cursor.png";

static const wstring	SPLASH_SCREEN_PATH	= L"data/gui/overlays/rebelle_splash_screen_overlay.png";
static const wstring	MAIN_MENU_PATH		= L"data/gui/overlays/rebelle_main_menu_overlay.png";
static const wstring	LOADING_LEVEL_PATH = L"data/gui/overlays/rebelle_loading_level_overlay.png";

static const wstring	START_IMAGE_PATH	= L"data/gui/buttons/start_game.png";
static const wstring	START_IMAGE_MO_PATH	= L"data/gui/buttons/start_game_mo.png";
static const wstring	EXIT_IMAGE_PATH		= L"data/gui/buttons/exit_game.png";
static const wstring	EXIT_IMAGE_MO_PATH	= L"data/gui/buttons/exit_game_mo.png";
static const wstring	CONTROLS_IMAGE_PATH = L"data/gui/buttons/display_controls.png";
static const wstring	CONTROLS_IMAGE_MO_PATH = L"data/gui/buttons/display_controls_mo.png";

// FOR OUR SPRITE
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";

// FOR THE GAME WORLD
static const float		MAX_VIEWPORT_AXIS_VELOCITY = 40.0f;
static const int		MIN_FPS = 5;
static const int		MAX_FPS = 100;
static const int		FPS_INC = 1;
static const wstring	IDLE(L"IDLE");



//// -- followings are screen artworks of ingame menu
static const wstring	INGAME_PAUSE_MENU_PATH = L"data/gui/overlays/ingame_pause_menu.png";
static const wstring	PAUSE_MENU_RESUME_PATH = L"data/gui/buttons/ingame_button_resume.png";
static const wstring	PAUSE_MENU_RESUME_MO_PATH = L"data/gui/buttons/ingame_button_resume_mouse_over.png";
static const wstring	PAUSE_MENU_EXIT_PATH = L"data/gui/buttons/ingame_button_exit.png";
static const wstring	PAUSE_MENU_EXIT_MO_PATH = L"data/gui/buttons/ingame_button_exit_mouse_over.png";
static const wstring	PAUSE_MENU_SHOW_UPGRADE_PATH = L"data/gui/buttons/show_upgrade_button.png";
static const wstring	PAUSE_MENU_SHOW_UPGRADE_MO_PATH = L"data/gui/buttons/show_upgrade_button_mouse_over.png";

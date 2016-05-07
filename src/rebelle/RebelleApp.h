#pragma once
#include "rebelle_VS\stdafx.h"

/*
	RebelleApp.h

	This file contains setup data for making the game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const int		VIEWPORT_OFFSET_X		= 0;
static const int		VIEWPORT_OFFSET_Y		= 265;
static const int		TOGGLE_OFFSET_Y			= 160;

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	YELLOW_CURSOR_PATH = L"data/gui/cursors/yellow_cursor.png";
static const wstring	RED_CURSOR_PATH = L"data/gui/cursors/red_cursor.png";

static const wstring	SPLASH_SCREEN_PATH	= L"data/gui/overlays/rebelle_splash_screen_overlay.png";
static const wstring	MAIN_MENU_PATH		= L"data/gui/overlays/rebelle_main_menu_overlay.png";
static const wstring	LOADING_LEVEL_PATH = L"data/gui/overlays/rebelle_loading_level_overlay.png";
static const wstring	CONTROLS_SCREEN_PATH = L"data/gui/overlays/controls.png";

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
static const wstring	PAUSE_MENU_DONATE_MONEY_PATH = L"data/gui/buttons/donate_money.png";
static const wstring	PAUSE_MENU_DONATE_MONEY_MO_PATH = L"data/gui/buttons/donate_money_mouse_over.png";

// artworks of donate screen
static const wstring	DONATE_SCREEN_LAYOUT_PATH = L"data/gui/overlays/donate_screen_layout.png";
static const wstring	DONATE_BUTTON_PATH = L"data/gui/buttons/donate_button.png";
static const wstring	DONATE_BUTTON_MO_PATH = L"data/gui/buttons/donate_button_mouse_over.png";
static const wstring	INCREASE_MONEY_PATH = L"data/gui/buttons/upgrade_button.png";
static const wstring	INCREASE_MONEY_MO_PATH = L"data/gui/buttons/upgrade_button_mouse_over.png";
static const wstring	DECREASE_MONEY_PATH = L"data/gui/buttons/upgrade_button_down.png";
static const wstring	DECREASE_MONEY_MO_PATH = L"data/gui/buttons/upgrade_button_mouse_over_down.png";
static const wstring	MONEY_TEXT_PATH = L"data/gui/buttons/money_text_box.png";
static const wstring	MONEY_LABEL_PATH = L"data/gui/overlays/money_label.png";
static const wstring	SCORE_LABEL_PATH = L"data/gui/overlays/score_label.png";


//// -- followings are artworks of upgrade screen
static const wstring	UPGRADE_SCREEN_LAYOUT_PATH = L"data/gui/overlays/upgrade_screen_layout.png";
static const wstring	BACK_TO_MENU_PATH = L"data/gui/buttons/back_to_menu_button.png";
static const wstring	BACK_TO_MENU_MO_PATH = L"data/gui/buttons/back_to_menu_button_mouse_over.png";
static const wstring	BACK_PATH = L"data/gui/buttons/back.png";
static const wstring	BACK_MO_PATH = L"data/gui/buttons/back_mo.png";

static const wstring	UPGRADE_BUTTON_PATH = L"data/gui/buttons/upgrade_button.png";
static const wstring	UPGRADE_BUTTON_MO_PATH = L"data/gui/buttons/upgrade_button_mouse_over.png";

static const wstring	SPEED_UPGRADE_TITLE_PATH = L"data/gui/overlays/speed_upgrade_title.png";
static const wstring	ATTACK_UPGRADE_TITLE_PATH = L"data/gui/overlays/attack_upgrade_title.png";
static const wstring	DEFENSE_UPGRADE_TITLE_PATH = L"data/gui/overlays/defense_upgrade_title.png";
static const wstring	UPGRADE_UPGRADE_TITLE_PATH = L"data/gui/overlays/upgrade_upgrade_title.png";
static const wstring	PRICE_UPGRADE_TITLE_PATH = L"data/gui/overlays/price_upgrade_title.png";
static const wstring	PURCHASE_UPGRADE_TITLE_PATH = L"data/gui/overlays/purchase_upgrade_title.png";
static const wstring	MONEY_UPGRADE_TITLE_PATH = L"data/gui/overlays/200_upgrade_title.png";

static const wstring	SPEED_ICON_PATH = L"data/gui/overlays/small_butterfly_icon.png";
static const wstring	ATTACK_ICON_PATH = L"data/gui/overlays/small_sword_icon.png";
static const wstring	DEFENSE_ICON_PATH = L"data/gui/overlays/small_armor_icon.png";

//// --- just for level-complete screen
static const wstring	LEVEL_COMPLETE_SCREEN_PATH = L"data/gui/overlays/level_complete_screen.png";
static const wstring	LEVEL_COMPLETE_BUTTON_RESUME_PATH = L"data/gui/buttons/level_complete_button_resume.png";
static const wstring	LEVEL_COMPLETE_BUTTON_RESUME_MO_PATH = L"data/gui/buttons/level_complete_button_resume_mouse_over.png";

/// -- sound effect paths
static const LPWSTR		SHOOT_SOUND_EFFECT_PATH = L"data/sounds/shoot.wav";
static const LPWSTR		MONEY_SOUND_EFFECT_PATH = L"data/sounds/money.wav";
static const LPWSTR		DAMAGE_SOUND_EFFECT_PATH = L"data/sounds/damage.wav";
static const LPWSTR		HEAL_SOUND_EFFECT_PATH = L"data/sounds/heal.wav";
static const LPWSTR		PUNCH_SOUND_EFFECT_PATH = L"data/sounds/punch.wav";

/// -- music paths
static const LPWSTR		MAIN_THEME_MUSIC_PATH = L"data/music/RebelleGameMusic.wav";
static const LPWSTR		LEVEL_COMPLETE_MUSIC_PATH = L"data/music/RebelleComplete.wav";
static const LPWSTR		GAMEOVER_MUSIC_PATH = L"data/music/RebelleGameOver.wav";
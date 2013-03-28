#ifndef Global_h
#define Global_h

#include <irrlicht.h>

using irr::f32;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const f32 MOVEMENT_SPEED = 1000.f;

const int BUTTON_WIDTH  = 494;
const int BUTTON_HEIGHT =  94;

enum GAME_STATE {
	GAME_MAINMENU_STATE = 101,
	GAME_NEWGAME_STATE,
	GAME_SETTINGS_STATE,
	GAME_HELP_STATE,
	GAME_ABOUT_STATE
};

enum NEWGAME_ELEMENT {
	NEWGAME_ROOT_NODE = 201,
	NEWGAME_BACKGROUND,
	NEWGAME_FIGHTER,
	NEWGAME_BACK_BUTTON,
	NEWGAME_PAUSE_BUTTON,
	NEWGAME_LEFT_TURBINE,
	NEWGAME_RIGHT_TURBINE
};

enum MAINMENU_ELEMENT {
	MAINMENU_ROOT_NODE = 301,
	MAINMENU_BACKGROUND,
	MAINMENU_FIGHTER,
	MAINMENU_TITLE,
	MAINMENU_NEW_GAME_BUTTON,
	MAINMENU_SETTINGS_BUTTON,
	MAINMENU_HELP_BUTTON,
	MAINMENU_ABOUT_BUTTON,
	MAINMENU_EXIT_BUTTON
};

enum ABOUT_ELEMENT {
	ABOUT_ROOT_NODE = 401,
	ABOUT_BACKGROUND,
	ABOUT_TITLE,
	ABOUT_BACK_BUTTON
};

enum SETTINGS_ELEMENT {
	SETTINGS_ROOT_NODE = 501,
	SETTINGS_BACKGROUND,
	SETTINGS_TITLE,
	SETTINGS_BACK_BUTTON
};

#endif
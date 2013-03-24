#ifndef MainMenu_h
#define MainMenu_h

#include <irrlicht.h>
#include <iostream>

using std::cout;
using std::endl;

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

enum MAINMENU_ELEMENTS {
	MAINMENU_ROOT_NODE = 101,
	MAINMENU_BACKGROUND,
	MAINMENU_FIGHTER,
	MAINMENU_TITLE,
	MAINMENU_NEW_GAME_BUTTON,
	MAINMENU_SETTINGS_BUTTON,
	MAINMENU_HELP_BUTTON,
	MAINMENU_ABOUT_BUTTON,
	MAINMENU_EXIT_BUTTON
};

class MainMenu {
	int width;
	int height;
	IVideoDriver* driver;
	IGUIEnvironment* gui;
	ISceneManager* scene;
	ISceneNode* mainMenuNode;
	bool visible;
public:
	MainMenu(IVideoDriver* vdr, IGUIEnvironment* genv, ISceneManager* scene, int sw, int sh);

	bool init();
	void setVisible(bool flg);
};

#endif
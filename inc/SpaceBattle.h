#ifndef SpaceBattle_h
#define SpaceBattle_h

#include <irrlicht.h>

using namespace irr;
using namespace io;
using namespace gui;
using namespace core;
using namespace scene;
using namespace video;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "/audiere.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
#endif

#include "Core/Global.h"
#include "Core/audiere.h"
#include "Core/StateManager.h"
#include "Core/EventReceiver.h"

using namespace audiere; //audio library

class SpaceBattle { //main game class
	IrrlichtDevice* device;
	IVideoDriver*	driver;
	ISceneManager*	 scene;
	IGUIEnvironment*   gui;

	StateManager* stateManager;
	EventReceiver* eventReceiver;

	SETTINGS_STRUCT SETTINGS; //general game settings
	f32 splashTime; //time of splash screen will be displayed
	ISceneNode* tmp; //scene node for splash screen
	bool isSplashShown;

	void loadFont(); //load font for buttons
	void showSplash(u32 time); //remove or create splash depending on isSplashShown and splashTime values
public:
	SpaceBattle(int argc, char** argv);
	~SpaceBattle();
	void run();
};

#endif
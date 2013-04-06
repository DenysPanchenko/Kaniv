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
#pragma comment(lib, "Irrlicht.lib") //link libraries
#pragma comment(lib, "audiere.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") //hide console window
#endif

#include "audiere.h" //audio API
using namespace audiere; 

#include "Global.h"
#include "StateManager.h"
#include "EventReceiver.h"

class SpaceBattle { //main game class
	IrrlichtDevice* device;
	IVideoDriver*	driver;
	ISceneManager*	 scene;
	IGUIEnvironment*   gui;

	StateManager* stateManager;
	EventReceiver* eventReceiver;

	f32 splashTime; //time of splash screen will be displayed
	ISceneNode* tmp; //scene node for splash screen
	bool isSplashShown;
	void showSplash(u32 time); //remove or create splash depending on isSplashShown and splashTime values

	SETTINGS_STRUCT SETTINGS; //general game settings
	void loadFont(); //load font for buttons
public:
	SpaceBattle(int argc, char** argv);
	~SpaceBattle();

	void run();
};

#endif
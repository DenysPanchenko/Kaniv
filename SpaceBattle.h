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

using namespace audiere;

class SpaceBattle {
	IrrlichtDevice* device;
	IVideoDriver*	driver;
	ISceneManager*	 scene;
	IGUIEnvironment*   gui;

	StateManager* stateManager;
	EventReceiver* eventReceiver;

	f32 splashTime;
	ISceneNode* tmp;
	bool isSplashShown;

	void loadFont();
	void showSplash(u32 time);
public:
	SpaceBattle(int argc, char** argv);
	~SpaceBattle();
	void run();
};

#endif
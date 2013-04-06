#ifndef EventReceiver_h
#define EventReceiver_h

#include <irrlicht.h>

#include "audiere.h"
#include "Global.h"
#include "StateManager.h"

using namespace audiere;

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;
using namespace io;

class EventReceiver : public IEventReceiver{
	IrrlichtDevice* device;
	StateManager* stateManager;
	SoundEffectPtr pushButtonSound;
	SETTINGS_STRUCT* SETTINGS;
public:
	struct MouseState{
		position2di position;
		bool leftButtonDown;
		bool rightButtonDown;
		MouseState() : leftButtonDown(false), rightButtonDown(false){};
	} currentMouseState;

	EventReceiver(IrrlichtDevice* dev = 0, StateManager* st = 0, SETTINGS_STRUCT* settings = 0);
	virtual bool OnEvent(const SEvent& ev);
	MouseState getMouseState() const;
	void showExitConfirmDialog();
	void showExitGameConfirmDialog();
};

#endif
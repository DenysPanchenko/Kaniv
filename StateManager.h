#ifndef StateManager_h
#define StateManager_h

#include <irrlicht.h>

using namespace irr;

#include "About.h"
#include "NewGame.h"
#include "MainMenu.h"
#include "Settings.h"
#include "AbstractState.h"

#include <map>

using namespace std;

class StateManager {
	IrrlichtDevice* device;
	std::map<GAME_STATE, AbstractState*> states;
	GAME_STATE currentState;
	void setCursor();
public:
	StateManager(IrrlichtDevice* dev);
	bool init();
	void setState(GAME_STATE st);
	GAME_STATE getState() const;
	void update(u32 time);
	void mouseInputEvent(EMOUSE_INPUT_EVENT event);
};

#endif
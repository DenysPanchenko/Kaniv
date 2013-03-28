#ifndef StateManager_h
#define StateManager_h

#include <irrlicht.h>

using namespace irr;

#include "About.h"
#include "NewGame.h"
#include "MainMenu.h"
#include "AbstractState.h"

#include <map>

using namespace std;

class StateManager {
	std::map<GAME_STATE, AbstractState*> states;
	GAME_STATE currentState;
	void setCursor();
public:
	StateManager();
	bool init();
	void setState(GAME_STATE st);
	GAME_STATE getState() const;
};

#endif
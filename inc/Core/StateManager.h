#ifndef StateManager_h
#define StateManager_h

#include <irrlicht.h>
using namespace irr;

//#include "audiere.h"

#include "Global.h"

#include "Help.h"
#include "About.h"
#include "NewGame.h"
#include "MainMenu.h"
#include "Settings.h"
#include "GameOver.h"
#include "AbstractState.h"

#include <map>
using namespace std;

class StateManager {
	IrrlichtDevice* device;
	std::map<GAME_STATE, AbstractState*> states;
	GAME_STATE currentState;
	SETTINGS_STRUCT* SETTINGS;
	void setCursor();

	OutputStreamPtr mainMenuMusic;
	OutputStreamPtr newGameMusic;
public:
	StateManager(IrrlichtDevice* dev, SETTINGS_STRUCT* set);
	bool init();
	void setState(GAME_STATE st);
	GAME_STATE getState() const;
	void update(u32 time);
	void setMusic();
	void mouseInputEvent(EMOUSE_INPUT_EVENT event);
};

#endif
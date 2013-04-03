#ifndef StateManager_h
#define StateManager_h

#include <irrlicht.h>

using namespace irr;

#include "../Core/audiere.h"
#include "../GameStates/Help.h"
#include "../GameStates/About.h"
#include "../GameStates/NewGame.h"
#include "../GameStates/MainMenu.h"
#include "../GameStates/Settings.h"
#include "../GameStates/GameOver.h"
#include "../GameStates/AbstractState.h"

#include <map>

using namespace std;

class StateManager {
	IrrlichtDevice* device;
	std::map<GAME_STATE, AbstractState*> states;
	GAME_STATE currentState;
	void setCursor();
	void setMusic();

	AudioDevicePtr deviceA;
	OutputStreamPtr mainMenuMusic;
	OutputStreamPtr newGameMusic;
public:
	StateManager(IrrlichtDevice* dev);
	bool init();
	void setState(GAME_STATE st);
	GAME_STATE getState() const;
	void update(u32 time);
	void mouseInputEvent(EMOUSE_INPUT_EVENT event);
};

#endif
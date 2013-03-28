#ifndef ActionManager_h
#define ActionManager_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

class ActionManager{
	f32 leftGunTime;
	f32 rightGunTime;
	bool isKeyDown[KEY_KEY_CODES_COUNT];
//	array<>
public:
	ActionManager();
	void fireAction(EMOUSE_INPUT_EVENT me);
	void fireAction(EKEY_CODE kc);
	void update(float time);
	void pause();
	void resume();
	void restart();
};

#endif
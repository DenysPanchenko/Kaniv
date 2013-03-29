#ifndef ActionManager_h
#define ActionManager_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

#include "Global.h"
#include "GameUnits\Fighter.h"
#include "GameUnits\Rocket.h"

class ActionManager{
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;
	u32 currentTime;
	u32 leftShotTime;
	u32 rightShotTime;
	bool isKeyDown[KEY_KEY_CODES_COUNT];
	array<Rocket*> rocketPool;
	IrrlichtDevice* device;
	ISceneNode* rootNode;
	void destroyRocket();
//	array<>
public:
	ActionManager(IrrlichtDevice* dev, ISceneNode* root);
	void fireAction(EMOUSE_INPUT_EVENT me);
	void fireAction(EKEY_CODE kc);
	void update(u32 time);
	void pause();
	void resume();
	void restart();
	void launchRocket(const vector3df& position, const vector3df& rotation);
};

#endif
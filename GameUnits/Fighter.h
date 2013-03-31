#ifndef Fighter_h
#define Fighter_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

#include "../Core/Global.h"

class Fighter {
	s32 LEFT_ROCKET_ID;
	s32 RIGHT_ROCKET_ID;
	IrrlichtDevice* device;
	IMeshSceneNode* ship;
public:
	Fighter(IrrlichtDevice* dev,
			ISceneNode* parent = 0,
			ISceneManager* scene = 0, 
			s32 id = NEWGAME_ELEMENT::NEWGAME_FIGHTER,
			vector3df pos = vector3df(0,0,0),
			vector3df rot = vector3df(-30,0,0));
	vector3df getLeftRocketPosition();
	vector3df getRightRocketPosition();
	void leftShot();
	void rightShot();
	//void fire();
	//void fire();
};

#endif
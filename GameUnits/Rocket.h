#ifndef Rocket_h
#define Rocket_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

#include "../Core/Global.h"

class Rocket {
	IrrlichtDevice* device;
public:
	Rocket(IrrlichtDevice* dev,
			s32 id,
			ISceneNode* parent = 0,
			vector3df pos = vector3df(0,0,0),
			vector3df rot = vector3df(0,0,0));
	void launch(const vector3df& position, const vector3df& direction);
};

#endif
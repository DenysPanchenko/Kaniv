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
	ISceneNodeAnimator* moveAnimator;
	IAnimatedMeshSceneNode* anms;
public:
	Rocket(IrrlichtDevice* dev,
			s32 id,
			ISceneNode* parent = 0,
			vector3df pos = vector3df(0,0,0),
			vector3df rot = vector3df(0,0,0));
	IAnimatedMeshSceneNode* getAnimatedMeshSceneNode();
	void remove();
	bool isMoveFinished();
	void launch(const vector3df& startPosition, const vector3df& endPosition);
};

#endif
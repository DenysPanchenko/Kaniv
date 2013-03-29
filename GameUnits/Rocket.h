#ifndef Rocket_h
#define Rocket_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

#include "../Global.h"

class Rocket {
	IrrlichtDevice* device;
	IMeshSceneNode* rocket;
	ISceneNode* root;
	ISceneNodeAnimator* anim;
	IAnimatedMeshSceneNode* anms;
	bool inMotion;
public:
	Rocket(IrrlichtDevice* dev,
			s32 id,
			bool im = false,
			ISceneNode* parent = 0,
			vector3df pos = vector3df(0,0,0),
			vector3df rot = vector3df(0,0,0));
	bool isUsing();
	void setIsUsing(bool flg);
	void launch(const vector3df& pos);
	//void fire();
	//void fire();
};

#endif
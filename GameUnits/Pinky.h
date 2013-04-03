#ifndef Pinky_h
#define Pinky_h

#include <irrlicht.h>

using namespace irr;
using namespace scene;

#include "Craft.h"

class Pinky : public Craft{
	ISceneNodeAnimator* moveAnimator;
public:
	Pinky(IrrlichtDevice* dev, ISceneNode* parent,
		s32 ID, const vector3df& position, f32 speed, u32 time, ENEMY_DIRECTION direction);
	void remove();
	bool isMoveFinished();
};

#endif
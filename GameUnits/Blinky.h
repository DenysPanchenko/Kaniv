#ifndef Blinky_h
#define Blinky_h

#include "Craft.h"

#include <cmath>

class Blinky : public Craft {
	ISceneNodeAnimator* moveAnimator;
public:
	Blinky(IrrlichtDevice* dev, ISceneNode* parent, s32 ID,
		vector3df startPosition, f32 speed, u32 time, ENEMY_DIRECTION direction, f32 f, f32 A);
	void remove();
	bool isMoveFinished();
};

#endif
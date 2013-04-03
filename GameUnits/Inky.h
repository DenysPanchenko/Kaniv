#ifndef Inky_h
#define Inky_h

#include "Craft.h"
#include "../Core/Global.h"

class Inky : public Craft {
	ISceneNodeAnimator* moveAnimator;
public:
	Inky(IrrlichtDevice* dev, ISceneNode* parent, s32 ID, vector3df startPosition, f32 speed, f32 time);
	void remove();
	bool isMoveFinished();
};

#endif
#ifndef Clyde_h
#define Clyge_h

#include "Craft.h"

class Clyde : public Craft {
	static bool alive;
	ISceneNodeAnimator* moveAnimator;
public:
	static bool isAlive();
	Clyde(IrrlichtDevice* dev, ISceneNode* parent, s32 ID,
		vector3df startPosition, f32 speed, u32 time);
	void remove();
	bool isMoveFinished();
};

#endif
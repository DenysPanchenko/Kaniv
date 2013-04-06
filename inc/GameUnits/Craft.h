#ifndef Craft_h
#define Craft_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

#include "../Core/Global.h"

class Craft {
protected:
	ISceneNode* craft;
	//ISceneNodeAnimator* moveAnimator;
	IrrlichtDevice* device;
public:
	Craft(IrrlichtDevice* dev);
	virtual ~Craft();

	ISceneNode* getSceneNode();
	virtual bool isMoveFinished();
	virtual void remove();
};

#endif
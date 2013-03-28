#ifndef NewGame_h
#define NewGame_h

#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

#include <iostream>

using std::cout;
using std::endl;

#include "GameUnits\Fighter.h"
#include "AbstractState.h"

class NewGame : public AbstractState{
	ICameraSceneNode* camera;
	ISceneNode* gameRootNode;
	IGUIEnvironment* gui;
	ISceneManager* scene;
public:
	NewGame(IrrlichtDevice* dev);
	virtual void setVisible(bool flg);
	virtual bool init();
};

#endif
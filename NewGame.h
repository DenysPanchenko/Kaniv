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
#include "ActionManager.h"
#include "AbstractState.h"

class NewGame : public AbstractState{
	Fighter* fighter;
	ActionManager* actionManager;
	ICameraSceneNode* camera;
	ISceneNode* gameRootNode;
	IGUIEnvironment* gui;
	ISceneManager* scene;
public:
	NewGame(IrrlichtDevice* dev);
	virtual void setVisible(bool flg);
	virtual bool init();
	void mouseInputEvent(EMOUSE_INPUT_EVENT event);
	void update(s32 time);
};

#endif
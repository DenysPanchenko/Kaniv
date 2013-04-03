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

#include "AbstractState.h"
#include "../Core/ActionManager.h"
#include "../GameUnits/Fighter.h"

class NewGame : public AbstractState{
	Fighter* fighter;
	ActionManager* actionManager;
	ICameraSceneNode* camera;
	ISceneNode* gameRootNode;
	IGUIEnvironment* gui;
	ISceneManager* scene;
public:
	NewGame(IrrlichtDevice* dev);
	void remove();
	virtual void setVisible(bool flg);
	virtual bool init();
	void mouseInputEvent(EMOUSE_INPUT_EVENT event);
	void update(s32 time);
};

#endif
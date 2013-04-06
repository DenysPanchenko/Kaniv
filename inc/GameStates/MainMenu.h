#ifndef MainMenu_h
#define MainMenu_h

#include <irrlicht.h>
using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

#include "AbstractState.h"

class MainMenu : public AbstractState{
	ICameraSceneNode* camera;
	IGUIEnvironment* gui;
	ISceneNode* mainMenuNode;


public:
	MainMenu(IrrlichtDevice* dev);
	virtual bool init();
	virtual void setVisible(bool flg);
};

#endif
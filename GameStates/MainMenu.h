#ifndef MainMenu_h
#define MainMenu_h

#include <irrlicht.h>
#include <iostream>

using std::cout;
using std::endl;

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

#include "../Core/audiere.h"
#include "AbstractState.h"

using namespace audiere;

class MainMenu : public AbstractState{
	ICameraSceneNode* camera;
	IGUIEnvironment* gui;
	ISceneNode* mainMenuNode;

	//bool visible;
public:
	MainMenu(IrrlichtDevice* dev);
	virtual bool init();
	virtual void setVisible(bool flg);
};

#endif
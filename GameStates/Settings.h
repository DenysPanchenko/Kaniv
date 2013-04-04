#ifndef Settings_h
#define Settings_h

#include "../GameStates/AbstractState.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

#include <iostream>

using std::cout;
using std::endl;

class Settings : public AbstractState {
	SETTINGS_STRUCT* SETTINGS;
	IGUIEnvironment* gui;
public:
	Settings(IrrlichtDevice* dev, SETTINGS_STRUCT* set);
	virtual void setVisible(bool flg);
	virtual bool init();

};

#endif
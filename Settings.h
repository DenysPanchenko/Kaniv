#ifndef Settings_h
#define Settings_h

#include "AbstractState.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

#include <iostream>

using std::cout;
using std::endl;

class Settings : public AbstractState {
	IGUIEnvironment* gui;
public:
	Settings(IrrlichtDevice* dev);
	virtual void setVisible(bool flg);
	virtual bool init();

};

#endif
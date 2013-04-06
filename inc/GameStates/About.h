#ifndef About_h
#define About_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

#include "AbstractState.h"

class About : public AbstractState{
	IGUIEnvironment* gui;
	bool visible;
public :
	About(IrrlichtDevice* dev);
	virtual bool init();
	virtual void setVisible(bool flg);
	bool isVisible() const;
};

#endif
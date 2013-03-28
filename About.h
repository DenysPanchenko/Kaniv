#ifndef About_h
#define About_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

#include "AbstractState.h"

#include <iostream>

using std::cout;
using std::endl;

class About : public AbstractState{
	IGUIEnvironment* gui;
	bool visible;
public :
	About();
	virtual bool init();
	virtual void setVisible(bool flg);
	bool isVisible() const;
};

#endif
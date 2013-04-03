#ifndef Help_h
#define Help_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

#include "AbstractState.h"

class Help : public AbstractState{
	IGUIEnvironment* gui;
	bool visible;
public :
	Help(IrrlichtDevice* dev);
	virtual bool init();
	virtual void setVisible(bool flg);
	bool isVisible() const;
};

#endif
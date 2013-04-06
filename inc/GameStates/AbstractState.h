#ifndef AbstractState_h
#define AbstractState_h

#include "../Core/Global.h"

#include <irrlicht.h>

using irr::IrrlichtDevice;

//class represented game state
class AbstractState {
protected:
	IrrlichtDevice* device;
	bool visible;
public:
	AbstractState(IrrlichtDevice* dev = 0) : device(dev) {};
	virtual bool init() = 0;
	virtual void setVisible(bool flg) = 0;
	bool isVisible() const {return visible;};
	virtual ~AbstractState(){};
};

#endif
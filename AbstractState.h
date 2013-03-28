#ifndef AbstractState_h
#define AbstractState_h

#include "Global.h"

#include <irrlicht.h>

using irr::IrrlichtDevice;

class AbstractState {
protected:
	IrrlichtDevice* device;
	bool visible;
public:
	AbstractState(IrrlichtDevice* dev = 0) : device(dev) {};
	virtual bool init() = 0;
	virtual void setVisible(bool flg) = 0;
	virtual ~AbstractState(){};
};

#endif
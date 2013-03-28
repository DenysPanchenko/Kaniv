#ifndef AbstractState_h
#define AbstractState_h

#include "Global.h"

class AbstractState {
protected:
	bool visible;
public:
	AbstractState(){};
	virtual bool init() = 0;
	virtual void setVisible(bool flg) = 0;
	virtual ~AbstractState(){};
};

#endif
#ifndef GameOver_h
#define GameOver_h

#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;
using namespace scene;

#include "AbstractState.h"

class GameOver : public AbstractState{
	IGUIEnvironment* gui;
public:
	GameOver(IrrlichtDevice* dev);
	bool init();
	void setVisible(bool flg);
};

#endif
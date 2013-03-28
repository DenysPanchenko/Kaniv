#ifndef Fighter_h
#define Fighter_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

#include "../Global.h"

class Fighter : public IMeshSceneNode{
public:
	Fighter(ISceneNode* prnt = 0,
			ISceneManager* mng = device->getSceneManager(), 
			s32 id = NEWGAME_ELEMENT::NEWGAME_FIGHTER,
			vector3df pos = vector3df(0,0,0),
			vector3df rot = vector3df(-30,0,0));
};

#endif
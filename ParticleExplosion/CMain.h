#ifndef CMAIN_H
#define CMAIN_H

#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;

void addExplosion(const irr::core::vector3df& pos, const irr::core::vector3df& rot, const irr::u32& scale, irr::scene::ISceneManager* smgr, const irr::core::plane3df& p, irr::scene::ITriangleSelector* selector);

#endif // CMAIN_H

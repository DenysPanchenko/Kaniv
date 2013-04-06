/*
  Copyright (C) 2011 Daniel Sudmann

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Daniel Sudmann suddani@googlemail.com
*/
#include "CParticleSystem.h"

#include "CTrailParticleDrawer.h"
#include "CBillboardParticleDrawer.h"
#include "COrientedParticleDrawer.h"

namespace irr
{
    namespace scene
    {
        CParticleSystem::CParticleSystem(ISceneNode* parent, ISceneManager* mgr, s32 id,
                        const core::vector3df& position,
                        const core::vector3df& rotation,
                        const core::vector3df& scale) : ISceneNode(parent, mgr, id, position, rotation, scale)
        {
            //ctor
            LastTime = 0;
            Paused = false;
        }

        CParticleSystem::~CParticleSystem()
        {
            //dtor
            for (irr::u32 i=0;i<Drawer.size();i++)
            {
                Drawer[i]->drop();
            }
            Drawer.clear();
        }

        void CParticleSystem::update(irr::u32 timeMs, irr::f32 diff)
        {
            for (irr::u32 i=0;i<Drawer.size();i++)
            {
                irr::core::vector3df camPos(0,0,0);
                if (SceneManager->getActiveCamera())
                {
                    camPos= SceneManager->getActiveCamera()->getAbsolutePosition();//SceneManager->getActiveCamera()->getTarget()-SceneManager->getActiveCamera()->getAbsolutePosition();
                    //view.normalize();
                }
                Drawer[i]->doParticles(SceneManager->getActiveCamera(), getAbsoluteTransformation(), timeMs, Paused ? 0.f : diff);
            }
        }

        void CParticleSystem::addDrawer(CParticleDrawer* drawer)
        {
            if (drawer)
            {
                drawer->grab();
                Drawer.push_back(drawer);
            }
        }

        CParticleDrawer* CParticleSystem::getDrawer(const irr::u32& id)
        {
            if (id < Drawer.size())
                return Drawer[id];
            return 0;
        }

        CParticleDrawer* CParticleSystem::addTrailParticleDrawer(void)
        {
            CParticleDrawer* drawer = new CTrailParticleDrawer();
            addDrawer(drawer);
            drawer->drop();
            return drawer;
        }

        CParticleDrawer* CParticleSystem::addParticleDrawer(void)
        {
            CParticleDrawer* drawer = new CBillboardParticleDrawer();
            addDrawer(drawer);
            drawer->drop();
            return drawer;
        }

        CParticleDrawer* CParticleSystem::addOrientedParticleDrawer(void)
        {
            CParticleDrawer* drawer = new COrientedParticleDrawer();
            addDrawer(drawer);
            drawer->drop();
            return drawer;
        }

        void CParticleSystem::OnRegisterSceneNode(void)
        {
            if (isVisible())
                SceneManager->registerNodeForRendering(this);
            ISceneNode::OnRegisterSceneNode();
        }

        void CParticleSystem::OnAnimate(u32 timeMs)
        {
            if (LastTime == 0)
            {
                LastTime = timeMs;
                return;
            }
            irr::f32 diff = timeMs-LastTime;
            diff /= 1000.f;
            update(timeMs, diff);
            ISceneNode::OnAnimate(timeMs);
            LastTime = timeMs;
        }

        void CParticleSystem::render(void)
        {
            for (u32 i=0;i<Drawer.size();++i)
            {
                Drawer[i]->drawParticles(AbsoluteTransformation, SceneManager->getVideoDriver());
            }
        }

        const core::aabbox3d<f32>& CParticleSystem::getBoundingBox() const
        {
            return Box;
        }

        video::SMaterial& CParticleSystem::getMaterial(u32 num)
        {
            if (num < Drawer.size())
                return Drawer[num]->getMaterial();
            return video::IdentityMaterial;
        }

        u32 CParticleSystem::getMaterialCount() const
        {
            return Drawer.size();
        }
    }
}

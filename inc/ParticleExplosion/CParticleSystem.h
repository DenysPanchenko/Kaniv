#ifndef CPARTICLESYSTEM_H
#define CPARTICLESYSTEM_H

#include <irrlicht.h>
class CParticleDrawer;
namespace irr
{
    namespace scene
    {
        class CParticleSystem : public irr::scene::ISceneNode
        {
        public:

            CParticleSystem(ISceneNode* parent, ISceneManager* mgr, s32 id=-1,
                        const core::vector3df& position = core::vector3df(0,0,0),
                        const core::vector3df& rotation = core::vector3df(0,0,0),
                        const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));
            virtual ~CParticleSystem();

            void addDrawer(CParticleDrawer* drawer);
            CParticleDrawer* getDrawer(const irr::u32& id);

            CParticleDrawer* addTrailParticleDrawer(void);
            CParticleDrawer* addParticleDrawer(void);
            CParticleDrawer* addOrientedParticleDrawer(void);

            bool Paused;

            //ISceneNode
            void OnRegisterSceneNode(void);
            void OnAnimate(u32 timeMs);
            void render(void);
            const core::aabbox3d<f32>& getBoundingBox() const;
            video::SMaterial& getMaterial(u32 num);
            u32 getMaterialCount() const;
        protected:
            void update(irr::u32 timeMs, irr::f32 diff);

            irr::core::array<CParticleDrawer*> Drawer;

            core::aabbox3d<f32> Box;

            u32 LastTime;
        private:
        };
    }
}

#endif // CPARTICLESYSTEM_H

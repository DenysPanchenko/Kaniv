#ifndef CTRAILPARTICLEDRAWER_H
#define CTRAILPARTICLEDRAWER_H

#include "CParticleDrawer.h"

class CTrailParticleDrawer : public CParticleDrawer
{
    public:
        CTrailParticleDrawer();
        virtual ~CTrailParticleDrawer();

        //void doParticles(const irr::core::vector3df& view, const irr::core::matrix4& transform, irr::u32 timeMs, irr::f32 diff);

        void createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform);
    protected:
    private:
};

#endif // CTRAILPARTICLEDRAWER_H

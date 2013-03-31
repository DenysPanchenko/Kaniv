#ifndef CPARTICLEDRAWER_H
#define CPARTICLEDRAWER_H

#include <irrlicht.h>
#include "Particle.h"

class CParticleAffector : public irr::IReferenceCounted
{
public:
    CParticleAffector(void){}
    virtual ~CParticleAffector(void){}

    virtual void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff) = 0;
};

class CParticleEmitter;
class CParticleDrawer : public irr::IReferenceCounted
{
public:
    CParticleDrawer(void);
    virtual ~CParticleDrawer(void);

    irr::video::SMaterial& getMaterial(void);

    void addUVCoords(const SParticleUV& coord);

    void doParticles(const irr::scene::ICameraSceneNode* camera, const irr::core::matrix4& transform, irr::u32 timeMs, irr::f32 diff);

    virtual void createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform) = 0;

    virtual void drawParticles(irr::core::matrix4& transform, irr::video::IVideoDriver* driver);

    void setEmitter(CParticleEmitter* emitter);

    CParticleEmitter* getEmitter(void);

    void addAffector(CParticleAffector* affector);

protected:
    irr::scene::SMeshBuffer Buffer;
    irr::video::SMaterial Material;
    CParticleEmitter* Emitter;

    irr::core::list<Particle*> Particles;
    irr::core::list<Particle*> ParticlePool;

    irr::core::list<CParticleAffector*> Affectors;
    irr::core::array<SParticleUV> UVCoords;

    virtual void rellocateBuffer(irr::u32 particleCount = 0);
    irr::u32 ParticleCount;
};

#endif // CPARTICLEDRAWER_H

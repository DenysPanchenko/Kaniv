#ifndef CPARTICLEEMITTER_H
#define CPARTICLEEMITTER_H

#include <irrlicht.h>
#include "Particle.h"

class CEmitterRegion : public irr::IReferenceCounted
{
public:
    CEmitterRegion(void)
    {
    }
    virtual ~CEmitterRegion(void)
    {
    }
    virtual irr::core::vector3df getPoint(const irr::core::matrix4& transform) = 0;
};

class CParticleEmitter : public irr::IReferenceCounted
{
public:
    CParticleEmitter(void);
    virtual ~CParticleEmitter(void);

    virtual void emitt(const irr::core::matrix4& transform, irr::core::list<Particle*>& particles, irr::core::list<Particle*>& particlepool, irr::u32 timeMs, irr::f32 diff, const irr::core::array<SParticleUV>& coords) = 0;

    const irr::u32& getMaxParticleEmitt(void) const;
    const irr::u32& getParticleEmitted(void) const;
    const irr::u32& getMaxParticlesPerSecond(void) const;
    const irr::u32& getMinParticlesPerSecond(void) const;
    const irr::u32& getMaxLifeTime(void) const;
    const irr::u32& getMinLifeTime(void) const;

    void setColor(const irr::video::SColor& min, const irr::video::SColor& max);
    const irr::video::SColor& getMinColor(void) const;
    const irr::video::SColor& getMaxColor(void) const;

    void setMaxAngleDegrees(const irr::core::vector3di& speed);
    const irr::core::vector3di& getMaxAngleDegrees(void) const;

    void setSpeed(const irr::core::vector3df& speed);
    const irr::core::vector3df& getSpeed(void) const;

    void setRotation(const irr::core::vector3df& rot);
    const irr::core::vector3df& getRotation(void) const;

    void setRotationSpeed(const irr::core::vector3df& rotspeed);
    const irr::core::vector3df& getRotationSpeed(void) const;

    void setSize(const irr::core::vector2df& min, const irr::core::vector2df& max);
    const irr::core::vector2df& getMinSize(void) const;
    const irr::core::vector2df& getMaxSize(void) const;

    void setSizeSpeed(const irr::core::vector2df& speed);
    const irr::core::vector2df& getSizeSpeed(void) const;

    bool emittAll(void)
    {
        if (MinParticlesPerSecond == 0 && ParticlesEmitted < MaxParticleEmitt)
            return true;
        return false;
    }
protected:
    irr::f32 Time;

    irr::core::vector3di MaxAngleDegrees;

    irr::u32 MaxParticleEmitt;
    irr::u32 ParticlesEmitted;

    irr::u32 MinParticlesPerSecond;
    irr::u32 MaxParticlesPerSecond;

    irr::core::vector3df Speed;

    irr::core::vector3df Rotation;
    irr::core::vector3df RotationSpeed;

    irr::core::vector2df MinSize;
    irr::core::vector2df MaxSize;
    irr::core::vector2df SizeSpeed;

    irr::video::SColor MinColor;
    irr::video::SColor MaxColor;

    irr::u32 MinLifeTime;
    irr::u32 MaxLifeTime;

    Particle* create(irr::core::list<Particle*>& particlepool, const irr::core::vector3df& pos, const irr::core::vector3df& speed, const irr::core::vector3df& rot, const irr::core::vector3df& rotSpeed, const irr::core::vector2df& size, const irr::core::vector2df& sizespeed, const irr::video::SColor& color, const irr::u32& start, const irr::u32& end);
    irr::core::vector3df rotateVec(const irr::core::vector3df& vec);
    bool doEmitt(irr::f32 diff);
    virtual void emittParticleStandard(const irr::core::vector3df& pos, const irr::core::matrix4& transform, irr::core::list<Particle*>& particles, irr::core::list<Particle*>& particlepool, irr::u32 timeMs, const irr::core::array<SParticleUV>& coords);
};

#endif // CPARTICLEEMITTER_H

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
#include "CMain.h"
#include "CParticleSystem.h"
#include "CParticleEmitter.h"
#include "CParticleDrawer.h"

class ColorAffector : public CParticleAffector
{
public:
    ColorAffector(const irr::video::SColor& targetColor)
    {
        Target = targetColor;
    }
    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff)
    {
        irr::f32 lifeTime = particle->LifeTime;//particle->DestroyTimeMs-particle->CreateTimeMs;
        irr::f32 livedTime = particle->TimeLived;//timeMs-particle->CreateTimeMs;

        particle->Color = Target.getInterpolated(particle->StartColor, livedTime/lifeTime);
    }
    irr::video::SColor Target;

};


class ColorAffectorQ : public CParticleAffector
{
public:
    ColorAffectorQ(const irr::video::SColor& targetColor0, const irr::video::SColor& targetColor1)
    {
        Target0 = targetColor0;
        Target1 = targetColor1;
    }
    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff)
    {
        irr::f32 lifeTime = particle->LifeTime;//particle->DestroyTimeMs-particle->CreateTimeMs;
        irr::f32 livedTime = particle->TimeLived;//timeMs-particle->CreateTimeMs;


        particle->Color = particle->StartColor.getInterpolated_quadratic(Target0, Target1, livedTime/lifeTime);
    }
    irr::video::SColor Target0;
    irr::video::SColor Target1;

};

class GravityAffector : public CParticleAffector
{
public:
    GravityAffector(const irr::core::vector3df& gravity)
    {
        Gravity = gravity;
    }
    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff)
    {
        particle->Speed += Gravity*diff;
    }
    irr::core::vector3df Gravity;

};

class PlaneCollisionAffector : public CParticleAffector
{
public:
    PlaneCollisionAffector(const irr::core::plane3df& plane)
    {
        Plane = plane;
    }
    void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff)
    {
        irr::core::vector3df collision;
        if (Plane.getIntersectionWithLimitedLine(particle->Position, particle->Position+particle->Speed*diff, collision))
        {
            irr::core::vector3df r = particle->Speed-(2*particle->Speed.dotProduct(Plane.Normal))*Plane.Normal;
            particle->Speed = r*0.5f;
        }
    }
    irr::core::plane3df Plane;
};

class CParticleEmitterPoint : public CParticleEmitter
{
public:
    CParticleEmitterPoint(const irr::core::vector3df& rotation = irr::core::vector3df(0,0,0), const irr::core::vector3df& rotationspeed = irr::core::vector3df(0,0,0), const irr::core::vector3df& speed = irr::core::vector3df(0,1,0), const irr::core::vector3di& maxAngle = irr::core::vector3di(45,0,45), const irr::u32& minPpS = 50, const irr::u32& maxPpS = 100, const irr::u32& maxEmitt = 100, const irr::u32& minlifetime = 100, const irr::u32& maxlifetime = 1000, const irr::core::vector2df& minsize = irr::core::vector2df(1,1), const irr::core::vector2df& maxsize = irr::core::vector2df(1,1), const irr::core::vector2df& sizespeed = irr::core::vector2df(0,0), const irr::video::SColor& minColor = irr::video::SColor(255,255,255,255), const irr::video::SColor& maxColor = irr::video::SColor(255,255,255,255))
    {
        Speed = speed;

        Rotation = rotation;
        RotationSpeed = rotationspeed;

        MaxParticlesPerSecond = maxPpS;
        MinParticlesPerSecond = minPpS;

        MaxAngleDegrees = maxAngle;

        MinLifeTime = minlifetime;
        MaxLifeTime = maxlifetime;

        MinSize = minsize;
        MaxSize = maxsize;
        SizeSpeed = sizespeed;

        MinColor = minColor;
        MaxColor = maxColor;

        MaxParticleEmitt = maxEmitt;
    }
    virtual ~CParticleEmitterPoint(void) {}

    void emitt(const irr::core::matrix4& transform, irr::core::list<Particle*>& particles, irr::core::list<Particle*>& particlepool, irr::u32 timeMs, irr::f32 diff, const irr::core::array<SParticleUV>& coords)
    {
        if (doEmitt(diff))
        {
            emittParticleStandard(transform.getTranslation(), transform, particles, particlepool, timeMs, coords);
        }
    }
};

void addExplosion(const irr::core::vector3df& pos, const irr::core::vector3df& rot, const irr::u32& scale, irr::scene::ISceneManager* smgr, const irr::core::plane3df& p, irr::scene::ITriangleSelector* selector)
{
    irr::scene::CParticleSystem* system = new irr::scene::CParticleSystem(smgr->getRootSceneNode(), smgr, 6);
    system->setPosition(pos);
    system->setRotation(rot);
	system->setScale(irr::core::vector3df((irr::f32)scale));
    system->updateAbsolutePosition();

    ///Spark Trails
    CParticleDrawer* drawer = system->addTrailParticleDrawer();

    SParticleUV uv(irr::core::vector2df(0.75f,0.75f), irr::core::vector2df(1.0f,0.75f), irr::core::vector2df(0.75f,1.0f), irr::core::vector2df(1.0f,1.0f));
    uv.turnRight();
    drawer->addUVCoords(uv);

    CParticleEmitter* emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3df(0,15,0), irr::core::vector3di(180, 0, 180), 0, 500, 30, 500, 1200, irr::core::vector2df(1.0), irr::core::vector2df(1.5), irr::core::vector2df(0,0), irr::video::SColor(255,255,255,0), irr::video::SColor(255,255,255,0));
    drawer->setEmitter(emitter);
    emitter->drop();

    CParticleAffector* affector = new ColorAffector(irr::video::SColor(0,100,50,0));
    drawer->addAffector(affector);
    affector->drop();

    ///Smoke Trails
    drawer = system->addTrailParticleDrawer();

    uv = SParticleUV(irr::core::vector2df(0.0f,0.5f), irr::core::vector2df(0.5f, 0.5f), irr::core::vector2df(0.0f,0.5f+0.125f), irr::core::vector2df(0.5f,0.5f+0.125f));
    uv.turnRight();
    drawer->addUVCoords(uv);
    uv = SParticleUV(irr::core::vector2df(0.0f,0.5f+0.125f), irr::core::vector2df(0.5f, 0.5f+0.125f), irr::core::vector2df(0.0f,0.5f+0.125f+0.125f), irr::core::vector2df(0.5f,0.5f+0.125f+0.125f));
    uv.turnRight();
    drawer->addUVCoords(uv);
    uv = SParticleUV(irr::core::vector2df(0.0f,0.5f+0.125f+0.125f), irr::core::vector2df(0.5f, 0.5f+0.125f+0.125f), irr::core::vector2df(0.0f,0.5f+0.125f+0.125f+0.125f), irr::core::vector2df(0.5f,0.5f+0.125f+0.125f+0.125f));
    uv.turnRight();
    drawer->addUVCoords(uv);

    emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3df(0,10,0), irr::core::vector3di(180, 0, 180), 0, 500, 10, 400, 600, irr::core::vector2df(0.25,1.0), irr::core::vector2df(0.25,1.0), irr::core::vector2df(2.f), irr::video::SColor(255,255,128,50), irr::video::SColor(255,255,128,50));
    drawer->setEmitter(emitter);
    emitter->drop();

    affector = new ColorAffectorQ(irr::video::SColor(128,128,128,50), irr::video::SColor(0,0,0,0));
    drawer->addAffector(affector);
    affector->drop();

    ///Debris
    drawer = system->addParticleDrawer();

    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f,0.5f), irr::core::vector2df(0.5f+0.0833f,0.5f), irr::core::vector2df(0.5f,0.5f+0.0833f), irr::core::vector2df(0.5f+0.0833f,0.5f+0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f+0.0833f,0.5f), irr::core::vector2df(0.5f+0.0833f+0.0833f,0.5f), irr::core::vector2df(0.5f+0.0833f,0.5f+0.0833f), irr::core::vector2df(0.5f+0.0833f+0.0833f,0.5f+0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f+0.0833f+0.0833f,0.5f), irr::core::vector2df(0.5f+0.0833f+0.0833f+0.0833f,0.5f), irr::core::vector2df(0.5f+0.0833f+0.0833f,0.5f+0.0833f), irr::core::vector2df(0.5f+0.0833f+0.0833f+0.0833f,0.5f+0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f,0.5f+0.0833f), irr::core::vector2df(0.5f+0.0833f,0.5f+0.0833f), irr::core::vector2df(0.5f,0.5f+0.0833f+0.0833f), irr::core::vector2df(0.5f+0.0833f,0.5f+0.0833f+0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f,0.5f+0.0833f+0.0833f), irr::core::vector2df(0.5f+0.0833f,0.5f+0.0833f+0.0833f), irr::core::vector2df(0.5f,0.5f+0.0833f+0.0833f+0.0833f), irr::core::vector2df(0.5f+0.0833f,0.5f+0.0833f+0.0833f+0.0833f)));

    emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(1,0,0), irr::core::vector3df(0,12,0), irr::core::vector3di(45, 0, 45), 0, 400, 10, 2000, 3000, irr::core::vector2df(0.2f,0.2f), irr::core::vector2df(0.5f,0.5f), irr::core::vector2df(0,0), irr::video::SColor(255,255,100,0), irr::video::SColor(255,255,100,0));
    drawer->setEmitter(emitter);
    emitter->drop();

    affector = new ColorAffectorQ(irr::video::SColor(255,50,50,50), irr::video::SColor(255,50,50,50));
    drawer->addAffector(affector);
    affector->drop();
    affector = new GravityAffector(irr::core::vector3df(0.f,-15.0f,0.f));
    drawer->addAffector(affector);
    affector->drop();
    affector = new PlaneCollisionAffector(p);
    drawer->addAffector(affector);
    affector->drop();

    ///Wave Emitter
    drawer = system->addOrientedParticleDrawer();
    drawer->getMaterial().BackfaceCulling = false;

    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.75f,0.5f), irr::core::vector2df(1.0f,0.5f), irr::core::vector2df(0.75f,0.75f), irr::core::vector2df(1.0f,0.75f)));

    emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3di(0), 20, 50, 1, 500, 500, irr::core::vector2df(2.5,2.5), irr::core::vector2df(2.5,2.5), irr::core::vector2df(15), irr::video::SColor(255,200,100,0), irr::video::SColor(255,200,128,0));
    drawer->setEmitter(emitter);
    emitter->drop();

    affector = new ColorAffector(irr::video::SColor(0,100,10,0));
    drawer->addAffector(affector);
    affector->drop();

    ///Fire/Smoke
    drawer = system->addParticleDrawer();

    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.0f,0.0f), irr::core::vector2df(0.25f,0.0f), irr::core::vector2df(0.0f,0.25f), irr::core::vector2df(0.25f,0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.25f,0.25f), irr::core::vector2df(0.5f,0.25f), irr::core::vector2df(0.25f,0.5f), irr::core::vector2df(0.5f,0.5f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.25f,0.0f), irr::core::vector2df(0.5f,0.0f), irr::core::vector2df(0.25f,0.25f), irr::core::vector2df(0.5f,0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.0f,0.25f), irr::core::vector2df(0.25f,0.25f), irr::core::vector2df(0.0f,0.5f), irr::core::vector2df(0.25f,0.5f)));

    emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(1,0,0), irr::core::vector3df(2,0,0), irr::core::vector3di(0, 180, 0), 200, 400, 50, 1000, 1200, irr::core::vector2df(1,1), irr::core::vector2df(2,2), irr::core::vector2df(2), irr::video::SColor(255,200,180,0), irr::video::SColor(255,200,180,0));
    drawer->setEmitter(emitter);
    emitter->drop();

    affector = new ColorAffectorQ(irr::video::SColor(255, 100, 0, 0), irr::video::SColor(0,0,0,0));
    drawer->addAffector(affector);
    affector->drop();
    affector = new GravityAffector(irr::core::vector3df(0.f,10.0f,0.f));
    drawer->addAffector(affector);
    affector->drop();

    ///Spark Emitter
    drawer = system->addParticleDrawer();

    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f,0.75f), irr::core::vector2df(0.75f,0.75f), irr::core::vector2df(0.5f,1.0f), irr::core::vector2df(0.75f,1.0f)));

    emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3df(0,6,0), irr::core::vector3di(90, 0, 90), 20, 50, 10, 1000, 1200, irr::core::vector2df(1.5, 1.5), irr::core::vector2df(2.0, 2.0), irr::core::vector2df(1,1), irr::video::SColor(255,255,128,0), irr::video::SColor(255,255,128,0));
    drawer->setEmitter(emitter);
    emitter->drop();

    affector = new GravityAffector(irr::core::vector3df(0.f,0.8f,0.f));
    drawer->addAffector(affector);
    affector->drop();
    affector = new ColorAffector(irr::video::SColor(0,255,128,0));
    drawer->addAffector(affector);
    affector->drop();

    ///Flash Emitter
    drawer = system->addParticleDrawer();

    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5,0), irr::core::vector2df(0.75,0), irr::core::vector2df(0.5,0.25), irr::core::vector2df(0.75f,0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5+0.25f,0), irr::core::vector2df(0.75+0.25f,0), irr::core::vector2df(0.5+0.25f,0.25), irr::core::vector2df(0.75f+0.25f,0.25f)));

    emitter = new CParticleEmitterPoint(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0), irr::core::vector3di(0), 20, 50, 5, 200, 300, irr::core::vector2df(1,1), irr::core::vector2df(1,1), irr::core::vector2df(3), irr::video::SColor(255,255,255,100), irr::video::SColor(255,255, 255,100));
    drawer->setEmitter(emitter);
    emitter->drop();

    affector = new ColorAffector(irr::video::SColor(0,255, 255,100));
    drawer->addAffector(affector);
    affector->drop();

    for (irr::u32 i=0; i<system->getMaterialCount(); ++i)
    {
        system->getMaterial(i).MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
        system->getMaterial(i).setTexture(0, smgr->getVideoDriver()->getTexture("/fig7_alpha.png"));
        system->getMaterial(i).setFlag(irr::video::EMF_LIGHTING, false);
        system->getMaterial(i).setFlag(irr::video::EMF_ZWRITE_ENABLE, false);
        system->getMaterial(i).MaterialTypeParam = irr::video::pack_textureBlendFunc (irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_VERTEX_COLOR | irr::video::EAS_TEXTURE );
    }

    irr::scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(3000);
    system->addAnimator(anim);
    anim->drop();

    system->drop();
}

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
#include "CParticleDrawer.h"
#include "CParticleEmitter.h"

CParticleDrawer::CParticleDrawer()
{
    //ctor
    Emitter = 0;
    ParticleCount = 0;

    Buffer.setHardwareMappingHint(irr::scene::EHM_NEVER, irr::scene::EBT_VERTEX_AND_INDEX);
    //Buffer.setHardwareMappingHint(irr::scene::EHM_DYNAMIC, irr::scene::EBT_INDEX);
    //Buffer.setHardwareMappingHint(irr::scene::EHM_STREAM, irr::scene::EBT_VERTEX);
}

CParticleDrawer::~CParticleDrawer()
{
    //dtor
    irr::core::list<Particle*>::Iterator it = Particles.begin();
    while (it != Particles.end())
    {
        (*it)->drop();
        ++it;
    }
    Particles.clear();

    it = ParticlePool.begin();
    while (it != ParticlePool.end())
    {
        (*it)->drop();
        ++it;
    }
    ParticlePool.clear();

    irr::core::list<CParticleAffector*>::Iterator at = Affectors.begin();
    while (at != Affectors.end())
    {
        (*at)->drop();
        ++at;
    }
    Affectors.clear();
}

void CParticleDrawer::drawParticles(irr::core::matrix4& transform, irr::video::IVideoDriver* driver)
{
    driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);

    driver->setMaterial(getMaterial());

    driver->drawVertexPrimitiveList(Buffer.getVertices(), ParticleCount*4,
		Buffer.getIndices(), ParticleCount*2, irr::video::EVT_STANDARD, irr::scene::EPT_TRIANGLES, Buffer.getIndexType());
}

irr::video::SMaterial& CParticleDrawer::getMaterial(void)
{
    return Material;
}

void CParticleDrawer::addUVCoords(const SParticleUV& coord)
{
    UVCoords.push_back(coord);
}

void CParticleDrawer::doParticles(const irr::scene::ICameraSceneNode* camera, const irr::core::matrix4& transform, irr::u32 timeMs, irr::f32 diff)
{
    ///Emitt new particles
    if (Emitter && diff != 0.f)
    {
        bool d = true;
        while(d)
        {
            Emitter->emitt(transform, Particles, ParticlePool, timeMs, diff, UVCoords);
            d = Emitter->emittAll();
        }
    }

    rellocateBuffer();

    irr::core::matrix4 viewMatrix = camera->getViewFrustum()->getTransform( irr::video::ETS_VIEW );
    irr::core::vector3df campos = camera->getAbsolutePosition();

    ///Remove Dead Particles
    irr::core::list<Particle*>::Iterator it = Particles.begin();
    irr::u32 idx = 0;
    while (it != Particles.end())
    {
        if ((*it)->TimeLived >= (*it)->LifeTime && diff != 0.f)
        {
            ParticlePool.push_back(*it);

            it = Particles.erase(it);
        }
        else
        {
            //Animate remaining
            Particle* particle = *it;

            if (particle->CreateTimeMs != timeMs)
            {
                particle->TimeLived += diff;

                irr::core::list<CParticleAffector*>::Iterator at = Affectors.begin();
                while (at != Affectors.end() && diff != 0.f)
                {
                    (*at)->affect(particle, timeMs, diff);
                    ++at;
                }

                particle->Position += particle->Speed*diff;
                particle->Size += particle->SizeSpeed*diff;
                particle->Rotation += particle->RotationSpeed*diff;
            }
            irr::core::vector3df view = particle->Position-campos;
            view.normalize();
            createParticle(idx, particle, view, viewMatrix);

            idx++;
            ++it;
        }
    }

    ParticleCount = idx;
    if (idx > 0)
        Buffer.setDirty(irr::scene::EBT_VERTEX);
}

void CParticleDrawer::setEmitter(CParticleEmitter* emitter)
{
    if (emitter)
    {
        emitter->grab();
        if (emitter->getMaxParticleEmitt())
            rellocateBuffer(emitter->getMaxParticleEmitt());
        else
            rellocateBuffer(emitter->getMaxLifeTime()/1000.f*emitter->getMaxParticlesPerSecond());
    }
    if (Emitter)
        Emitter->drop();
    Emitter = emitter;
}

CParticleEmitter* CParticleDrawer::getEmitter(void)
{
    return Emitter;
}

void CParticleDrawer::addAffector(CParticleAffector* affector)
{
    if (affector)
    {
        affector->grab();
        Affectors.push_back(affector);
    }
}

void CParticleDrawer::rellocateBuffer(irr::u32 particleCount)
{
    irr::u32 size = particleCount;
    if (size == 0)
        size = Particles.size();
    while (Particles.size()+ParticlePool.size() < size)
    {
        ParticlePool.push_back(new Particle());
    }
    bool bufferDirty = false;
    while (Buffer.Vertices.size() < size*4 || Buffer.Indices.size() < size*6)
    {
        bufferDirty = true;

        Buffer.Vertices.push_back(irr::video::S3DVertex());
        Buffer.Vertices.push_back(irr::video::S3DVertex());
        Buffer.Vertices.push_back(irr::video::S3DVertex());
        Buffer.Vertices.push_back(irr::video::S3DVertex());

        Buffer.Indices.push_back(Buffer.Vertices.size()-4);
        Buffer.Indices.push_back(Buffer.Vertices.size()-3);
        Buffer.Indices.push_back(Buffer.Vertices.size()-2);

        Buffer.Indices.push_back(Buffer.Vertices.size()-2);
        Buffer.Indices.push_back(Buffer.Vertices.size()-3);
        Buffer.Indices.push_back(Buffer.Vertices.size()-1);
    }
    if (bufferDirty)
    {
        //Buffer.setDirty(irr::scene::EBT_VERTEX_AND_INDEX);
        /*
        printf("SetIndexAndVertexData Dirty\n");
        if (rand()%2 == 0)
            printf("\n");
        */
    }
}

#include "Rocket.h"

Rocket::Rocket(IrrlichtDevice* device, s32 id, ISceneNode* parent, vector3df position, vector3df destination) {
	ISceneManager* scene = device->getSceneManager();

	anms = scene->addAnimatedMeshSceneNode(
		scene->getMesh("/rocket.irrmesh"), parent, id, position);
	anms->setLoopMode(false);

	//anms->setDebugDataVisible(scene::EDS_BBOX);

	//ATTENTION!
	//rocket removal should be implemented with callbacks like this
	//
	//anms->setAnimationEndCallback(new MyIAnimationEndCallBack);
	//
	//but it doesn't work ='(

	IParticleSystemSceneNode* fire = scene->addParticleSystemSceneNode( //create fire tail
		false, anms, -2, vector3df(0,0,0), vector3df(-150,0,0));

	IParticleEmitter* emitter = fire->createBoxEmitter( //create emitter for fire for fire tail
		aabbox3df(-1, 0,-1, 1, 1, 1),
		vector3df(0.0f, -0.03f, 0.0f),
		600, 800,
		SColor(0,255,255,255),SColor(0,255,255,255),
		50, 100, 0,
		dimension2df(5,5), dimension2df(5,5));

	IParticleFadeOutAffector* paf = fire->createFadeOutParticleAffector();
	paf->setFadeOutTime(100);

	fire->addAffector(paf);

	//apply emitter to turbines
	fire->setEmitter(emitter);

	fire->setMaterialFlag(video::EMF_LIGHTING, false);
	fire->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	fire->setMaterialTexture(0, device->getVideoDriver()->getTexture("/brightfire.jpg"));
	fire->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	if(anms){
		moveAnimator = scene->createFlyStraightAnimator(
			position, destination, (destination.Y - position.Y) / ROCKET_SPEED);
		if(moveAnimator){
			anms->addAnimator(moveAnimator);
			moveAnimator->drop();
		}
	}
}

IAnimatedMeshSceneNode* Rocket::getAnimatedMeshSceneNode(){
	return anms;
}

void Rocket::launch(const vector3df& position, const vector3df& direction){
	//
}

void Rocket::remove(){
	anms->remove();
}

bool Rocket::isMoveFinished(){
	return moveAnimator->hasFinished();
}
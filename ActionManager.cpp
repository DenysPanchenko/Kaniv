#include "ActionManager.h"

ActionManager::ActionManager(IrrlichtDevice* dev, ISceneNode* root){
	//if(!scene) log << "NULL cout" << endl;
	rootNode = root;
	device = dev;
	leftShotTime = 0;
	rightShotTime = 0;
	currentTime = 0;
	leftPressed = false;
	rightPressed = false;
	/*
	for(int i = 0; i < 10; i++)
		rocketPool.push_back(new Rocket(device,ROCKET_THRESHOLD + i, false, root));
	*/
}

void ActionManager::launchRocket(const vector3df& position, const vector3df& rotation){
	ISceneManager* scene = device->getSceneManager();
	ISceneNodeAnimator* anim;
	IAnimatedMeshSceneNode* anms;

	anms = scene->addAnimatedMeshSceneNode(
		scene->getMesh("/rocket.irrmesh"),
		rootNode, -2, position, rotation);

	IParticleSystemSceneNode* fire = scene->addParticleSystemSceneNode(false, anms, -2,vector3df(0,0,0),vector3df(-150,0,0));

	//create emitter for fire for turbines
	IParticleEmitter* emitter = fire->createBoxEmitter(
		aabbox3df(-1,0,-1,1,1,1),
		vector3df(0.0f, -0.03f, 0.0f),
		600, 800,
		SColor(0,255,255,255),SColor(0,255,255,255),
		100, 200, 0,
		dimension2df(5,5), dimension2df(5,5)
		);

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
		anim = scene->createFlyStraightAnimator(
			position, vector3df(position.X, SCREEN_HEIGHT, position.Z),10000);
		if(anim){
			anms->addAnimator(anim);
			anim->drop();
		}
	}
}

void ActionManager::fireAction(EMOUSE_INPUT_EVENT me){
	ISceneNode* fighter = device->getSceneManager()->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER);
	if(me == EMIE_LMOUSE_PRESSED_DOWN){
		leftPressed = true;
		if(currentTime - leftShotTime > RESPONSE_TIME){
			launchRocket(fighter->getPosition() + vector3df(-17.0, -11.1, -5.0), vector3df(0.0, 0.0, 0.0));
			leftShotTime = currentTime;
		}
	} else if(me == EMIE_RMOUSE_PRESSED_DOWN){
		rightPressed = true;
		if(currentTime - rightShotTime > RESPONSE_TIME){
			launchRocket(fighter->getPosition() + vector3df(16.5, -11.0, -6.0), vector3df(0.0, 0.0, 0.0));
			rightShotTime = currentTime;
		}
	}
}

void ActionManager::fireAction(EKEY_CODE kc){

}

void ActionManager::pause(){
};

void ActionManager::resume(){
};

void ActionManager::restart(){
};

void ActionManager::update(u32 time){
	currentTime = time;
}
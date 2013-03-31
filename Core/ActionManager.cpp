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

	ISceneManager* scene = device->getSceneManager();
	ISceneNode* fighter = scene->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER);
	//fighter->setDebugDataVisible(scene::EDS_BBOX);

	craftPool.push_back(fighter);

	ISceneNode* enemy = scene->addMeshSceneNode(scene->getMesh("/enemy_1.irrmesh"), root, ENEMY_CRAFT_THRESHOLD - 10, vector3df(0,50,fighter->getPosition().Z));
	craftPool.push_back(enemy);
}

void ActionManager::launchRocket(const vector3df& position, const vector3df& rotation){
	ISceneManager* scene = device->getSceneManager();
	ISceneNodeAnimator* anim;
	IAnimatedMeshSceneNode* anms;

	anms = scene->addAnimatedMeshSceneNode(
		scene->getMesh("/rocket.irrmesh"),
		rootNode, ROCKET_ID, position, rotation);
	anms->setLoopMode(false);
	//anms->setAnimationEndCallback(new MyIAnimationEndCallBack);
	//anms->setDebugDataVisible(scene::EDS_BBOX);
	projectilePool.push_back(anms);

	//ATTENTION!
	//rocket removal should be implemented with callbacks like this
	//
	//anms->setAnimationEndCallback(new RocketAnimationEndCallback);
	//
	//but it doesn't work ='(
	
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
			position, vector3df(position.X, 150, position.Z),(150 - position.Y) / ROCKET_SPEED);
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
	currentTime = time; //update current time

	//check for collisions between crafts and projectiles
	for(int i = 0; i < craftPool.size(); i++)
		for(int j = 0; j < projectilePool.size(); j++)
			if(collisionCheck(craftPool[i], projectilePool[j])){
				ISceneNode* craftNode = 0; 
				if(craftPool[i]->getID() < ENEMY_CRAFT_THRESHOLD) //define type of craft whether it is enemy or not
					craftNode = craftPool[i];
				ISceneNode* projectileNode = (ISceneNode*)projectilePool[j];
				if(craftNode && projectileNode){ 
					plane3df plane(craftNode->getPosition(), vector3df(0,0,-1)); 
					addExplosion(craftNode->getPosition(), vector3df(0,0,0), 5, device->getSceneManager(), plane, 0); //create cool particle explosion
					craftPool[i]->remove(); //remove craft
					craftPool.erase(i);
					projectilePool[j]->remove(); //remove projectile
					projectilePool.erase(j);
				}
			}

	//remove projectiles that have left the visible screen
	//callbacks doesn't work! (see comment above)
	for(int i = 0; i < projectilePool.size(); i++){
		if(projectilePool[i]->getPosition().Y > 140){
			projectilePool[i]->remove(); //remove it from scene
			projectilePool.erase(i); //remove it from pool
		}
	}
}

bool ActionManager::collisionCheck(ISceneNode* obj_1, ISceneNode* obj_2){
	if(obj_1->getTransformedBoundingBox().intersectsWithBox(obj_2->getTransformedBoundingBox()))
		return (obj_1->getTransformedBoundingBox().intersectsWithBox(obj_2->getTransformedBoundingBox()));
	return false;
}

bool ActionManager::onCollision(const ISceneNodeAnimatorCollisionResponse& animator){
	cout << "Collision" << endl;
	device->drop();
	return true;
}
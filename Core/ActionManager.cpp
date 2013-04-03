#include "ActionManager.h"

ActionManager::ActionManager(IrrlichtDevice* dev, ISceneNode* root, Craft* f) : device(dev), rootNode(root) {
	//if(!scene) log << "NULL cout" << endl;
	leftShotTime = 0;
	rightShotTime = 0;
	currentTime = 0;
	gameOverTime = 0;
	currentScore = 0;
	delay = 5;
	inGame = true;
	leftPressed = false;
	rightPressed = false;

	ISceneManager* scene = device->getSceneManager();
	fighter = scene->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER);
	fighter->setDebugDataVisible(scene::EDS_BBOX);
	craftPool.push_back(f);

	deviceA = OpenDevice();
	rocketSound = OpenSoundEffect(deviceA, "/rocket.wav", MULTIPLE);
	rocketSound->setVolume(0.5f); // 0.0 to 1.0
	rocketSound->setPan(0);       // 0 Left, 1 Right
	rocketSound->setPitchShift(1.5);

	explosionSound = OpenSoundEffect(deviceA, "/explosion.wav", MULTIPLE);
	explosionSound->setVolume(0.5f); // 0.0 to 1.0
	explosionSound->setPan(0);       // 0 Left, 1 Right
	explosionSound->setPitchShift(2.0);

	IGUIFont* font = device->getGUIEnvironment()->getFont("/button_font.xml");
	stringw tmp(L"SCORE: ");
	tmp += currentScore;
	score = scene->addTextSceneNode(font, tmp.c_str(), SColor(100,255,255, 255), rootNode, vector3df(0,SH_SF - 20,0));

	/*	
	craftPool.push_back(new Blinky(device,
		rootNode, -1001,
		vector3df(0, SCREEN_HEIGHT / SCALE_FACTOR + 10, 0),
		0.5f, currentTime, ENEMY_ORIENTATION::ENEMY_LEFT, 1000, 100));
	*/

	/*
	ISceneNode* sphere_1 = scene->addSphereSceneNode();
	sphere_1->setPosition(vector3df(0,0,0));

	ISceneNode* sphere_2 = scene->addSphereSceneNode();
	sphere_2->setPosition(vector3df(-10,-10,0));
	*/
	
	enemyGenerator = new EnemyGenerator(GAME_MODE::GAME_MODE_EASY, device, rootNode, craftPool);
}

void ActionManager::launchRocket(const vector3df& position, const vector3df& destination){
	projectilePool.push_back(new Rocket(device, ROCKET_ID, rootNode, position, destination));
}

void ActionManager::fireAction(EMOUSE_INPUT_EVENT me){
	if(inGame)
		if(me == EMIE_LMOUSE_PRESSED_DOWN){
			leftPressed = true;
			if(currentTime - leftShotTime > RESPONSE_TIME){
				vector3df leftRocketPosition(-16.5f, -7.0f, -10.5f);
				launchRocket(
					fighter->getPosition() + leftRocketPosition,
					fighter->getPosition() + leftRocketPosition + 
					vector3df(0.0, SH_SF - fighter->getPosition().Y - leftRocketPosition.Y - 10, 0.0));
				leftShotTime = currentTime;
				rocketSound->play();
			}
		} else if(me == EMIE_RMOUSE_PRESSED_DOWN){
			rightPressed = true;
			if(currentTime - rightShotTime > RESPONSE_TIME){
				vector3df rightRocketPosition(16.5f, -7.0f, -10.5f);
				launchRocket(
					fighter->getPosition() + rightRocketPosition,
					fighter->getPosition() + rightRocketPosition + 
					vector3df(0.0, SH_SF - fighter->getPosition().Y - rightRocketPosition.Y - 10, 0.0));
				rightShotTime = currentTime;
				rocketSound->play();
			}
		}
}

void ActionManager::stop(){
	for(unsigned int i = 0; i < craftPool.size(); i++){
		if(craftPool[i]->getSceneNode()->getID() != NEWGAME_FIGHTER){
			craftPool[i]->remove();
			delete craftPool[i];
			craftPool.erase(i);
		}
	}
	for(unsigned int i = 0; i < projectilePool.size(); i++){
		projectilePool[i]->remove();
		delete projectilePool[i];
		projectilePool.erase(i);
	}
}

void ActionManager::createExplosion(const vector3df& position, int size){
	plane3df plane(vector3df(0,0,0), vector3df(0,0,-1));
	addExplosion(position,vector3df(0,0,0), size, device->getSceneManager(), plane, 0); //create cool particle explosion
	explosionSound->play();
}

void ActionManager::start(){
	for(unsigned int i = 0; i < craftPool.size(); i++){
		if(craftPool[i]->getSceneNode()->getID() != NEWGAME_FIGHTER){
			craftPool[i]->remove();
			delete craftPool[i];
			craftPool.erase(i);
		}
	}
	for(unsigned int i = 0; i < projectilePool.size(); i++){
		projectilePool[i]->remove();
		delete projectilePool[i];
		projectilePool.erase(i);
	}
	fighter->setVisible(true);
	inGame = true;
	gameOverTime = 0;
	currentScore = 0;
	score->setText(L"SCORE: 0");
}

void ActionManager::generateWave(ENEMYWAVE_TYPE type){
};

void ActionManager::fireAction(EKEY_CODE kc){
};

void ActionManager::pause(){
};

void ActionManager::resume(){
};

void ActionManager::update(u32 time){
	currentTime = time; //update current time
	if(inGame){
		if(enemyGenerator->isReady(time)) //if it is time to generate new enemies
			enemyGenerator->generateWave(ENEMYWAVE_EMPTY, time); //just do it
		collisionHandling();
		checkForCapture();
	} else {
		gameOverDelay();
	}
	removeInvisibleProjectiles();
}

bool ActionManager::collisionCheck(ISceneNode* obj_1, ISceneNode* obj_2){
	if(obj_1->getTransformedBoundingBox().intersectsWithBox(obj_2->getTransformedBoundingBox()))
		return (obj_1->getTransformedBoundingBox().intersectsWithBox(obj_2->getTransformedBoundingBox()));
	return false;
}

void ActionManager::checkForCapture(){
	//if one of the enemies gets the destination you lose
	for(unsigned int i = 0; i < craftPool.size(); i++)
		if(craftPool[i]->isMoveFinished()){
			craftPool[i]->remove();//remove it from scene
			delete craftPool[i];
			craftPool.erase(i); //remove it from pool
			ISceneNode* fighter = device->getSceneManager()->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER);
			fighter->setVisible(false);
			createExplosion(fighter->getPosition(), 12);
			gameOver();
		}
}

void ActionManager::collisionHandling(){
	collisionCraftVsCraft();
	collisionProjectileVsCraft();
	collisionProjectileVsProjectile();
}

void ActionManager::removeInvisibleProjectiles(){
	//remove projectiles that have left the visible screen
	//callbacks doesn't work! (see comment above)
	for(unsigned int i = 0; i < projectilePool.size(); i++){
		if(projectilePool[i]->isMoveFinished()){
			projectilePool[i]->remove(); //remove it from scene
			delete projectilePool[i];
			projectilePool.erase(i); //remove it from pool
		}
	}
}

void ActionManager::collisionCraftVsCraft(){
	for(unsigned int i = 0; i < craftPool.size(); i++)
		for(unsigned int j = i + 1; j < craftPool.size(); j++)
			if(collisionCheck(craftPool[i]->getSceneNode(), craftPool[j]->getSceneNode())){
				ISceneNode* fighter;
				ISceneNode* craft;
				bool isFighter = false;
				if(craftPool[i]->getSceneNode()->getID() == NEWGAME_ELEMENT::NEWGAME_FIGHTER){
					 fighter = craftPool[i]->getSceneNode();
					 craft = craftPool[j]->getSceneNode();
					 isFighter = true;
				} else if (craftPool[j]->getSceneNode()->getID() == NEWGAME_ELEMENT::NEWGAME_FIGHTER){
					 fighter = craftPool[j]->getSceneNode();
					 craft = craftPool[i]->getSceneNode();
					 isFighter = true;
				}
				if(isFighter){
					craft->setVisible(false);
					fighter->setVisible(false);
					createExplosion(fighter->getPosition(), 12);
					gameOver();
				}
			}
}

void ActionManager::collisionProjectileVsCraft(){
	//check for collisions between crafts and projectiles
	for(unsigned int i = 0; i < craftPool.size(); i++)
		for(unsigned int j = 0; j < projectilePool.size(); j++)
			if(collisionCheck(craftPool[i]->getSceneNode(), projectilePool[j]->getAnimatedMeshSceneNode())){
				ISceneNode* craftNode = 0; 
				if(craftPool[i]->getSceneNode()->getID() < ENEMY_CRAFT_THRESHOLD) //define type of craft whether it is enemy or not
					craftNode = craftPool[i]->getSceneNode();
				ISceneNode* projectileNode = (ISceneNode*)projectilePool[j]->getAnimatedMeshSceneNode();
				if(craftNode && projectileNode){ 
					createExplosion(craftNode->getPosition(), 12);
					craftPool[i]->remove(); //remove craft
					delete craftPool[i]; //release its memory
					craftPool.erase(i); //remove from active pool
					projectilePool[j]->remove(); //remove projectile
					delete projectilePool[j];
					projectilePool.erase(j);
					currentScore += 10;
					stringw tmp(L"SCORE: ");
					tmp += currentScore;
					score->setText(tmp.c_str());
				}
			}
}

void ActionManager::collisionProjectileVsProjectile(){
	for(unsigned int i = 0; i < craftPool.size(); i++)
		for(unsigned int j = i + 1; j < craftPool.size(); j++)
		{}
}

void ActionManager::gameOver(){
	inGame = false;
	gameOverTime = currentTime;
}

void ActionManager::gameOverDelay(){
	if((currentTime - gameOverTime) / 1000.f > delay){
		irr::SEvent event;
		event.EventType = EET_USER_EVENT;
		event.UserEvent.UserData1 = -1;
		device->postEventFromUser(event);
	}
}

ActionManager::~ActionManager(){
	//delete enemyGenerator;
	/*
	for(unsigned int i = 0; i < craftPool.size(); i++){
		craftPool[i]->remove();
		delete craftPool[i];
		craftPool.erase(i);
	}
	for(unsigned int i = 0; i < projectilePool.size(); i++){
		projectilePool[i]->remove();
		delete projectilePool[i];
		projectilePool.erase(i);
	}
	*/
}
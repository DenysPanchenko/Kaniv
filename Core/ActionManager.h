#ifndef ActionManager_h
#define ActionManager_h

#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;

#include "Global.h"
#include "audiere.h"
#include "../ParticleExplosion/CMain.h"
#include "../GameUnits/Fighter.h"
#include "../GameUnits/Rocket.h"
#include "../GameUnits/Craft.h"
#include "../GameUnits/Pinky.h"
#include "EnemyGenerator.h"

using namespace audiere;

#include <iostream>
using namespace std;

/*
class MyIAnimationEndCallBack : public irr::scene::IAnimationEndCallBack
{
   virtual void OnAnimationEnd (IAnimatedMeshSceneNode *node) 
   {
	   cout << "I'm here" << endl;
      node->remove();
   }
};
*/
#include <map>

class ActionManager {//: public IAnimationEndCallBack{
	ISceneNode* rootNode;
	ISceneNode* fighter;
	IrrlichtDevice* device;

	bool leftPressed; //state of left mouse button
	bool rightPressed; //state of right mouse button
	bool spacePressed; //state of space keyboard button
	bool isKeyDown[KEY_KEY_CODES_COUNT];

	u32 currentTime; //current game time
	u32 leftShotTime;
	u32 rightShotTime;

	EnemyGenerator* enemyGenerator;
	array<Craft*> craftPool;
	array<Rocket*> projectilePool;

	void generateWave(ENEMYWAVE_TYPE type);

	f32 delay;
	u32 gameOverTime;
	bool inGame;

	int currentScore;
	ITextSceneNode* score;

	AudioDevicePtr deviceA;
	SoundEffectPtr rocketSound;
	SoundEffectPtr explosionSound;
	

	void createExplosion(const vector3df& position, int size);
	void gameOverDelay();
	void checkForCapture();
	void collisionHandling();
	void collisionCraftVsCraft();
	void collisionProjectileVsCraft();
	void collisionProjectileVsProjectile();
	void removeInvisibleProjectiles();
	void launchRocket(const vector3df& position, const vector3df& rotation);
	bool collisionCheck(ISceneNode* obj_1, ISceneNode* obj_2);
public:
	ActionManager(IrrlichtDevice* dev, ISceneNode* root, Craft* f);
	~ActionManager();
	void fireAction(EMOUSE_INPUT_EVENT me);
	void fireAction(EKEY_CODE kc);
	void update(u32 time);	
	void pause();
	void resume();
	void start();
	void stop();
	void gameOver();
};

#endif
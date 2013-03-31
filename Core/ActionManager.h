#ifndef ActionManager_h
#define ActionManager_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

#include "Global.h"
#include "../ParticleExplosion/CMain.h"
#include "../GameUnits/Fighter.h"
#include "../GameUnits/Rocket.h"

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

class ActionManager : public ICollisionCallback {//: public IAnimationEndCallBack{
	bool leftPressed; //state of left mouse button
	bool rightPressed; //state of right mouse button
	bool spacePressed; //state of space keyboard button
	u32 currentTime; //current game time
	u32 leftShotTime;
	u32 rightShotTime;
	bool isKeyDown[KEY_KEY_CODES_COUNT];
	array<Rocket*> rocketPool;
	IrrlichtDevice* device;
	ISceneNode* rootNode;
	ITriangleSelector* selector;
	void destroyRocket();
	array<IAnimatedMeshSceneNode*> projectilePool;
	array<ISceneNode*> craftPool;
	//std::map<ISceneNode*, ISceneNode*> actors;
	//MyIAnimationEndCallBack end;
public:
	ActionManager(IrrlichtDevice* dev, ISceneNode* root);
	void fireAction(EMOUSE_INPUT_EVENT me);
	void fireAction(EKEY_CODE kc);
	void update(u32 time);
	void pause();
	void resume();
	void restart();
	void launchRocket(const vector3df& position, const vector3df& rotation);
	bool onCollision(const ISceneNodeAnimatorCollisionResponse& animator);
	bool collisionCheck(ISceneNode* obj_1, ISceneNode* obj_2);
	/*
	void OnAnimationEnd(IAnimatedMeshSceneNode* node){
		node->remove();
	}
	*/
};

#endif
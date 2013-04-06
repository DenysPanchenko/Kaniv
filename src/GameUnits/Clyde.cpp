#include "Clyde.h"

#include <iostream>

using namespace std;

Clyde::Clyde(IrrlichtDevice* dev, ISceneNode* parent, s32 ID, vector3df position,
	f32 speed, u32 time) : Craft(dev) {
	alive = true;
	ISceneManager* scene = device->getSceneManager();
		craft = scene->addAnimatedMeshSceneNode(scene->getMesh("/enemy_3.irrmesh"), parent, ID, position);

	if(craft){
		ISceneNodeAnimator* rotationAnimator = scene->createRotationAnimator(vector3df(0.0, 1.0, 0.0));
		if(rotationAnimator){
			craft->addAnimator(rotationAnimator);
			rotationAnimator->drop();
		}
	}
}

bool Clyde::alive;

bool Clyde::isAlive(){
	return alive;
}

void Clyde::remove(){
	craft->removeAnimators();
	craft->remove();
	alive = false;
}

bool Clyde::isMoveFinished(){
	return false;//moveAnimator->hasFinished();
}
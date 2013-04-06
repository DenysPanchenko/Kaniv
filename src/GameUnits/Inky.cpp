#include "Inky.h"

Inky::Inky(IrrlichtDevice* dev, ISceneNode* parent, s32 ID, vector3df position, f32 speed, f32 time) : Craft(dev) {
	ISceneManager* scene = device->getSceneManager();
	craft = scene->addAnimatedMeshSceneNode(scene->getMesh("enemy_4.irrmesh"), parent, ID, position);
		
	if(craft){
		array<vector3df> points; //directional points of spline fighter traectory
		points.push_back(position);
		points.push_back(vector3df(position.X, -SH_SF - ENEMY_BUFFER_HEIGHT, position.Z));
		moveAnimator = scene->createFollowSplineAnimator(time, points, speed, 0.5f, false);
		/*
		moveAnimator = scene->createFlyStraightAnimator(
			position, vector3df(position.X, - 2 * SCREEN_HEIGHT / SCALE_FACTOR, position.Z), speed);
		*/
		if(moveAnimator){
			craft->addAnimator(moveAnimator);
			moveAnimator->drop();
		}

		ISceneNodeAnimator* rotationAnimator = scene->createRotationAnimator(vector3df(0.0, 1.0, 0.0));
		if(rotationAnimator){
			craft->addAnimator(rotationAnimator);
			rotationAnimator->drop();
		}
	}
}

void Inky::remove(){
	craft->removeAnimators();
	craft->remove();
}

bool Inky::isMoveFinished(){
	return moveAnimator->hasFinished();
}
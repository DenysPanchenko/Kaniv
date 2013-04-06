#include "Blinky.h"

Blinky::Blinky(IrrlichtDevice* dev, ISceneNode* parent, s32 ID,
	vector3df position, f32 speed, u32 time, ENEMY_DIRECTION direction, f32 f, f32 A) : Craft(dev) {
	ISceneManager* scene = device->getSceneManager();
		craft = scene->addAnimatedMeshSceneNode(scene->getMesh("enemy_1.irrmesh"), parent, ID, position);
			
		if(craft){
			array<vector3df> points; //directional points of spline fighter traectory
			points.push_back(position);
			for(int i = position.Y; i > - SH_SF - ENEMY_BUFFER_HEIGHT; i -= 100)
				points.push_back(vector3df(position.X + A * sin(f * i), i, position.Z));
			moveAnimator = scene->createFollowSplineAnimator(time, points, speed, 0.5f, false);

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

void Blinky::remove(){
	craft->removeAnimators();
	craft->remove();
}

bool Blinky::isMoveFinished(){
	return moveAnimator->hasFinished();
}
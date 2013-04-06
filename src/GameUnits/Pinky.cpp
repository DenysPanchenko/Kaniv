#include "Pinky.h"

Pinky::Pinky(IrrlichtDevice* dev, ISceneNode* parent,
	s32 ID, const vector3df& position, f32 speed, u32 time, ENEMY_DIRECTION direction) : Craft(dev){
		ISceneManager* scene = device->getSceneManager();
		craft = scene->addAnimatedMeshSceneNode(scene->getMesh("enemy_2.irrmesh"), parent, ID, position);

		if(craft){
			array<vector3df> points; //directional points of spline fighter traectory
			if(direction == ENEMY_DIRECTION::ENEMY_LEFT){
				points.push_back(vector3df(-position.X, position.Y, position.Z));
				points.push_back(vector3df(SW_SF - position.X, 0, position.Z));
				points.push_back(vector3df(-position.X, -position.Y, position.Z));
			} else {
				points.push_back(vector3df(position.X, position.Y, position.Z));
				points.push_back(vector3df(-SW_SF + position.X, 0, position.Z));
				points.push_back(vector3df(position.X, -position.Y, position.Z));
			}

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
};

void Pinky::remove(){
	craft->removeAnimators();
	craft->remove();
}

bool Pinky::isMoveFinished(){
	return moveAnimator->hasFinished();
}
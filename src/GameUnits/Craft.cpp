#include "Craft.h"

#include <iostream>
using namespace std;

Craft::Craft(IrrlichtDevice* dev) : device(dev) {
	//moveAnimator = 0;
};

Craft::~Craft(){
};

ISceneNode* Craft::getSceneNode(){
	return craft;
}

void Craft::remove(){
	cout << "I'm here in craft" << endl;
	craft->remove();
};

bool Craft::isMoveFinished(){
	return false;
}
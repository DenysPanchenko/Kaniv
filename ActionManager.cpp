#include "ActionManager.h"

ActionManager::ActionManager(){
	//if(!scene) log << "NULL cout" << endl;
	leftGunTime = 0.f;
	rightGunTime = 0.f;
}

void ActionManager::fireAction(EMOUSE_INPUT_EVENT me){

}

void ActionManager::fireAction(EKEY_CODE kc){

}

void ActionManager::pause(){
};

void ActionManager::resume(){
};

void ActionManager::restart(){
};

void ActionManager::update(float time){
}
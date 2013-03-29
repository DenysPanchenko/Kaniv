#include "StateManager.h"

StateManager::StateManager(IrrlichtDevice* dev) : device(dev) {
	//init();
};

bool StateManager::init(){
	states.insert(make_pair(GAME_MAINMENU_STATE, (AbstractState*) new MainMenu(device)));
	states.insert(make_pair(GAME_NEWGAME_STATE, (AbstractState*) new NewGame(device)));
	states.insert(make_pair(GAME_SETTINGS_STATE, (AbstractState*) new Settings(device)));
	//states.insert(GAME_HELP, new Help(device));
	states.insert(make_pair(GAME_ABOUT_STATE, (AbstractState*) new About(device)));
	std::map<GAME_STATE, AbstractState*>::iterator iter = states.begin();
	for(; iter != states.end(); iter++)
		if(!iter->second){
			cout << "StateManager: Failed to create state with id " << iter->first << endl;
			return false;
		} else {
			iter->second->init();
			iter->second->setVisible(false);
		}
	setState(GAME_STATE::GAME_MAINMENU_STATE);
	return true;
}

GAME_STATE StateManager::getState() const {
	return currentState;
}

void StateManager::setState(GAME_STATE st){
	if(st != currentState){
		std::map<GAME_STATE, AbstractState*>::iterator iter = states.begin();
		for(; iter != states.end(); iter++)
			if(iter->second)
				iter->second->setVisible(false);
			else
				cout << "StateManager: State with null value" << endl;
		if(states.find(st) != states.end()){
			states[st]->setVisible(true);
			currentState = st;
		} else{
			cout << "StateManager: Reference to unexisted state" << endl;
		}
		setCursor();
	}
}

void StateManager::setCursor(){
	if(currentState == GAME_STATE::GAME_NEWGAME_STATE)
		device->getCursorControl()->setVisible(false);
	else
		device->getCursorControl()->setVisible(true);
}

void StateManager::update(u32 time){
	if(currentState == GAME_NEWGAME_STATE)
		((NewGame*)states[currentState])->update(time);
}

void StateManager::mouseInputEvent(EMOUSE_INPUT_EVENT event){
	if(currentState == GAME_STATE::GAME_NEWGAME_STATE)
		((NewGame*)states[currentState])->mouseInputEvent(event);
}
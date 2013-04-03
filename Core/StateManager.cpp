#include "StateManager.h"

StateManager::StateManager(IrrlichtDevice* dev) : device(dev) {
	//init();
};

bool StateManager::init(){
	deviceA = OpenDevice();
	
	mainMenuMusic = OpenSound(deviceA, "/mainmenu.wav", true);
	mainMenuMusic->setVolume(0.5f); // 0.0 to 1.0
	mainMenuMusic->setPan(0);       // 0 Left, 1 Right
	mainMenuMusic->setRepeat(1);    // 1 loop, 0 don't loop

	newGameMusic = OpenSound(deviceA, "/newgame.mp3", true);
	newGameMusic->setVolume(0.5f); // 0.0 to 1.0
	newGameMusic->setPan(0);       // 0 Left, 1 Right
	newGameMusic->setRepeat(1);    // 1 loop, 0 don't loop

	states.insert(make_pair(GAME_MAINMENU_STATE, (AbstractState*) new MainMenu(device)));
	states.insert(make_pair(GAME_NEWGAME_STATE, (AbstractState*) new NewGame(device)));
	states.insert(make_pair(GAME_SETTINGS_STATE, (AbstractState*) new Settings(device)));
	states.insert(make_pair(GAME_HELP_STATE, (AbstractState*) new Help(device)));
	states.insert(make_pair(GAME_ABOUT_STATE, (AbstractState*) new About(device)));
	states.insert(make_pair(GAME_GAMEOVER_STATE, (AbstractState*) new GameOver(device)));
	std::map<GAME_STATE, AbstractState*>::iterator iter = states.begin();
	for(; iter != states.end(); iter++)
		if(iter->second){
			iter->second->init();
			iter->second->setVisible(false);
		}
	//setState(GAME_STATE::GAME_MAINMENU_STATE);
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
		if(states.find(st) != states.end()){
			states[st]->setVisible(true);
			currentState = st;
		}
		setCursor();
		setMusic();
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

void StateManager::setMusic(){
	switch(currentState){
	case GAME_MAINMENU_STATE:
		newGameMusic->stop();
		mainMenuMusic->play();
		break;
	case GAME_NEWGAME_STATE:
		newGameMusic->play();
		mainMenuMusic->stop();
		break;
	}
}
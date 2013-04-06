#include "EventReceiver.h"

EventReceiver::EventReceiver(IrrlichtDevice* dev, StateManager* st, SETTINGS_STRUCT* set) 
	: device(dev), stateManager(st), SETTINGS(set){
	pushButtonSound = OpenSoundEffect(audioDevice, "./res/sound/button.mp3", MULTIPLE);
}

EventReceiver::MouseState EventReceiver::getMouseState() const {
	return currentMouseState;
}

bool EventReceiver::OnEvent(const SEvent& event){
	if(event.EventType == EET_KEY_INPUT_EVENT){
		switch(event.KeyInput.Key){
		case KEY_ESCAPE:
			if(stateManager->getState() == GAME_NEWGAME_STATE)
				//showExitGameConfirmDialog();
				stateManager->setState(GAME_MAINMENU_STATE);
			break;
		default:
			break;
		}
	}
	//implement here keyboard control
	if(event.EventType == EET_MOUSE_INPUT_EVENT){
		stateManager->mouseInputEvent(event.MouseInput.Event);
		switch(event.MouseInput.Event){
		case EMIE_LMOUSE_PRESSED_DOWN:
			currentMouseState.leftButtonDown = true;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			currentMouseState.leftButtonDown = false;
			break;
		case EMIE_RMOUSE_PRESSED_DOWN:
			currentMouseState.rightButtonDown = true;
			break;
		case EMIE_RMOUSE_LEFT_UP:
			currentMouseState.rightButtonDown = false;
			break;
		case EMIE_MOUSE_MOVED:
			currentMouseState.position.X = event.MouseInput.X;
			currentMouseState.position.Y = event.MouseInput.Y;
			break;
		default:
			//don't use wheel
			break;
		}
	}
	//handle gui events
	if(event.EventType == EET_GUI_EVENT){
		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* gui = device->getGUIEnvironment();
		switch(event.GUIEvent.EventType){
		case EGET_BUTTON_CLICKED:
			switch(id){
			case MAINMENU_NEW_GAME_BUTTON:
				stateManager->setState(GAME_NEWGAME_STATE);
				break;
			case MAINMENU_SETTINGS_BUTTON:
				stateManager->setState(GAME_SETTINGS_STATE);
				break;
			case MAINMENU_HELP_BUTTON:
				stateManager->setState(GAME_HELP_STATE);
				break;
			case MAINMENU_ABOUT_BUTTON:
				stateManager->setState(GAME_ABOUT_STATE);
				break;
			case MAINMENU_EXIT_BUTTON:
				showExitConfirmDialog();
				break;
			case ABOUT_BACK_BUTTON:
				stateManager->setState(GAME_MAINMENU_STATE);
				break;
			case EXIT_OK:
				device->drop();
				break;
			case EXIT_CANCEL:
				event.GUIEvent.Caller->getParent()->remove();
				break;
			case EXIT_NEWGAME_YES:
				stateManager->setState(GAME_MAINMENU_STATE);
				break;
			case EXIT_NEWGAME_NO:
				event.GUIEvent.Caller->getParent()->remove();
				break;
			default:
				break;
			}
			pushButtonSound->setVolume(SETTINGS->soundVolume);
			pushButtonSound->play();
			break;
		case EGET_CHECKBOX_CHANGED:
			if(!((IGUICheckBox*)(event.GUIEvent.Caller))->isChecked()){
				SETTINGS->soundVolume = 0.0;
			}
			else{
				SETTINGS->soundVolume = 0.5;
			}
			stateManager->setMusic();
			break;
		case EGET_COMBO_BOX_CHANGED:
			int index = ((IGUIComboBox*)(event.GUIEvent.Caller))->getSelected();
			cout << "index = " << index << endl;
			switch(index){
			case 0:
				SETTINGS->gameMode = GAME_MODE_EASY;
				break;
			case 1:
				SETTINGS->gameMode = GAME_MODE_NORMAL;
				break;
			case 2:
				SETTINGS->gameMode = GAME_MODE_HARD;
				break;
			default:
				break;
			}
			break;
		}
	} else if(event.EventType == EET_USER_EVENT){
		if(event.UserEvent.UserData1 == -1){
			stateManager->setState(GAME_GAMEOVER_STATE);
		}
	}
	return false;
}

void EventReceiver::showExitConfirmDialog(){
	IGUIEnvironment* env = device->getGUIEnvironment();
	IGUIWindow* window = env->addWindow(
		rect<s32>(224, 200, 800, 390),true, L"Confirm dialog");
	env->addStaticText(L"Do you want to exit the game?",
		rect<s32>(35,50,600,150),
		false, // border?
		false, // wordwrap?
		window);
	for (u32 i=0; i<EGDC_COUNT ; ++i){
		SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
	env->addButton(
		rect<s32>(15, 100, 285, 170), window, EXIT_OK, L"Ok");
	env->addButton(
		rect<s32>(300, 100, 555, 170), window, EXIT_CANCEL, L"Cancel");
}

void EventReceiver::showExitGameConfirmDialog(){
	/*
	IGUIEnvironment* env = device->getGUIEnvironment();
	IGUIWindow* window = env->addWindow(
		rect<s32>(224, 200, 800, 390),true, L"Confirm dialog");
	env->addStaticText(L"Stop this battle?",
		rect<s32>(35,50,600,150),
		false, // border?
		false, // wordwrap?
		window);
	for (u32 i=0; i<EGDC_COUNT ; ++i){
		SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
	env->addButton(
		rect<s32>(15, 100, 285, 170), window, EXIT_NEWGAME_YES, L"Yes");
	env->addButton(
		rect<s32>(300, 100, 555, 170), window, EXIT_NEWGAME_NO, L"No");
		*/
}
#include "EventReceiver.h"

EventReceiver::EventReceiver(IrrlichtDevice* dev, StateManager* st) : device(dev), stateManager(st){
	if(!st)
		cout << "EventReceiver: NULL StateManager" << endl;
}

EventReceiver::MouseState EventReceiver::getMouseState() const {
	return currentMouseState;
}

bool EventReceiver::OnEvent(const SEvent& event){
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
				//log
				cout << "New game button event" << id << endl;
				stateManager->setState(GAME_NEWGAME_STATE);
				break;
			case MAINMENU_SETTINGS_BUTTON:
				//log
				cout << "Settings button event" << id << endl;
				stateManager->setState(GAME_SETTINGS_STATE);
				break;
			case MAINMENU_HELP_BUTTON:
				//log
				cout << "Help button event" << id << endl;
				stateManager->setState(GAME_HELP_STATE);
				break;
			case MAINMENU_ABOUT_BUTTON:
				//log
				cout << "About button event" << id << endl;
				stateManager->setState(GAME_ABOUT_STATE);
				break;
			case MAINMENU_EXIT_BUTTON:
				//log
				cout << "Exit button event" << endl;
				device->drop();	
				break;
			case ABOUT_BACK_BUTTON:
				//log
				cout << "Back from about button event" << id << endl;
				stateManager->setState(GAME_MAINMENU_STATE);
				break;
			default:
				//log
				cout << "EventReceiver: Undefined push button event" << endl;
				break;
			}
			break;
		}
	}
	return false;
}
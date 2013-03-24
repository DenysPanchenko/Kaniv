#include "EventReceiver.h"

EventReceiver::EventReceiver(){
	
}

bool EventReceiver::OnEvent(const SEvent& event){
	if(event.EventType == EET_GUI_EVENT){
		s32 id = event.GUIEvent.Caller->getID();
		//IGUIEnvironment* gui = device->getGUIEnvironment();

		switch(event.GUIEvent.EventType){
		case EGET_BUTTON_CLICKED:
			switch(id){
			}
			break;
		}
	}
	return false;
}
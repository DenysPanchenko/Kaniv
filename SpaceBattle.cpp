#include "SpaceBattle.h"

SpaceBattle::SpaceBattle(int argc, char** argv){
	device = createDevice(video::EDT_OPENGL, //create irrlicht game device
		dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT),
		16, false, false, false);

	//device->setWindowCaption(L"Space Battle XPN 2013"); //set up window title

	driver = device->getVideoDriver();
	scene = device->getSceneManager();
	gui = device->getGUIEnvironment();

	stateManager = new StateManager(device); //create state manager
	if(stateManager) 
		stateManager->init(); //initialize it if created

	eventReceiver = new EventReceiver(device, stateManager); //create event receiver
	device->setEventReceiver(eventReceiver);

	loadFont(); //load "space" font
}

void SpaceBattle::run(){
	u32 then = device->getTimer()->getTime(); //get starting time
	ISceneNode* fighter = scene->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER); //obtain fighter scene node

	int lastFPS = driver->getFPS(); //get starting fps
	
	while(device->run() && driver){ //game main loop

		if(stateManager->getState() == GAME_STATE::GAME_NEWGAME_STATE){ //if game in playing regime

			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; //time in seconds
			then = now;

			stateManager->update(now); //send update signal to ActionManager
	
			vector3df fighterPosition = fighter->getPosition();
	
			line3df ray = scene->getSceneCollisionManager()->getRayFromScreenCoordinates(
				eventReceiver->getMouseState().position);

			plane3df plane(fighterPosition, vector3df(0,0,-1)); //plane 
			vector3df mousePosition; //current mouse position

			if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition)){ //check whether the mouse pointer within the visible screen
				vector3df toMousePosition(mousePosition - fighterPosition);
				const f32 availableMovement = FIGHTER_SPEED * frameDeltaTime;
				if(toMousePosition.getLength() <= availableMovement) //prevents dithering of fighter
						fighterPosition = mousePosition; // jump to the final position
					else
				        fighterPosition += toMousePosition.normalize() * availableMovement; // move towards cursor position
			}
			fighter->setPosition(fighterPosition);
		}

		driver->beginScene(true, true, 0);
			scene->drawAll();
			gui->drawAll();
		driver->endScene();

		int fps = driver->getFPS(); //show fps block

        if (lastFPS != fps){
            core::stringw tmp(L"Space Battle XPN 2013 [Denis Panchenko]");
            tmp += L"fps: ";
            tmp += fps;

            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
	}
}

void SpaceBattle::loadFont(){
	IGUIFont* defaultFont = 0;
	IFileSystem* fileSystem = device->getFileSystem(); 
	if(!fileSystem->existFile("/font.zip")){
		cout << "main: Failed to load font, archive does not exists" << endl;
	} else {
		fileSystem->addZipFileArchive("/font.zip");
		defaultFont = gui->getFont("/myfont.xml");
		if(!defaultFont){
			cout << "main: Failed to load font from archive" << endl;
		} else {
			defaultFont->grab();
			gui->getSkin()->setFont(defaultFont);
			cout << "Font successfully loaded" << endl;
		}
	}
}

SpaceBattle::~SpaceBattle(){

}
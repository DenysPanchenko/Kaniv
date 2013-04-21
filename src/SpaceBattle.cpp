#include "SpaceBattle.h"

SpaceBattle::SpaceBattle(int argc, char** argv){
	splashTime = 3500.f; //show splash screen 3.5 seconds
	isSplashShown = false;

	device = createDevice(video::EDT_DIRECT3D9, //create irrlicht game device
		dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT),
		32, false, false, false);

	driver = device->getVideoDriver();
	scene = device->getSceneManager();
	gui = device->getGUIEnvironment();

	device->getFileSystem()->addFileArchive("../res/"); //add folder with resources
	device->getFileSystem()->addZipFileArchive("../res/font.zip");
	device->getFileSystem()->addZipFileArchive("../res/mesh.zip");
	device->getFileSystem()->addZipFileArchive("../res/image.zip");

	stateManager = new StateManager(device, &SETTINGS); //create state manager
	if(stateManager) 
		stateManager->init(); //initialize it if is created

	eventReceiver = new EventReceiver(device, stateManager, &SETTINGS); //create event receiver
	device->setEventReceiver(eventReceiver);
	
	loadFont(); //load "space" font
}

void SpaceBattle::showSplash(u32 time){
	if(!isSplashShown){
		//alternative way to show splash screen, but with annoying distortions
		/*
			IGUIImage* background = gui->addImage(
			driver->getTexture("/splash_screen.jpg"), position2d<s32>(0,0), true);
		*/	
		tmp = scene->addEmptySceneNode();
		IBillboardSceneNode* splash = scene->addBillboardSceneNode(tmp,
			dimension2d<f32>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), vector3df(0,0,50));
		splash->setMaterialFlag(video::EMF_LIGHTING, false);
		splash->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		splash->setMaterialTexture(0, driver->getTexture("splash_screen.jpg"));

		ICameraSceneNode* camera = scene->addCameraSceneNode(tmp);
		camera->setPosition(vector3df(0,0,-100));

		CMatrix4<f32> projectionMatrix;
		projectionMatrix.buildProjectionMatrixOrthoRH(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 150, -150);
		camera->setProjectionMatrix(projectionMatrix, true);
		isSplashShown = true;
	} else if(time > splashTime){
		scene->getMesh("fighter.irrmesh");
		scene->getMesh("rocket.irrmesh");
		scene->getMesh("enemy_1.irrmesh");
		scene->getMesh("enemy_2.irrmesh");
		scene->getMesh("enemy_3.irrmesh");
		scene->getMesh("enemy_4.irrmesh");
		scene->getMesh("asteroid.irrmesh");
		tmp->remove();
		stateManager->setState(GAME_MAINMENU_STATE);
		isSplashShown = false;
	}
}

void SpaceBattle::run(){
	showSplash(0);

	u32 then = device->getTimer()->getTime(); //get starting time
	ISceneNode* fighter = scene->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER); //obtain fighter scene node

	int lastFPS = driver->getFPS(); //get starting fps
	
	while(device->run() && driver){ //game main loop
		const u32 now = device->getTimer()->getTime();
		if(isSplashShown)
			showSplash(now);
		if(stateManager->getState() == GAME_STATE::GAME_NEWGAME_STATE){ //if game in playing regime

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
            core::stringw tmp(L"Space Battle XPN 2013 [Denis Panchenko] ");
            tmp += L" FPS: ";
            tmp += fps;

            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
	}
}

void SpaceBattle::loadFont(){
	IGUIFont* defaultFont = 0;
	defaultFont = gui->getFont("button_font.xml");
	if(defaultFont){
		defaultFont->grab();
		gui->getSkin()->setFont(gui->getFont("text_font.xml"), EGDF_DEFAULT);
		gui->getSkin()->setFont(defaultFont, EGDF_BUTTON);
	}
}

SpaceBattle::~SpaceBattle(){

}
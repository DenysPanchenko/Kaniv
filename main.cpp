#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;
using namespace io;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "/audiere.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <cstdio>
#include "Global.h"
#include "MainMenu.h"
#include "StateManager.h"
#include "EventReceiver.h"

#include "audiere.h"

using namespace audiere;

int main(int argc, char** argv){
	freopen("log","w+",stdout); //output to log file

	//log
	cout << "SPACE BATTLE XPN 2013 log file" << endl;

	//create irrlicht game device

	IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT), 16, false, false, false);
	if(!device){ //device isn't created => exit the program
		cout << "main: Failed to create device" << endl;
		return -1;
	}

	//GLOBAL::init(device);

	//log
	cout << "Device created. EDT_OPENGL driver. Resolution: " << 
		SCREEN_WIDTH << "x" << SCREEN_HEIGHT << endl;

	device->setWindowCaption(L"Space Battle XPN 2013");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* scene = device->getSceneManager();
	IGUIEnvironment* gui = device->getGUIEnvironment();

	//log
	cout << "Loading fonts" << endl;

	//loading font
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

	//launch music
	AudioDevicePtr deviceA(OpenDevice());
	OutputStreamPtr mySound(OpenSound(deviceA, "/mainmenu.flac", true));
	mySound->setVolume(0.5f);
	mySound->setPan(0);
	mySound->setRepeat(1);
	//mySound->play();
 
   /*
	IGUIStaticText* caption = guiEnv->addStaticText(L"SPACE BATTLE",rect<s32>(10,10, 1014,200), true);
	caption->setDrawBorder(false);
	caption->setBackgroundColor(SColor(0,0,0,1));
    caption->setOverrideColor(SColor(255,255,255,255));
	*/
	
	//MainMenu mm(driver, gui, scene, 1024, 768);	
	//mm.setVisible(false);
	//mm.setVisible(true);
	
	StateManager* state = new StateManager(device);
	if(!state){ //state manager keeps all game states, without it game won't work
		cout << "main: Failed to create StateManager" << endl;
		return -1;
	} else {
		if(!state->init())
			cout << "main: Error in StateManger::init()" << endl;
		//log
		cout << "StateManger successfully created and initialized" << endl;
	}

	
	EventReceiver eventReceiver(device, state);
	device->setEventReceiver(&eventReceiver);


	/*
	ICameraSceneNode* camera = scene->addCameraSceneNodeMaya();
	camera->setFarValue(20000.f);
	// Maya cameras reposition themselves relative to their target, so target the location
	// where the mesh scene node is placed.
	camera->setTarget(core::vector3df(0,30,0));

	scene->setActiveCamera(camera);
	*/
		
	//log
	cout << "Launching the main loop" << endl;

	u32 then = device->getTimer()->getTime();
	//const f32 MOVEMENT_SPEED = 1000.f;

	ISceneNode* fighter = scene->getSceneNodeFromId(NEWGAME_ELEMENT::NEWGAME_FIGHTER);

	//main game loop
	while(device->run() && driver){
		if(state->getState() == GAME_STATE::GAME_NEWGAME_STATE){

			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; //time in seconds
			then = now;
	
			vector3df fighterPosition = fighter->getPosition();
	
			line3df ray = scene->getSceneCollisionManager()->getRayFromScreenCoordinates(
				eventReceiver.getMouseState().position);

			plane3df plane(fighterPosition, vector3df(0,0,-1));
			vector3df mousePosition;
			if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition)){
				vector3df toMousePosition(mousePosition - fighterPosition);
				const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;
				if(toMousePosition.getLength() <= availableMovement)
						fighterPosition = mousePosition; // Jump to the final position
					else
				        fighterPosition += toMousePosition.normalize() * availableMovement; // Move towards it
			}
			fighter->setPosition(fighterPosition);
		}
		driver->beginScene(true, true, 0);
			scene->drawAll();
			gui->drawAll();
		driver->endScene();
	}

	return 0;
}
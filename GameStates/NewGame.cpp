#include "NewGame.h"

NewGame::NewGame(IrrlichtDevice* dev) : AbstractState(dev){
	//init();
}

bool NewGame::init(){
	gui = device->getGUIEnvironment();
	scene = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();

	//create root node for level scene
	gameRootNode = scene->addEmptySceneNode(0, NEWGAME_ELEMENT::NEWGAME_ROOT_NODE);
	

	//create skybox with background texture
	ISceneNode* background = scene->addSkyBoxSceneNode(
		driver->getTexture("/background.tga"),
		driver->getTexture("/background.tga"),
		driver->getTexture("/background.tga"),
		driver->getTexture("/background.tga"),
		driver->getTexture("/background.tga"),
		driver->getTexture("/background.tga"),
		gameRootNode,
		NEWGAME_ELEMENT::NEWGAME_BACKGROUND);
	if(!background){
		cout << "NewGame: Failed to create background" << endl;
		return false;
	}

	//create fighter
	fighter = new Fighter(device, gameRootNode, scene);

	actionManager = new ActionManager(device, gameRootNode);

	//create a camera and add it to scene
	camera = scene->addCameraSceneNode(gameRootNode);
	camera->setPosition(vector3df(0,0,-150));
	camera->setTarget(vector3df(0,0,0));

	
	return true;
}

void NewGame::setVisible(bool flg){
	gameRootNode->setVisible(flg);
	if(!flg){
		gui->clear();
	} else {
		//device->getCursorControl()->setPosition(dimension2df(SCREEN_WIDTH / 2.0, 1.0 / 6.0 * SCREEN_HEIGHT));
		gui->loadGUI("newgame_gui.xml");
		device->getSceneManager()->setActiveCamera(camera);
	}
}

void NewGame::mouseInputEvent(EMOUSE_INPUT_EVENT event){
	actionManager->fireAction(event);
}

void NewGame::update(s32 time){
	actionManager->update(time);
}
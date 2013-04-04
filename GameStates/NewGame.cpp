#include "NewGame.h"

NewGame::NewGame(IrrlichtDevice* dev, SETTINGS_STRUCT* set) : AbstractState(dev), SETTINGS(set){
	//init();
}

bool NewGame::init(){
	gui = device->getGUIEnvironment();
	scene = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();

	//create root node for level scene
	gameRootNode = scene->addEmptySceneNode(0, NEWGAME_ELEMENT::NEWGAME_ROOT_NODE);
	
	/*
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
	*/

	//create fighter
	fighter = new Fighter(device, gameRootNode, scene);

	actionManager = new ActionManager(device, gameRootNode, fighter, SETTINGS);
	
	IBillboardSceneNode* background = scene->addBillboardSceneNode(
		gameRootNode, dimension2d<f32>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
		vector3df(0,0,50), NEWGAME_ELEMENT::NEWGAME_BACKGROUND);
	background->setMaterialFlag(video::EMF_LIGHTING, false);
    background->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    background->setMaterialTexture(0, driver->getTexture("/background.tga"));


	//create a camera and add it to scene
	camera = scene->addCameraSceneNode(gameRootNode);
	camera->setPosition(vector3df(0,0,-100));

	CMatrix4<f32> projectionMatrix;
	projectionMatrix.buildProjectionMatrixOrthoRH(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 150, -150);
	camera->setProjectionMatrix(projectionMatrix, true);
	
	/*
	IGUIButton* newGameButton = gui->addButton(
		rect<s32>(10,10,150,70),
		0, -2, L"menu",L"Return to main menu");
	newGameButton->setUseAlphaChannel(true);
	//newGameButton->setDrawBorder(false);
	//newGameButton->setImage(driver->getTexture("/inactive.png"));
	//newGameButton->setPressedImage(driver->getTexture("/active.png"));
	*/
	gui->saveGUI("newgame_gui.xml");

	return true;
}

void NewGame::setVisible(bool flg){
	gameRootNode->setVisible(flg);
	if(!flg){
		gui->clear();
		actionManager->stop();
	} else {
		gui::IGUIInOutFader* fader = gui->addInOutFader();
		fader->setColor(video::SColor(0,0,0,0));
		fader->fadeIn(1500);
		//device->getCursorControl()->setPosition(dimension2df(SCREEN_WIDTH / 2.0, 1.0 / 6.0 * SCREEN_HEIGHT));
		gui->loadGUI("newgame_gui.xml");
		actionManager->start();
		device->getSceneManager()->setActiveCamera(camera);
	}
}

void NewGame::mouseInputEvent(EMOUSE_INPUT_EVENT event){
	actionManager->fireAction(event);
}

void NewGame::update(s32 time){
	actionManager->update(time);
}
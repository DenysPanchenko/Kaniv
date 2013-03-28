#include "MainMenu.h"

MainMenu::MainMenu(){
	//init();
};

bool MainMenu::init(){
	gui = device->getGUIEnvironment();
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* scene = device->getSceneManager();

	//----------------------------------
	//set up gui elements
	//----------------------------------

	/*
	//create main menu background
	ITexture* bgrTexture = driver->getTexture("/background.jpg");
	if(!bgrTexture){
		cout << "MainMenu: Failed to load background" << endl;
		return false;
	}

	IGUIImage* bgrImage = gui->addImage(core::rect<s32>(0,0,width,height)); //fixed resolution by convention
	bgrImage->setImage(bgrTexture);
	driver->removeTexture(bgrTexture); //free memmory
	*/
	
	dimension2d<u32> screenResolution = driver->getScreenSize();
	int height = screenResolution.Height;
	int width = screenResolution.Width;

	//create main menu title
	ITexture* captionTexture = driver->getTexture("/title.png");
	if(!captionTexture){
		cout << "MainMenu: Failed to load title" << endl;
		return false;
	}

	dimension2d<u32> size = captionTexture->getSize();
	int titleWidth = 926;
	int titleHeight = 85;

	int topMargin = 15;
	int leftMargin = 30;//1.0 * (width - size.Width) / 2;

	IGUIImage* captionImage = gui->addImage(core::rect<s32>(
		width / 2.0 - titleWidth / 2.0, topMargin,
		width / 2.0 + titleWidth / 2.0 ,size.Height)); //centered relative to the fixed resolution
	captionImage->setImage(captionTexture);
	driver->removeTexture(captionTexture); //free memmory

	//auxiliary variables for buttons positionin
	int remaining = height - topMargin - titleHeight;
	
	int buttonSpan = ((remaining - (BUTTON_HEIGHT * 5)) / 6.0);
	int buttonTopMargin = topMargin + titleHeight;

	//set up menu buttons	
	IGUIButton* newGameButton = gui->addButton(rect<s32>(leftMargin, 1.0 * buttonSpan + 0.0 * BUTTON_HEIGHT + buttonTopMargin,
		leftMargin + BUTTON_WIDTH, 1.0 * (buttonSpan + BUTTON_HEIGHT) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_NEW_GAME_BUTTON, L"NEW GAME", L"Start new game");
	newGameButton->setUseAlphaChannel(true);
	newGameButton->setDrawBorder(false);
	newGameButton->setImage(driver->getTexture("/inactive.png"));
	newGameButton->setPressedImage(driver->getTexture("/active.png"));
	
	IGUIButton* settingsButton = gui->addButton(rect<s32>(leftMargin, 2.0 * buttonSpan + 1.0 * BUTTON_HEIGHT + buttonTopMargin,
		leftMargin + BUTTON_WIDTH, 2.0 * (buttonSpan + BUTTON_HEIGHT) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_SETTINGS_BUTTON, L"SETTINGS", L"Change game settings");
	settingsButton->setUseAlphaChannel(true);
	settingsButton->setDrawBorder(false);
	settingsButton->setImage(driver->getTexture("/inactive.png"));
	settingsButton->setPressedImage(driver->getTexture("/active.png"));

	IGUIButton* helpButton = gui->addButton(rect<s32>(leftMargin, 3.0 * buttonSpan + 2.0 * BUTTON_HEIGHT + buttonTopMargin,
		leftMargin + BUTTON_WIDTH, 3.0 * (buttonSpan + BUTTON_HEIGHT) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_HELP_BUTTON, L"HELP", L"Game help");
	helpButton->setUseAlphaChannel(true);
	helpButton->setDrawBorder(false);
	helpButton->setImage(driver->getTexture("/inactive.png"));
	helpButton->setPressedImage(driver->getTexture("/active.png"));

	IGUIButton* aboutButton = gui->addButton(rect<s32>(leftMargin, 4.0 * buttonSpan + 3.0 * BUTTON_HEIGHT + buttonTopMargin,
		leftMargin + BUTTON_WIDTH, 4.0 * (buttonSpan + BUTTON_HEIGHT) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_ABOUT_BUTTON, L"ABOUT", L"About the author");
	aboutButton->setUseAlphaChannel(true);
	aboutButton->setDrawBorder(false);
	aboutButton->setImage(driver->getTexture("/inactive.png"));
	aboutButton->setPressedImage(driver->getTexture("/active.png"));

	IGUIButton* exitButton = gui->addButton(rect<s32>(leftMargin, 5.0 * buttonSpan + 4.0 * BUTTON_HEIGHT + buttonTopMargin,
		leftMargin + BUTTON_WIDTH, 5.0 * (buttonSpan + BUTTON_HEIGHT) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_EXIT_BUTTON, L"EXIT", L"Quit the game");
	exitButton->setUseAlphaChannel(true);
	exitButton->setDrawBorder(false);
	exitButton->setImage(driver->getTexture("/inactive.png"));
	exitButton->setPressedImage(driver->getTexture("/active.png"));

	/*
	gui->addButton(rect<s32>(leftMargin, 2.0 * buttonSpan + 1.0 * buttonHeight + buttonTopMargin,
		width / 2, 2.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_SETTINGS_BUTTON, L"SETTINGS", L"Change game settings");
	gui->addButton(rect<s32>(leftMargin, 3.0 * buttonSpan + 2.0 * buttonHeight + buttonTopMargin,
		width / 2, 3.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_HELP_BUTTON, L"HELP", L"Game help");
	gui->addButton(rect<s32>(leftMargin, 4.0 * buttonSpan + 3.0 * buttonHeight + buttonTopMargin,
		width / 2, 4.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_ABOUT_BUTTON, L"ABOUT", L"About the author");
	gui->addButton(rect<s32>(leftMargin, 5.0 * buttonSpan + 4.0 * buttonHeight + buttonTopMargin,
		width / 2, 5.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENT::MAINMENU_EXIT_BUTTON, L"EXIT", L"Quit the game");
	*/

	//gui->loadGUI("/gui.xml");
	

	//----------------------------------
	//set up scene elements
	//----------------------------------

	//root node for main menu scene elements
	mainMenuNode = scene->addEmptySceneNode(0, MAINMENU_ELEMENT::MAINMENU_ROOT_NODE);

	//create main menu background as a skybox element
	ISceneNode* background = scene->addSkyBoxSceneNode(
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		mainMenuNode,
		MAINMENU_ELEMENT::MAINMENU_BACKGROUND);
	if(!background){
		cout << "MainMenu: Failed to create background" << endl;
		return false;
	}

	//create fighter mesh
	IMesh* fighter = scene->getMesh("/fighter.irrmesh");
	if(!fighter){
		cout << "MainMenu: Failed to load fighter mesh" << endl;
		return false;
	}
	//create an animation under fighter mesh
	IAnimatedMeshSceneNode* anms = scene->addAnimatedMeshSceneNode(scene->getMesh("/fighter.irrmesh"), 
		mainMenuNode,
		MAINMENU_ELEMENT::MAINMENU_FIGHTER);
	anms->setPosition(vector3df(-20,-15,-5));
	anms->setRotation(vector3df(45,-210,-3));
	if(anms){
		array<vector3df> points; //directional points of spline fighter traectory
		points.push_back(vector3df(-20,-15,-5));
		points.push_back(vector3df(-20,-13,-5));
		points.push_back(vector3df(-20,-10,-5));
		points.push_back(vector3df(-20,-13,-5));
		points.push_back(vector3df(-20,-15,-5));
		ISceneNodeAnimator* anim = scene->createFollowSplineAnimator(
				0,
				points
			);
		if(anim){
			anms->addAnimator(anim);
			anim->drop();
		}
	}

	//set up the scene camera
	camera = scene->addCameraSceneNode(mainMenuNode);
	camera->setPosition(vector3df(0,0,50));
    camera->setFarValue(50.f);
	camera->setTarget(core::vector3df(0,0,0));
	//scene->setActiveCamera(camera);

	gui->saveGUI("gui.xml");

	return true;
}

void MainMenu::setVisible(bool flg){
	mainMenuNode->setVisible(flg);
	if(!flg){
		gui->clear();
	}
	else{
		gui->loadGUI("gui.xml");
		device->getSceneManager()->setActiveCamera(camera);
	}
	//for(int i = MAINMENU_ELEMENTS::MAINMENU_TITLE; i <= MAINMENU_ELEMENTS::MAINMENU_EXIT_BUTTON; i++)

		
}
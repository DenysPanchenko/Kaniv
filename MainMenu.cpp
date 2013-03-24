#include "MainMenu.h"

MainMenu::MainMenu(IVideoDriver* vdr, IGUIEnvironment* genv, ISceneManager* sc, int sw, int sh) : 
	driver(vdr), gui(genv), scene(sc), width(sw), height(sh){
	if(!vdr || !genv)
		return;
	visible = true;
	init();
};

bool MainMenu::init(){
	
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
	
	//create main menu title
	ITexture* captionTexture = driver->getTexture("/title.png");
	if(!captionTexture){
		cout << "MainMenu: Failed to load title" << endl;
		return false;
	}

	dimension2d<u32> size = captionTexture->getSize();
	int topMargin = 15;
	int leftMargin = 50;//1.0 * (width - size.Width) / 2;

	IGUIImage* captionImage = gui->addImage(core::rect<s32>(
		leftMargin,topMargin,
		leftMargin + size.Width ,size.Height)); //centered relative to the fixed resolution
	captionImage->setImage(captionTexture);
	driver->removeTexture(captionTexture); //free memmory

	//auxiliary variables for buttons positionin
	int remaining = height - topMargin - size.Height;
	int buttonHeight = 100;
	int buttonSpan = ((remaining - (buttonHeight * 5)) / 6.0);
	int buttonTopMargin = topMargin + size.Height;

	//set up menu buttons	
	IGUIButton* newGameButton = gui->addButton(rect<s32>(leftMargin, 1.0 * buttonSpan + 0.0 * buttonHeight + buttonTopMargin,
		width / 2, 1.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENTS::MAINMENU_NEW_GAME_BUTTON, L"NEW GAME", L"Start new game");
	/*
	newGameButton->setImage(driver->getTexture("/newgame_inactive.png"));
	newGameButton->setPressedImage(driver->getTexture("/newgame_active.png"));
	*/
	gui->addButton(rect<s32>(leftMargin, 2.0 * buttonSpan + 1.0 * buttonHeight + buttonTopMargin,
		width / 2, 2.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENTS::MAINMENU_SETTINGS_BUTTON, L"SETTINGS", L"Change game settings");
	gui->addButton(rect<s32>(leftMargin, 3.0 * buttonSpan + 2.0 * buttonHeight + buttonTopMargin,
		width / 2, 3.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENTS::MAINMENU_HELP_BUTTON, L"HELP", L"Game help");
	gui->addButton(rect<s32>(leftMargin, 4.0 * buttonSpan + 3.0 * buttonHeight + buttonTopMargin,
		width / 2, 4.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENTS::MAINMENU_ABOUT_BUTTON, L"ABOUT", L"About the author");
	gui->addButton(rect<s32>(leftMargin, 5.0 * buttonSpan + 4.0 * buttonHeight + buttonTopMargin,
		width / 2, 5.0 * (buttonSpan + buttonHeight) + buttonTopMargin),
		0, MAINMENU_ELEMENTS::MAINMENU_ABOUT_BUTTON, L"EXIT", L"Quit the game");
	

	//gui->loadGUI("/gui.xml");
	

	//----------------------------------
	//set up scene elements
	//----------------------------------

	//root node for main menu scene elements
	mainMenuNode = scene->addEmptySceneNode(0, MAINMENU_ELEMENTS::MAINMENU_ROOT_NODE);

	//create main menu background as a skybox element
	ISceneNode* background = scene->addSkyBoxSceneNode(
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		driver->getTexture("/background.jpg"),
		mainMenuNode,
		MAINMENU_ELEMENTS::MAINMENU_BACKGROUND);
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
		MAINMENU_ELEMENTS::MAINMENU_FIGHTER);
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

	return true;
}

void MainMenu::setVisible(bool flg){
	mainMenuNode->setVisible(flg);
	if(!flg){
		gui->saveGUI("gui.xml");
		gui->clear();
	}
	else{
		gui->loadGUI("gui.xml");
	}
	//for(int i = MAINMENU_ELEMENTS::MAINMENU_TITLE; i <= MAINMENU_ELEMENTS::MAINMENU_EXIT_BUTTON; i++)

		
}
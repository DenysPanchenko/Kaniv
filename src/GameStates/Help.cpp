#include "Help.h"

Help::Help(IrrlichtDevice* dev) : AbstractState(dev){
	//init();
}

bool Help::init(){
	IVideoDriver* driver = device->getVideoDriver();
	gui = device->getGUIEnvironment();
	
	dimension2d<u32> screenResolution = driver->getScreenSize();
	int width = screenResolution.Width;
	int height = screenResolution.Height;

	//----------------------
	//set up gui elemetns
	//----------------------

	ITexture* captionTexture = driver->getTexture("help.png");

	IGUIImage* captionImage = gui->addImage(core::rect<s32>(0,0,SCREEN_WIDTH,200));

	captionImage->setImage(captionTexture);
	driver->removeTexture(captionTexture); //free memmory

	int bottomMargin = 50;
	int x1 = 50, y1 = 100; //left top corner
	int x2 = SCREEN_WIDTH - 50, y2 = SCREEN_HEIGHT - BUTTON_HEIGHT - 100; //bottom right corner

	IGUIStaticText* text = gui->addStaticText(
		L"Objective: defend your planet from invasion\n\
		Available weapons: rockets\n\
		Enemies: 4 types of aliens spacecraft\n\n\
		Be careful of falling asteroids\n\
		Don't let them cross our frontier\n\n\
		Good luck, captain!\n\n\
		Push \"New game\" to begin the game\n\
		To exit the game press ESC",
		rect<s32>(x1, y1, x2, y2),true);
	text->setOverrideColor(SColor(255,255,255,255));
	text->enableOverrideColor(true);
	text->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER); //short about information
	
	IGUIButton* back = gui->addButton(rect<s32>(
		width / 2.0 - BUTTON_WIDTH / 2.0,
		height - bottomMargin - BUTTON_HEIGHT,
		width / 2.0 + BUTTON_WIDTH / 2.0,
		height - bottomMargin),
		0, ABOUT_ELEMENT::ABOUT_BACK_BUTTON, L"BACK", L"Return to main menu");
	back->setUseAlphaChannel(true);
	back->setDrawBorder(false);
	back->setImage(driver->getTexture("inactive.png"));
	back->setPressedImage(driver->getTexture("active.png")); //back to main menu button

	gui->saveGUI("help_gui.xml");
	return false;
}

void Help::setVisible(bool flg){
	if(flg)
		gui->loadGUI("help_gui.xml");
	else 
		gui->clear();
}
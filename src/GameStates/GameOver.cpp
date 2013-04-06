#include "GameOver.h"

GameOver::GameOver(IrrlichtDevice* dev) : AbstractState(dev){

}

bool GameOver::init(){
	IVideoDriver* driver = device->getVideoDriver();
	gui = device->getGUIEnvironment();
	
	dimension2d<u32> screenResolution = driver->getScreenSize();
	int width = screenResolution.Width;
	int height = screenResolution.Height;

	//----------------------
	//set up gui elemetns
	//----------------------
	
	IGUIImage* background = gui->addImage(driver->getTexture("gameover_background.png"), position2d<s32>(75,30), true);

	int x1 = width / 2 - 300, y1 = height / 8 - 100;
	int x2 = width / 2 + 300, y2 = height / 8 + 100;

	IGUIStaticText* text = gui->addStaticText( L"GAME OVER",
		rect<s32>(x1, y1, x2, y2),true);
	text->setOverrideColor(SColor(255,255,255,255));
	text->enableOverrideColor(true);
	text->setDrawBorder(false);
	text->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
	
	int bottomSpan = 50;

	IGUIButton* replay = gui->addButton(rect<s32>(
		width / 2.0 - BUTTON_WIDTH / 2.0,
		height - bottomSpan - BUTTON_HEIGHT,
		width / 2.0 + BUTTON_WIDTH / 2.0,
		height - bottomSpan),
		0, ABOUT_ELEMENT::ABOUT_BACK_BUTTON, L"MAIN MENU", L"Return to main menu");
	/*
	IGUIButton* back = gui->addButton(rect<s32>(
		width / 2.0 - BUTTON_WIDTH / 2.0,
		height - bottomSpan - BUTTON_HEIGHT,
		width / 2.0 + BUTTON_WIDTH / 2.0,
		height - bottomSpan),
		0, ABOUT_ELEMENT::ABOUT_BACK_BUTTON, L"BACK", L"Return to main menu");
	*/
	replay->setUseAlphaChannel(true);
	replay->setDrawBorder(false);
	replay->setImage(driver->getTexture("inactive.png"));
	replay->setPressedImage(driver->getTexture("active.png"));
	
	gui->saveGUI("gameover_gui.xml");
	return false;
};

void GameOver::setVisible(bool flg){
	if(!flg)
		gui->clear();
	else
		gui->loadGUI("gameover_gui.xml");
};
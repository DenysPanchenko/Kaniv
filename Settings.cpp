#include "Settings.h"

Settings::Settings() {
	
}

void Settings::setVisible(bool flg){
	if(flg)
		gui->loadGUI("settings_gui.xml");
	else 
		gui->clear();
}

bool Settings::init(){
	IVideoDriver* driver = device->getVideoDriver();
	gui = device->getGUIEnvironment();
	
	dimension2d<u32> screenResolution = driver->getScreenSize();
	int width = screenResolution.Width;
	int height = screenResolution.Height;

	//----------------------
	//set up gui elemetns
	//----------------------

	ITexture* captionTexture = driver->getTexture("/about.png");
	if(!captionTexture){
		cout << "About: Failed to load title" << endl;
		return false;
	}

	dimension2d<u32> size = captionTexture->getSize();
	int topMargin = 15;

	IGUIImage* captionImage = gui->addImage(core::rect<s32>(
		width / 2.0 - size.Width / 2.0,
		topMargin,
		width / 2.0 + size.Width / 2.0,
		topMargin + size.Height)); //centered relative to the fixed resolution
	captionImage->setImage(captionTexture);
	driver->removeTexture(captionTexture); //free memmory

	gui->addStaticText(L"13",rect<s32>(
		10,10,100,100),true);

	int buttonWidth = 500;
	int buttonHeight = 50;
	int bottomMargin = 50;
	gui->addButton(rect<s32>(
		width / 2.0 - buttonWidth / 2.0,
		height - bottomMargin - buttonHeight,
		width / 2.0 + buttonWidth / 2.0,
		height - bottomMargin),
		0, SETTINGS_ELEMENT::SETTINGS_BACK_BUTTON, L"BACK", L"Return to main menu");

	gui->saveGUI("settings_gui.xml");
	return false;
}
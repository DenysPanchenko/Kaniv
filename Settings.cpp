#include "Settings.h"

Settings::Settings(IrrlichtDevice* dev) : AbstractState(dev){
	
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

	ITexture* captionTexture = driver->getTexture("/settings.png");
	if(!captionTexture){
		cout << "About: Failed to load title" << endl;
		return false;
	}

	dimension2df size(434, 85);
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

	int bottomMargin = 50;
	IGUIButton* back = gui->addButton(rect<s32>(
		width / 2.0 - BUTTON_WIDTH / 2.0,
		height - bottomMargin - BUTTON_HEIGHT,
		width / 2.0 + BUTTON_WIDTH / 2.0,
		height - bottomMargin),
		0, ABOUT_ELEMENT::ABOUT_BACK_BUTTON, L"BACK", L"Return to main menu");
	back->setUseAlphaChannel(true);
	back->setDrawBorder(false);
	back->setImage(driver->getTexture("/inactive.png"));
	back->setPressedImage(driver->getTexture("/active.png"));

	gui->saveGUI("settings_gui.xml");
	return false;
}
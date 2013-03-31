#include "About.h"

About::About(IrrlichtDevice* dev) : AbstractState(dev){
	//init();
}

bool About::init(){
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

	dimension2df size(434, 85);
	int topMargin = 15;

	IGUIImage* captionImage = gui->addImage(core::rect<s32>(
		width / 2.0 - size.Width / 2.0,
		topMargin,
		width / 2.0 + size.Width / 2.0,
		topMargin + size.Height)); //centered relative to the fixed resolution

	captionImage->setImage(captionTexture);
	driver->removeTexture(captionTexture); //free memmory

	int bottomMargin = 50;

	int x1 = 50, y1 = topMargin + size.Height + topMargin;
	int x2 = width - 50, y2 = height - bottomMargin - BUTTON_HEIGHT - topMargin;

	IGUIStaticText* text = gui->addStaticText(
		L"Space Battle\nGame created by\nDenis Panchenko\nmail: actor07@ukr.net\nXPN 2013 Kiev",
		rect<s32>(x1, y1, x2, y2),true);
	text->setOverrideColor(SColor(255,255,255,255));
	text->enableOverrideColor(true);
	
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

	gui->saveGUI("about_gui.xml");
	return false;
}

void About::setVisible(bool flg){
	if(flg)
		gui->loadGUI("about_gui.xml");
	else 
		gui->clear();
}
#include "Settings.h"

#include <iostream>

using namespace std;

Settings::Settings(IrrlichtDevice* dev, SETTINGS_STRUCT* set) : AbstractState(dev), SETTINGS(set){
	
}

void Settings::setVisible(bool flg){
	if(flg){
		gui->loadGUI("settings_gui.xml");
		IGUICheckBox* checkBox = (IGUICheckBox*)gui->getRootGUIElement()->getElementFromId(SETTINGS_SOUND_CHECKBOX);
		if(!SETTINGS->soundVolume)
			checkBox->setChecked(false);
		else
			checkBox->setChecked(true);
		IGUIComboBox* comboBox = (IGUIComboBox*)gui->getRootGUIElement()->getElementFromId(SETTINGS_COMBOBOX);
		switch(SETTINGS->gameMode){
		case GAME_MODE_EASY:
			comboBox->setSelected(0);
			break;
		case GAME_MODE_NORMAL:
			comboBox->setSelected(1);
			break;
		case GAME_MODE_HARD:
			comboBox->setSelected(2);
			break;
		default:
			break;
		}
	} else gui->clear();
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

	dimension2df size(619, 94);
	int topMargin = 15;

	IGUIImage* captionImage = gui->addImage(core::rect<s32>(
		width / 2.0 - size.Width / 2.0,
		topMargin,
		width / 2.0 + size.Width / 2.0,
		topMargin + size.Height)); //centered relative to the fixed resolution

	captionImage->setImage(captionTexture);
	driver->removeTexture(captionTexture); //free memmory

	IGUIStaticText* labelSound = gui->addStaticText( L"SOUND (ENABLE/DISABLE)",
		rect<s32>(200, 150, 500, 200),true);
	labelSound->setOverrideColor(SColor(255,255,255,255));
	labelSound->enableOverrideColor(true);
	labelSound->setDrawBorder(false);
	labelSound->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
	IGUICheckBox* soundEnableCheckBox = gui->addCheckBox(true, rect<s32> (600,150,650,200), 0, SETTINGS_SOUND_CHECKBOX, L"");

	IGUIStaticText* labelDifficulty = gui->addStaticText( L"GAME DIFFICULTY",
		rect<s32>(200, 350, 500, 400),true);
	labelDifficulty->setOverrideColor(SColor(255,255,255,255));
	labelDifficulty->enableOverrideColor(true);
	labelDifficulty->setDrawBorder(false);
	labelDifficulty->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
	IGUIComboBox* difficultyComboBox = gui->addComboBox(rect<s32>(600, 350, 850, 400),0,SETTINGS_COMBOBOX);
	difficultyComboBox->addItem(L"EASY",SETTINGS_MODE_EASY);
	difficultyComboBox->addItem(L"NORMAL",SETTINGS_MODE_NORMAL);
	difficultyComboBox->addItem(L"HARD",SETTINGS_MODE_HARD);

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
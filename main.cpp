#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;
using namespace io;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "MainMenu.h"
#include "EventReceiver.h"

ISceneNode* skyBox;

int main(){
	EventReceiver eventReceiver;

	//create irrlicht game device
	IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32> (1024,768), 16, false, false, false, &eventReceiver);
	if(!device) //device isn't created => exit the program
		return -1;

	device->setWindowCaption(L"Space Battle XPN 2013");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* scene = device->getSceneManager();
	IGUIEnvironment* gui = device->getGUIEnvironment();
	//scene->getParameters()->setAttribute(scene::COLLADA_CREATE_SCENE_INSTANCES, true);

	//ISceneNode* nCamera = scMngr->addCameraSceneNode(0,core::vector3df(1,1,1),core::vector3df(0,0,0), -1);
	/*
	scene->addLightSceneNode(0, core::vector3df(200,200,200),
		video::SColorf(1.0f,1.0f,1.0f),2000);
	scene->setAmbientLight(video::SColorf(0.3f,0.3f,0.3f));
	*/
	/*
	ISceneNode* mainMenuNode = scMngr->addEmptySceneNode();
	MainMenu mainMenu(mainMenuNode);

	
	ITexture* captionTexture = vDriver->getTexture("/caption2.png");
	if(!captionTexture)
		return -1;
	IGUIImage* captionImage = guiEnv->addImage(core::rect<s32>(10,10,1100,500));
	captionImage->setImage(captionTexture);
	vDriver->removeTexture(captionTexture);
	*/

    IGUIFont* m_defaultFont = 0;
	IFileSystem* m_fileSystem = device->getFileSystem();
    if(m_fileSystem->existFile("/font.zip"))
    {
        m_fileSystem->addZipFileArchive("/font.zip");
        m_defaultFont = gui->getFont("/myfont.xml");
        if(m_defaultFont)
        {
            m_defaultFont->grab();
            gui->getSkin()->setFont(m_defaultFont);
        } else printf("Error loading font");
    }
    if(!m_defaultFont)
        printf("Error loading defaults.zip\n");
 
   /*
	IGUIStaticText* caption = guiEnv->addStaticText(L"SPACE BATTLE",rect<s32>(10,10, 1014,200), true);
	caption->setDrawBorder(false);
	caption->setBackgroundColor(SColor(0,0,0,1));
    caption->setOverrideColor(SColor(255,255,255,255));
	*/
	
	MainMenu mm(driver, gui, scene, 1024, 768);	
	//mm.setVisible(false);
	//mm.setVisible(true);
	
	
	ICameraSceneNode* cam = scene->addCameraSceneNode();
	cam->setPosition(vector3df(0,0,50));
    cam->setFarValue(20000.f);
	cam->setTarget(core::vector3df(0,0,0));
	scene->setActiveCamera(cam);


	/*
	ICameraSceneNode* camera = scene->addCameraSceneNodeMaya();
	camera->setFarValue(20000.f);
	// Maya cameras reposition themselves relative to their target, so target the location
	// where the mesh scene node is placed.
	camera->setTarget(core::vector3df(0,30,0));

	scene->setActiveCamera(camera);

	
	*/
		
	//main game loop
	while(device->run() && driver){
		driver->beginScene(true, true, 0);
		scene->drawAll();
		gui->drawAll();
		driver->endScene();
	}

	return 0;
}
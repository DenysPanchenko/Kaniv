#include "NewGame.h"

NewGame::NewGame(){
	//init();
}

bool NewGame::init(){
	gui = device->getGUIEnvironment();
	scene = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();


	//create root node for level scene
	gameRootNode = scene->addEmptySceneNode(0, NEWGAME_ELEMENT::NEWGAME_ROOT_NODE);

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

	//create fighter mesh
	IMesh* fighter = scene->getMesh("/fighter.irrmesh");
	if(!fighter){
		cout << "MainMenu: Failed to load fighter mesh" << endl;
		return false;
	}

	IMeshSceneNode* node = scene->addMeshSceneNode(
		fighter,
		gameRootNode,
		NEWGAME_ELEMENT::NEWGAME_FIGHTER,
		vector3df(0,0,0));
	node->setRotation(vector3df(-30,0,0));

	IParticleSystemSceneNode* left = scene->addParticleSystemSceneNode(false,node,
		NEWGAME_ELEMENT::NEWGAME_LEFT_TURBINE,vector3df(4,-11,-15),vector3df(-150,0,0));
	IParticleSystemSceneNode* right = scene->addParticleSystemSceneNode(false,node,
		NEWGAME_ELEMENT::NEWGAME_RIGHT_TURBINE,vector3df(-4,-11,-15),vector3df(-150,0,0));
	//left->setParticleSize(dimension2d<f32>(5.0f, 5.0f));

	IParticleEmitter* emitter = left->createBoxEmitter(
		aabbox3df(-1,0,-1,1,1,1),
		vector3df(0.0f, -0.03f, 0.0f),
		400, 800,
		SColor(0,255,255,255),SColor(0,255,255,255),
		400, 800, 0,
		dimension2df(5,5), dimension2df(5,5)
		);

	left->setEmitter(emitter);
	right->setEmitter(emitter);

	emitter->drop();

	IParticleFadeOutAffector* paf = left->createFadeOutParticleAffector();
	paf->setFadeOutTime(1000);
	left->addAffector(paf);
	right->addAffector(paf);
	paf->drop();

	right->setMaterialFlag(video::EMF_LIGHTING, false);
    right->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    right->setMaterialTexture(0, driver->getTexture("/brightfire.jpg"));
    right->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	left->setMaterialFlag(video::EMF_LIGHTING, false);
    left->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    left->setMaterialTexture(0, driver->getTexture("/brightfire.jpg"));
    left->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	camera = scene->addCameraSceneNode(gameRootNode);
	camera->setPosition(vector3df(0,0,-150));
	camera->setTarget(vector3df(0,0,0));

	return true;
}

void NewGame::setVisible(bool flg){
	gameRootNode->setVisible(flg);
	if(!flg){
		gui->clear();
	}
	else{
		gui->loadGUI("newgame_gui.xml");
		device->getSceneManager()->setActiveCamera(camera);
	}
}
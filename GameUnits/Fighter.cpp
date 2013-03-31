#include "Fighter.h"

Fighter::Fighter(IrrlichtDevice* dev, ISceneNode* parent, ISceneManager* scene, s32 id, vector3df pos, vector3df rot) {
	device = dev;
	//create fighter mesh
	IMesh* fighter = scene->getMesh("/fighter.irrmesh");
	ship = scene->addMeshSceneNode(fighter,
		parent,
		NEWGAME_ELEMENT::NEWGAME_FIGHTER,
		pos, rot);
	//fighter->drop(); //raise an error during exiting

	//create left turbine
	IParticleSystemSceneNode* left = scene->addParticleSystemSceneNode(false, ship,
		NEWGAME_ELEMENT::NEWGAME_LEFT_TURBINE,vector3df(4,-11,-15),vector3df(-150,0,0));
	//create right turbine
	IParticleSystemSceneNode* right = scene->addParticleSystemSceneNode(false, ship,
		NEWGAME_ELEMENT::NEWGAME_RIGHT_TURBINE,vector3df(-4,-11,-15),vector3df(-150,0,0));
	//left->setParticleSize(dimension2d<f32>(5.0f, 5.0f));

	//create emitter for fire for turbines
	IParticleEmitter* emitter = left->createBoxEmitter(
		aabbox3df(-1,0,-1,1,1,1),
		vector3df(0.0f, -0.03f, 0.0f),
		600, 1000,
		SColor(0,255,255,255),SColor(0,255,255,255),
		400, 600, 0,
		dimension2df(5,5), dimension2df(5,5)
		);

	//apply emitter to turbines
	left->setEmitter(emitter);
	right->setEmitter(emitter);

	emitter->drop();

	IParticleFadeOutAffector* paf = left->createFadeOutParticleAffector();
	paf->setFadeOutTime(1000);
		
	left->addAffector(paf);
	right->addAffector(paf);

	paf->drop();

	//set up parameters for left turbine fire
	right->setMaterialFlag(video::EMF_LIGHTING, false);
    right->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    right->setMaterialTexture(0, device->getVideoDriver()->getTexture("/brightfire.jpg"));
    right->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//set up parameters for right turbine fire
	left->setMaterialFlag(video::EMF_LIGHTING, false);
    left->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    left->setMaterialTexture(0, device->getVideoDriver()->getTexture("/brightfire.jpg"));
    left->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//add left rocket
	LEFT_ROCKET_ID = -100;
	RIGHT_ROCKET_ID = -101;

	ISceneNode* leftRocket = scene->addMeshSceneNode(
		scene->getMesh("/rocket.irrmesh"),
		ship,
		LEFT_ROCKET_ID,
		vector3df(-17.3, -7.8, -9.5),
		vector3df(30.0,0.0,0.0));

	//add right rocket
	ISceneNode* rightRocket = scene->addMeshSceneNode(
		scene->getMesh("/rocket.irrmesh"),
		ship,
		RIGHT_ROCKET_ID,
		vector3df(16.5, -7.0, -10.5),
		vector3df(30.0,0.0,0.0));
}

vector3df Fighter::getLeftRocketPosition(){
	return ship->getPosition();
}

vector3df Fighter::getRightRocketPosition(){
	return device->getSceneManager()->getSceneNodeFromId(RIGHT_ROCKET_ID)->getPosition();
}

void Fighter::leftShot(){
	//scene->getSceneNodeFromId(LEFT_ROCKET_NODE)->setVisible(false);
}

void Fighter::rightShot(){
}

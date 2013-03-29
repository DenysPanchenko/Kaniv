#include "Rocket.h"

Rocket::Rocket(IrrlichtDevice* device, s32 id, bool im, ISceneNode* parent, vector3df pos, vector3df rot) {
	inMotion = im;
	root = parent;
	ISceneManager* scene = device->getSceneManager();

	//create fighter mesh
	IMesh* rocketMesh = scene->getMesh("/rocket.irrmesh");
	/*
	rocket = scene->addMeshSceneNode(rocketMesh,
		parent,
		NEWGAME_ELEMENT::NEWGAME_FIGHTER,
		pos, rot);
		*/
	//rocket->setVisible(false);
	//fire
	/*
	
	*/
	anms = scene->addAnimatedMeshSceneNode(
		scene->getMesh("/rocket.irrmesh"),
		parent, id);

	IParticleSystemSceneNode* fire = scene->addParticleSystemSceneNode(false, anms,
		NEWGAME_ELEMENT::NEWGAME_RIGHT_TURBINE,vector3df(0,0,0),vector3df(-150,0,0));

	//create emitter for fire for turbines
	IParticleEmitter* emitter = fire->createBoxEmitter(
		aabbox3df(-1,0,-1,1,1,1),
		vector3df(0.0f, -0.03f, 0.0f),
		400, 800,
		SColor(0,255,255,255),SColor(0,255,255,255),
		400, 800, 0,
		dimension2df(5,5), dimension2df(5,5)
		);

	//apply emitter to turbines
	fire->setEmitter(emitter);

	int screenHeight = device->getVideoDriver()->getScreenSize().Height;

	if(anms){
		anim = scene->createFlyStraightAnimator(
			pos, vector3df(pos.X, SCREEN_HEIGHT, pos.Z),100000);
		if(anim){
			anms->addAnimator(anim);
			anim->drop();
		}
	}
	
	//anms->setVisible(false);
}

void Rocket::setIsUsing(bool flg){
	inMotion = flg;
}

bool Rocket::isUsing(){
	return inMotion;
}

void Rocket::launch(const vector3df& pos){

}
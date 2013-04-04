#ifndef EnemyGenerator_h
#define EnemyGenerator_h

#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;

#include "Global.h"
#include "../GameUnits/Inky.h"
#include "../GameUnits/Clyde.h"
#include "../GameUnits/Pinky.h"
#include "../GameUnits/Craft.h"
#include "../GameUnits/Blinky.h"

#include <ctime>
#include <cstdlib> //AI is mostly from random generated numbers

class EnemyGenerator {
	IrrlichtDevice* device;
	ISceneNode* rootNode;

	u32 currentTime; 
	u32 lastGenerationTime; //last enemy wave generation time
	u32 lastDifficultyUpdate;
	f32 updateDifficultyTime;
	
	struct BlinkyInfo { //struct that contains all parameters of last generated blinky wave
		f32 speed;
		u32 density; //time period in what blinky will appear
		u32 lastGeneration; //last blinky generation time
		int remaining; //quantity of blinky remainig to generate in current wave
		vector3df headPosition;
		ENEMY_DIRECTION direction;
		BlinkyInfo(){ //constructor with appropriate values
			density = 750;
			remaining = 0;
			headPosition = vector3df();
			direction = ENEMY_LEFT; 
			lastGeneration = 0;
		}
	} blinkyInfo;
	
	struct Difficulty{
		f32 speedFactor;
		f32 generationFrequency;
		GAME_MODE mode;
		Difficulty(){
			speedFactor = 0.15;
			mode = GAME_MODE_EASY;
			generationFrequency = 2;
		}
	} difficulty;
	
	Clyde* clyde; //the most serious enemy in game, almost boss, can be only one
	array<Craft*>& pool;
	
	void updateBlinkyQueue(); //helps generate consicutive series of blinky
	void generateInkyWave(f32 speed);
	void generatePinkyWave(f32 speed);
	void generateClydeWave(f32 speed);
	void generateBlinkyWave(f32 speed);

	ENEMY_DIRECTION getDirection();
public:
	EnemyGenerator(GAME_MODE mode, IrrlichtDevice* dev, ISceneNode* prnt, array<Craft*>& p);
	~EnemyGenerator();

	void generateWave(ENEMYWAVE_TYPE type, u32 time); //generate enemy wave of certain type
	bool isReady(u32 time); //isn't it to early to add new enemies
	void reset(GAME_MODE gameMode);
};

#endif
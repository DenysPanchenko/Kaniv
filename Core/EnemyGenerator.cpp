#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(GAME_MODE m, IrrlichtDevice* dev, ISceneNode* prnt, array<Craft*>& p) 
	: device(dev), rootNode(prnt), pool(p) {
	srand(time_t());
	clyde = 0; //clyde isn'talive at the begining
	blinkyInfo = BlinkyInfo();
	difficulty = Difficulty();
	difficulty.mode = m;
	lastGenerationTime = 0;
	lastDifficultyUpdate = 0;
	updateDifficultyTime = 10;
};

void EnemyGenerator::generateWave(ENEMYWAVE_TYPE type, u32 time){
	lastGenerationTime = time;
	(ENEMYWAVE_TYPE) type = (ENEMYWAVE_TYPE)(rand() % 5);
	switch(type){
	case ENEMYWAVE_ENEMY_1:
		generateBlinkyWave(0.70f * difficulty.speedFactor);
		break;
	case ENEMYWAVE_ENEMY_2:
		generatePinkyWave(0.15f * difficulty.speedFactor);
		break;
	case ENEMYWAVE_ENEMY_3:
		generateClydeWave(100.f * difficulty.speedFactor);
		break;
	case ENEMYWAVE_ENEMY_4:
		generateInkyWave(0.15f * difficulty.speedFactor);
		break;
	case ENEMYWAVE_ASTEROID:
		break;
	case ENEMYWAVE_EMPTY:
		break;
	default:
		break;
	}
}

void EnemyGenerator::generatePinkyWave(f32 speed){
	ENEMY_DIRECTION direction = getDirection(); //from left to right or vice versa
	int quantity = 3 + (rand() % 3); // group of enemy consists of 3 to 5 crafts
	int enemySpan = SW_SF / quantity; //calculate span between enemies
	for(int i = 0; i < quantity; i++){
		pool.push_back(new Pinky(device,rootNode, PINKY_ID,
			vector3df(SW_SF - i * enemySpan, SH_SF + ENEMY_BUFFER_HEIGHT, 0),
			speed, currentTime, direction));
	}
}

void EnemyGenerator::generateBlinkyWave(f32 speed){
	if(!blinkyInfo.remaining){
		blinkyInfo.lastGeneration = currentTime;
		blinkyInfo.direction = getDirection();
		blinkyInfo.remaining = 3 + (rand() % 10); //group of enemy consists of 3 to 10 crafts
		int startPos = rand() % 3;
		vector3df headPosition;
		if(!startPos)
			headPosition.X = -(2 * SW_SF / 3);
		else if(startPos == 1)
			headPosition.X = 0;
		else 
			headPosition.X = +(2 * SW_SF / 3);
		headPosition.Y = SH_SF + ENEMY_BUFFER_HEIGHT;
		headPosition.Z = 0;
		pool.push_back(new Blinky(device,
			rootNode, BLINKY_ID, headPosition,
			speed, currentTime, ENEMY_DIRECTION::ENEMY_LEFT, 1000, 100));
		blinkyInfo.speed = speed;
		blinkyInfo.headPosition = headPosition;
	}
};

void EnemyGenerator::generateInkyWave(f32 speed){
	int dice = rand() % 2;
	int quantity = 0;
	vector3df headPosition; //position of 
	if(!dice){
		quantity = 3;
		headPosition.X = -(2 * SW_SF / 3);
	} else {
		quantity = 2;
		headPosition.X = -(SW_SF / 3);	
	}
	headPosition.Y = SH_SF + ENEMY_BUFFER_HEIGHT;
	headPosition.Z = 0;
	int groupMargin = (2 * SW_SF / 3);
	for(int i = 0; i < quantity; i++){
		pool.push_back(new Inky(device, rootNode, INKY_ID,
			vector3df(headPosition.X - 50 + groupMargin * i, headPosition.Y + 50, headPosition.Z),speed, currentTime));
		pool.push_back(new Inky(device, rootNode, INKY_ID,
			vector3df(headPosition.X      + groupMargin * i, headPosition.Y, headPosition.Z),speed, currentTime));
		pool.push_back(new Inky(device, rootNode, INKY_ID,
			vector3df(headPosition.X + 50 + groupMargin * i, headPosition.Y + 50, headPosition.Z),speed, currentTime));
	}
}

ENEMY_DIRECTION EnemyGenerator::getDirection(){
	if(!(rand() % 2))
		return ENEMY_DIRECTION::ENEMY_LEFT;
	return ENEMY_DIRECTION::ENEMY_RIGHT;
}

void EnemyGenerator::generateClydeWave(f32 speed){
	if(!Clyde::isAlive()){
			clyde = new Clyde(device,
				rootNode, CLYDE_ID,
				vector3df(0,0,0),
				0.1f, currentTime);
			pool.push_back(clyde);
		}
}

void EnemyGenerator::updateBlinkyQueue(){
	if(currentTime - blinkyInfo.lastGeneration > blinkyInfo.density)
		if(blinkyInfo.remaining > 0){
			pool.push_back(new Blinky(device,
				rootNode, BLINKY_ID, blinkyInfo.headPosition,
				blinkyInfo.speed, currentTime, blinkyInfo.direction, 1000, 100));
			blinkyInfo.lastGeneration = currentTime;
			blinkyInfo.remaining--;
		}
}

bool EnemyGenerator::isReady(u32 time){
	currentTime = time;
	updateBlinkyQueue();
	if((time - lastDifficultyUpdate) / 1000.f > updateDifficultyTime){
		difficulty.speedFactor += 0.025;
		difficulty.generationFrequency += 0.05;
		lastDifficultyUpdate = time;
	}
	if((time - lastGenerationTime) / 1000.f > difficulty.generationFrequency)
		return true;
	return false;
}

void EnemyGenerator::reset(GAME_MODE gameMode){
	switch(gameMode){
	case GAME_MODE_EASY:
		difficulty = Difficulty();
		break;
	case GAME_MODE_NORMAL:
		difficulty = Difficulty();
		difficulty.speedFactor = 0.2;
		difficulty.generationFrequency = 1.75;
		break;
	case GAME_MODE_HARD:
		difficulty = Difficulty();
		difficulty.speedFactor = 0.25;
		difficulty.generationFrequency = 1.5;
		break;
	default:
		break;
	}
	clyde = 0;
	lastGenerationTime = 0;
	lastDifficultyUpdate = 0;
}

EnemyGenerator::~EnemyGenerator(){

}
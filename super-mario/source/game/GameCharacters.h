#ifndef _GAMECHARACTERS_H_
#define _GAMECHARACTERS_H_

#include "./GameVars.h"


#include "../utils/Utils.h"

#include "./Mario.h"
#include "./Goomba.h"
#include "./Koopa.h"

class CharacterLoader {
public:
	static void loadMario();
	static void loadGoombas();
	static void loadKoopas();
	static void loadCharacters();

	static void createCollisionTuples();
};

void CharacterLoader::loadMario() {
	Mario::GetSingleton().initialize(readJSON(MARIO_CONF_PATH));
}

void CharacterLoader::loadGoombas() {
	GoombaHolder::GetSingleton().CreateGoombaMap(readJSON(GOOMBA_CONF_PATH));
}

void CharacterLoader::loadKoopas() {
	KoopaHolder::GetSingleton().Initialize(readJSON(KOOPA_CONF_PATH));
}

void CharacterLoader::loadCharacters() {
	loadKoopas();
	loadGoombas();
	loadMario();

	createCollisionTuples();
}

bool isMarioAbove(Sprite* mario, Sprite* enemy) {
	//an o patos(...) tou mario einai apo panw, tote ok
	int marioY = mario->GetBox().y + mario->GetBox().h / 2; //prosoxi sto meiwn
	int enemyY = enemy->GetBox().y ; //prosoxi sto meiwn //give a look again
	std::cout << "Mario Bottom Y: " << marioY << " Enemy Head Y: " << enemyY << "\n";
	return marioY <= enemyY;
}

void marioGoombaCollision(Sprite* mario, Sprite* goomba) {
	if (!isMarioAbove(mario, goomba)) {
		std::cout << "Mario killed by a goomba!";
		//die mario
		//SpriteManager::GetSingleton().Remove(mario);
		//Mario::GetSingleton().Die();
		Mario::GetSingleton().decreaseLifes();
	}
	else {
		std::cout << "Mario killed a goomba!";
		SpriteManager::GetSingleton().Remove(goomba); //remove right away from the display list!
		//GoombaHolder::GetSingleton().GetInstanceOf(goomba)->destroyAnimators();
		
		Mario::GetSingleton().increaseScoreBy(1);
		Mario::GetSingleton().smallJump();
		goomba->Destroy(); //kill the fucking goomba!
		//trigger mario jump
	}
}

void marioKoopaCollision(Sprite* mario, Sprite* koopa) {
	
	if (!isMarioAbove(mario, koopa)) {
		//std::cout << "Mario killed by a koopa!";
	}
	else {
		std::cout << "Mario killed a koopa!";
		SpriteManager::GetSingleton().Remove(koopa); //remove right away from the display list!
		Mario::GetSingleton().increaseScoreBy(1);
		Mario::GetSingleton().smallJump();
		koopa->Destroy(); //kill the fucking goomba!
		//trigger mario jump
	}
}

void CharacterLoader::createCollisionTuples() {

	Sprite* mario = Mario::GetSingleton().GetCurrSprite();

	std::list<Sprite*> goombas = GoombaHolder::GetSingleton().GetGoombaSpritesList();
	std::list<Sprite*> koopas = KoopaHolder::GetSingleton().GetKoopaSpritesList();

	/*Register the pairs of mario-goombas and mario-koopas*/
	for (Sprite* g : goombas) {
		CollisionChecker::GetSingleton().Register(mario, g, marioGoombaCollision);
	}

	for (Sprite* k : koopas) {
		CollisionChecker::GetSingleton().Register(mario, k, marioKoopaCollision);
	}
}


#endif _GAMECHARACTERS_H_
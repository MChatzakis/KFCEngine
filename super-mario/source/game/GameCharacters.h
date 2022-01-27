#ifndef _GAMECHARACTERS_H_
#define _GAMECHARACTERS_H_

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
	Mario::GetSingleton().initialize();
}

void CharacterLoader::loadGoombas() {
	std::list<Point>gPos = { Point{ 10,300 }, Point{ 500,300 } };
	GoombaHolder::GetSingleton().initialize(gPos);
}

void CharacterLoader::loadKoopas() {
	std::list<Point>kPos = { Point{ 550,200 }, Point{ 540,200 } };
	KoopaHolder::GetSingleton().initialize(kPos);
}

void CharacterLoader::loadCharacters() {
	loadKoopas();
	loadGoombas();
	loadMario();
	createCollisionTuples();
}

bool isMarioAbove(Sprite* mario, Sprite* enemy) {
	//an o patos(...) tou mario einai apo panw, tote ok
	int marioY = mario->GetBox().y - mario->GetBox().h; //prosoxi sto meiwn
	int enemyY = enemy->GetBox().y; //prosoxi sto meiwn
	return marioY == enemyY;
}

void marioGoombaCollision(Sprite* mario, Sprite* goomba) {
	std::cout << "Mario collided with a goomba!";

	
	//CollisionChecker::GetSingleton().Cancel(mario, goomba); //produces exception...
	if (isMarioAbove(mario, goomba)) {
		SpriteManager::GetSingleton().Remove(goomba);
		goomba->Destroy();
	}

	
	
}

void marioKoopaCollision(Sprite* mario, Sprite* koopa) {
	std::cout << "Mario collided with a koopa!";
	SpriteManager::GetSingleton().Remove(koopa);
	//koopa->Destroy();
}



void CharacterLoader::createCollisionTuples() {
	
	Sprite* mario = Mario::GetSingleton().GetCurrSprite();
	
	std::list<Sprite*> goombas = GoombaHolder::GetSingleton().getGoombasSprites();
	std::list<Sprite*> koopas = KoopaHolder::GetSingleton().getKoopasSprites();

	/*Register the pairs of mario-goombas and mario-koopas*/
	for (Sprite* g : goombas) {
		CollisionChecker::GetSingleton().Register(mario, g, marioGoombaCollision);
	}

	for (Sprite* k : koopas) {
		CollisionChecker::GetSingleton().Register(mario, k, marioKoopaCollision);
	}

	//CollisionChecker::GetSingleton().Cancel(mario, koopas.front());

}


#endif _GAMECHARACTERS_H_
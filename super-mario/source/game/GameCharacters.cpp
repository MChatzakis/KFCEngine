#include "GameCharacters.h"

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

//Other useful functions
bool isMarioAbove(Sprite* mario, Sprite* enemy) {
	int marioY = mario->GetBox().y + mario->GetBox().h / 2; //prosoxi sto meiwn
	int enemyY = enemy->GetBox().y; //prosoxi sto meiwn //give a look again

	std::cout << "Mario Bottom Y: " << marioY << " Enemy Head Y: " << enemyY << "\n";

	return marioY <= enemyY;
}


void marioGoombaCollision(Sprite* mario, Sprite* goomba) {
	if (!isMarioAbove(mario, goomba)) {
		std::cout << "Mario killed by a goomba!";
		Mario::GetSingleton().EvaluateDeathAction();
	}
	else {
		std::cout << "Mario killed a goomba!";

		SpriteManager::GetSingleton().Remove(goomba); //remove right away from the display list!		

		Mario::GetSingleton().increaseScoreBy(1);
		Mario::GetSingleton().smallJump();

		goomba->Destroy();
	}
}


void marioKoopaCollision(Sprite* mario, Sprite* koopa) {

	if (!isMarioAbove(mario, koopa)) {
		std::cout << "Mario killed by a koopa!";
		Mario::GetSingleton().EvaluateDeathAction();
	}
	else {
		std::cout << "Mario killed a koopa!";
		SpriteManager::GetSingleton().Remove(koopa);

		Mario::GetSingleton().increaseScoreBy(1);
		Mario::GetSingleton().smallJump();

		koopa->Destroy();
	}
}
#include "DestructionManagement.h"
#include "Coin.h"

void CommitDestructions() {

	ValidateSpritePositions();

	RemoveDeadGoombas();
	RemoveDeadKoopas();
	RemoveRetrievedCoins();

	DestructionManager::Get().Commit(); //Produces an exception.
}

void RemoveRetrievedCoins() {
	std::map<Sprite*, Coin*>gs = CoinHolder::GetSingleton().GetCoinMap();

	for (auto e : gs) {
		Sprite* gSprite = e.first;
		Coin* gClass = e.second;

		if (!gSprite->IsAlive()) {
			CollisionChecker::GetSingleton().cancelAllTuplesOf(gSprite);
			CoinHolder::GetSingleton().Erase(gSprite);
		}

	}
}

void RemoveDeadGoombas() {
	std::map<Sprite*, Goomba*>gs = GoombaHolder::GetSingleton().GetGoombaMap();

	for (auto e : gs) {
		Sprite* gSprite = e.first;
		Goomba* gClass = e.second;

		if (!gSprite->IsAlive()) {
			CollisionChecker::GetSingleton().cancelAllTuplesOf(gSprite);
			GoombaHolder::GetSingleton().ErasePair_freeGoomba(gSprite);
		}

	}
}


void RemoveDeadKoopas() {
	std::map<Sprite*, Koopa*>gs = KoopaHolder::GetSingleton().GetKoopaMap();

	for (auto e : gs) {
		Sprite* kSprite = e.first;
		Koopa* kClass = e.second;

		if (!kSprite->IsAlive()) {
			CollisionChecker::GetSingleton().cancelAllTuplesOf(kSprite);
			KoopaHolder::GetSingleton().ErasePair(kSprite);
		}

	}
}


void ValidateSpritePositions() {
	//delete the sprites that have fallen in the space
	std::list<Sprite*> activeSprites = SpriteManager::GetSingleton().GetDisplayList();
	for (auto s : activeSprites) {
		int x = s->GetBox().x;
		int y = s->GetBox().y;
		Goomba* goomba = GoombaHolder::GetSingleton().GetInstanceOf(s);
		Koopa* koopa = KoopaHolder::GetSingleton().GetInstanceOf(s);

		for (auto r : FALL_COORDINATES_LIST) {
			if (x <= (r.x + r.w) && x >= r.x) {
				if (y >= r.y) {
					if (s == Mario::GetSingleton().GetCurrSprite()) { //mario fall
						Mario::GetSingleton().EvaluateDeathAction();
					}
					else if(goomba != nullptr){ //goomba fall
						goomba->die();
						GoombaHolder::GetSingleton().ErasePair_freeGoomba(s);
						CollisionChecker::GetSingleton().cancelAllTuplesOf(s);
					}
					else if (koopa != nullptr) { //goomba fall
						koopa->die();
						KoopaHolder::GetSingleton().ErasePair(s);
						CollisionChecker::GetSingleton().cancelAllTuplesOf(s);
					}
				}
			}
		}

	}
}
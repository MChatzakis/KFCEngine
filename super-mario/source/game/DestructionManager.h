#ifndef _GAMEDESTRUCTIONMANAGER_H_
#define _GAMEDESTRUCTIONMANAGER_H_

#include "./GameVars.h"
#include "../engine/DestructionManager.h"

void CommitDestructions();
void RemoveDeadGoombas();
void RemoveDeadKoopas();
void ValidateSpritePositions();


void CommitDestructions() {
	
	ValidateSpritePositions();

	RemoveDeadGoombas();
	RemoveDeadKoopas();

	//DestructionManager::Get().Commit(); //Produces an exception.
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

		for (auto r : FALL_COORDINATES_LIST) {
			if (x <= (r.x + r.w) && x >= r.x) {
				if (y >= r.y) {
					if (s == Mario::GetSingleton().GetCurrSprite()) {
						Mario::GetSingleton().EvaluateDeathAction();
					}
					else {
						s->Destroy();
						SpriteManager::GetSingleton().Remove(s);
					}
					
				}
			}
		}

	}
}


#endif _GAMEDESTRUCTIONMANAGER_H_
#ifndef _GAMEDESTRUCTIONMANAGER_H_
#define _GAMEDESTRUCTIONMANAGER_H_

#include "../engine/DestructionManager.h"

void CommitDestructions();
void RemoveDeadGoombas();
void RemoveDeadKoopas();

void CommitDestructions() {
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
			//gClass->stopAnimators();
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

#endif _GAMEDESTRUCTIONMANAGER_H_
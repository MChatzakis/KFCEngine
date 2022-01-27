#ifndef _GAMEDESTRUCTIONMANAGER_H_
#define _GAMEDESTRUCTIONMANAGER_H_

#include "../engine/DestructionManager.h"

void CommitDestructions() {
	//destroy goombas
	std::list<Sprite*>gs = GoombaHolder::GetSingleton().getGoombasSprites();
	for (Sprite* g : gs) {
		if (!g->IsAlive()) {
			//the sprite is early destroyed in the action func of collision checker
			//SpriteManager::GetSingleton().Remove(g);
			CollisionChecker::GetSingleton().cancelAllTuplesOf(g);
			GoombaHolder::GetSingleton().deleteGoombaSprite(g);
		}
	}

	//DestructionManager::Get().Commit();
}

#endif _GAMEDESTRUCTIONMANAGER_H_
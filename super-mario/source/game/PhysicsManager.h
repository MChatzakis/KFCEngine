#ifndef _PHYSICSMANAGER_H_
#define _PHYSICSMANAGER_H_

#include "../engine/SpriteManager.h"

void Gravity();

void Physics() {
	Gravity();
}


void Gravity() {
	std::list<Sprite*>activeSrpites = SpriteManager::GetSingleton().GetDisplayList();
	for (auto currSprite : activeSrpites) {
		if (currSprite->GetGravityHandler().GetGravityAddicted() && currSprite->GetGravityHandler().IsFalling() && currSprite->GetStateId() != "JUMP") {
			//peftei
			currSprite->Move(0, 1);
		}
	}

}


#endif _PHYSICSMANAGER_H_
#ifndef _PHYSICSMANAGER_H_
#define _PHYSICSMANAGER_H_

#include "../engine/SpriteManager.h"

#define SPRITE_FALLING (currSprite->GetStateId() == "falling_right" || currSprite->GetStateId() == "falling_left")
#define SPRITE_JUMPING (currSprite->GetStateId() == "jumping_vertical_right" || currSprite->GetStateId() == "jumping_vertical_left")

#define GRAVITY_FORCE 1

void Gravity();
void Physics();

void Physics() {
	Gravity();
}


void Gravity() {
	std::list<Sprite*>activeSrpites = SpriteManager::GetSingleton().GetDisplayList();
	for (auto currSprite : activeSrpites) {
		if (!SPRITE_JUMPING && ((currSprite->GetGravityHandler().GetGravityAddicted() && currSprite->GetGravityHandler().IsFalling()))) {
			//peftei

			/*if (currSprite->GetTypeId() == "walking_right") {
				currSprite->SetStateId("falling_right");
			}
			else {
				currSprite->SetStateId("falling_left");
			}*/


			currSprite->Move(0, GRAVITY_FORCE);
		}
	}

}


#endif _PHYSICSMANAGER_H_
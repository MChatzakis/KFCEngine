#ifndef _PHYSICSMANAGER_H_
#define _PHYSICSMANAGER_H_

#include "../engine/SpriteManager.h"

#define SPRITE_FALLING (currSprite->GetStateId() == "falling_right" || currSprite->GetStateId() == "falling_left")
#define SPRITE_JUMPING (currSprite->GetStateId() == "jumping_vertical_right" || currSprite->GetStateId() == "jumping_vertical_left" || currSprite->GetStateId() == "jumping_left" || currSprite->GetStateId() == "jumping_right")
//#define SPRITE_WALKING (currSprite->GetStateId() == "walking_right" || currSprite->GetStateId() == "walking_left")
//#define SPRITE_RUNNING (currSprite->GetStateId() == "running_right" || currSprite->GetStateId() == "running_left")

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

			std::string id = currSprite->GetStateId();
			if (id == "walking_right" || id == "running_right" || id == "idle_right") {
				currSprite->SetStateId("falling_right");
			}
			else if (id == "walking_left" || id == "running_left" || id == "idle_left") {
				currSprite->SetStateId("falling_left");
			}


			currSprite->Move(0, GRAVITY_FORCE);
		}
	}

}


#endif _PHYSICSMANAGER_H_
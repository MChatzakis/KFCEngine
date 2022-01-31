#include "PhysicsManager.h"

void Physics() {
	Gravity();
}


void Gravity() {
	std::list<Sprite*>activeSrpites = SpriteManager::GetSingleton().GetDisplayList();
	for (auto currSprite : activeSrpites) {
		if (!SPRITE_JUMPING && !SPRITE_BOUNCING && ((currSprite->GetGravityHandler().GetGravityAddicted() && currSprite->GetGravityHandler().IsFalling()))) {
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
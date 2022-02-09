#include "./PhysicsManager.h"
#include "./GameVars.h"
#include "./Mario.h"


void Physics() {
	Gravity();
}


void Gravity() {
	std::list<Sprite*>activeSrpites = SpriteManager::GetSingleton().GetDisplayList();
	for (auto currSprite : activeSrpites) {
		if (!SPRITE_JUMPING && !SPRITE_BOUNCING && ((currSprite->GetGravityHandler().GetGravityAddicted() && currSprite->GetGravityHandler().IsFalling()))) {
			//peftei
			//int gravityForce = GRAVITY_FORCE + 1;
			int dx = 0;
			std::string id = currSprite->GetStateId();
			if (id == "walking_right" || id == "running_right" || id == "idle_right") { //animators have been already stopped from 
				currSprite->SetStateId("falling_right");
				currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);
				
			}
			else if (id == "walking_left" || id == "running_left" || id == "idle_left") {
				currSprite->SetStateId("falling_left");
				currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);
				
			}

			/*if (id == "running_right") {
				dx = 1;
			}
			else if(id ==  "running_left"){
				dx = -1;
			}*/

			currSprite->Move(0, GRAVITY_FORCE);
		}
	}

}
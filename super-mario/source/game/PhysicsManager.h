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


#endif _PHYSICSMANAGER_H_
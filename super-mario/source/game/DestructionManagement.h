#ifndef _DESTRUCTIONMANAGEMENT_H_
#define _DESTRUCTIONMANAGEMENT_H_

#include "./GameVars.h"
#include "../engine/DestructionManager.h"
#include "Goomba.h"
#include "../engine/CollisionChecker.h"
#include "Koopa.h"
#include "Mario.h"

void CommitDestructions();
void RemoveDeadGoombas();
void RemoveDeadKoopas();
void RemoveRetrievedCoins();
void ValidateSpritePositions();


#endif _DESTRUCTIONMANAGEMENT_H_

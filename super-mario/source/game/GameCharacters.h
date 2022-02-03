#ifndef _GAMECHARACTERS_H_
#define _GAMECHARACTERS_H_

#include "./GameVars.h"

#include "../utils/Utils.h"

#include "./Mario.h"
#include "./Goomba.h"
#include "./Koopa.h"
#include "./Coin.h"

#include "../engine/CollisionChecker.h"

class CharacterLoader {
public:
	static void loadMario();
	static void loadGoombas();
	static void loadKoopas();
	static void loadCharacters();
	static void loadPowerups();

	static void createCollisionTuples();
};


bool isMarioAbove(Sprite* mario, Sprite* enemy);
void marioGoombaCollision(Sprite* mario, Sprite* goomba);
void marioKoopaCollision(Sprite* mario, Sprite* koopa);
void marioCoinCollision(Sprite* mario, Sprite* coin);


#endif _GAMECHARACTERS_H_
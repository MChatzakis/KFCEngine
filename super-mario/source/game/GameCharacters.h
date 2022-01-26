#ifndef _GAMECHARACTERS_H_
#define _GAMECHARACTERS_H_

#include "./Mario.h"
#include "./Goomba.h"
#include "./Koopa.h"

class CharacterLoader {
public:
	static void loadMario();
	static void loadGoombas();
	static void loadKoopas();

	static void loadCharacters();
};

void CharacterLoader::loadMario() {
	Mario::GetSingleton().initialize();
}

void CharacterLoader::loadGoombas() {
	std::list<Point>gPos = { Point{ 10,300 }, Point{ 500,300 } };

	GoombaHolder::GetSingleton().initialize(gPos);
}

void CharacterLoader::loadKoopas() {
	std::list<Point>kPos = { Point{ 550,200 } };

	KoopaHolder::GetSingleton().initialize(kPos);
}

void CharacterLoader::loadCharacters() {
	loadKoopas();
	loadGoombas();
	loadMario();
}

#endif _GAMECHARACTERS_H_
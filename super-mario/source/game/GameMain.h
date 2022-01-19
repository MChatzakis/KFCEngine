#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "./GameVars.h"

#include "./AllegroInitializer.h"
#include "./VariableInitializer.h"

#include "./MapLoader.h"
#include "./AnimationLoader.h"

#include "./SoundPlayer.h"

#include "./GameFunctions.h"

void Initialise() {
	VariableInitializer::initializeVariables();
	AllegroInitializer::initializeAllegro();
}

void Load() {
	MapLoader::loadMap();
	AnimationLoader::loadAnimations();
	SoundPlayer::loadSounds();
}

void Clear() {
	al_destroy_display(display);
	al_destroy_bitmap((ALLEGRO_BITMAP*)tileSet);
	al_destroy_event_queue(queue);
}

void Run() {
	setGameActions();
	game->MainLoop();
}

void GameMain() {
	Initialise();
	Load();
	Run();
	Clear();
}

#endif _GAMEMAIN_H_
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "./GameVars.h"

#include "./AllegroInitializer.h"
#include "./VariableInitializer.h"

#include "./MapLoader.h"
#include "./AnimationLoader.h"

#include "./GameFunctions.h"

void Initialise() {
	VariableInitializer::initializeVariables();
	AllegroInitializer::initializeAllegro();
}

void Load() {
	MapLoader::loadMap();
	AnimationLoader::loadAnimations();
	SoundsManager::GetSingleton().LoadSounds("resources/Sounds/sounds-config.json", getSoundsDataParser);
	SoundsManager::GetSingleton().PrintSoundsList();
}

void Clear() {
	al_destroy_display(display);
	al_destroy_bitmap((ALLEGRO_BITMAP*)tileSet);
	al_destroy_event_queue(queue);
}

void Run() {
	setGameActions();
	SoundsManager::GetSingleton().PlaySound("main_sound");
	game->MainLoop();
}

void GameMain() {
	Initialise();
	Load();
	Run();
	Clear();
}

#endif _GAMEMAIN_H_
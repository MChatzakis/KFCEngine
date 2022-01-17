#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "./GameVars.h"

#include "./AllegroInitializer.h"
#include "./VariableInitializer.h"

#include "./MapLoader.h"

#include "./GameFunctions.h"

void Initialise() {
	initializeVariables();
	initializeAllegro();
}

void Load() {
	loadMap();
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
	//AnimationLoader::loadAnimations();
	Run();
	Clear();
}

#endif _GAMEMAIN_H_
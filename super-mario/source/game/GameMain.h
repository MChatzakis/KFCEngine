#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "./GameVars.h"

#include "./AllegroInitializer.h"
#include "./VariableInitializer.h"

#include "./MapLoader.h"
#include "./AnimationLoader.h"

#include "./SoundPlayer.h"

#include "./GameFunctions.h"
#include "./GameCharacters.h"

#include "../engine/BoundingArea.h"
#include "../engine/BoundingCircle.h"

void Initialise();
void Load();
void Clear();
void Run();
void GameMain();

void Initialise() {
	/* //clean after testing
	BoundingArea* circle = new BoundingCircle(10, 10, 5);
	BoundingArea* box = new BoundingBox(13, 13, 15, 15);
	std::cout << (int)circle->Intersects(*box) << std::endl;*/

	VariableInitializer::initializeVariables();
	AllegroInitializer::initializeAllegro();

	//showStartingScreen(); //blocking
}

void Load() {
	MapLoader::loadMap();
	AnimationLoader::loadAnimations();
	SoundPlayer::loadSounds();
	CharacterLoader::loadCharacters();
	//SoundPlayer::playSound("main_sound");
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
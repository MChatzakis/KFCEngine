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
#include "./TopTexts.h"
#include "./ExtraScreens.h"

#include "../engine/BoundingArea.h"
#include "../engine/BoundingCircle.h"

void Initialise();
void Load();
void Clear();
void Run();
void GameMain();

void Initialise() {
	VariableInitializer::initializeVariables();
	AllegroInitializer::initializeAllegro();
	
	TopTexts::GetSingleton().Initialize(FONT_PATH, FONT_SIZE);
}

void Load() {
	MapLoader::loadMap();
	AnimationLoader::loadAnimations();
	SoundPlayer::loadSounds();
	CharacterLoader::loadCharacters();
}

void Clear() {
	al_destroy_display(display);
	al_destroy_bitmap((ALLEGRO_BITMAP*)tileSet);
	al_destroy_event_queue(queue);
}

void Run() {
	
	//SoundPlayer::playSound("main_sound");
	ExtraScreens::GetSingleton().DispScreen(STARTING_SCREEN_PATH);

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
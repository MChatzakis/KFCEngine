#include "GameMain.h"

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
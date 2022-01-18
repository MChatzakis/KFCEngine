#include "./App.h"

App::App(Game& _game) { game = _game; }

void App::Main(void) {
	Initialise();
	Load();
	Run();
	Clear();
}

Game& App::GetGame(void) { return game; }

const Game& App::GetGame(void) const { return game; }

void App::SetGame(Game& _game) { game = _game; }
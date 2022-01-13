#ifndef _APP_H_
#define _APP_H_

#include "./Game.h"

class App {
protected:
	Game game;
public:
	App(Game& _game) { game = _game; }
	virtual void Initialise(void) = 0;
	virtual void Load(void) = 0;
	virtual void Run(void) { game.MainLoop(); }
	virtual void RunIteration(void)
	{
		game.MainLoopIteration();
	}
	Game& GetGame(void) { return game; }
	const Game& GetGame(void) const { return game; }
	void SetGame(Game& _game) { game = _game; }
	virtual void Clear(void) = 0;
	void Main(void) {
		Initialise();
		Load();
		Run();
		Clear();
	}
};



#endif _APP_H_
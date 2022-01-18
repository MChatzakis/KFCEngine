#ifndef _APP_H_
#define _APP_H_

#include "./Game.h"

class App {
protected:
	Game game;
public:
	App(Game& _game);
	virtual void Initialise(void) = 0;
	virtual void Load(void) = 0;
	virtual void Run(void) { game.MainLoop(); }
	virtual void RunIteration(void)
	{
		game.MainLoopIteration();
	}
	Game& GetGame(void);
	const Game& GetGame(void) const;
	void SetGame(Game& _game);
	virtual void Clear(void) = 0;
	void Main(void);
};



#endif _APP_H_
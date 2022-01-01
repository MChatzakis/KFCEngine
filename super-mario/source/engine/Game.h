#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <functional>

class Game { // app::Game namespace, the mother application
public:
	using Action = std::function<void(void)>;
	using Pred = std::function<bool(void)>;
private:
	Action render, anim, input, ai, physics, destruct, collisions, user;
	Pred done;
	void Invoke(const Action& f) {
		if (!f) {
			std::cout << "Invoke: Could not map a function." << std::endl;
			exit(-1);
		}
		f();
	}
public:
	Game() {};

	//Setters
	void SetRender(const Action& f) { render = f; }
	void SetProgressAnimations(const Action& f) { anim = f; }
	void SetInput(const Action& f) { input = f; }
	void SetAI(const Action& f) { ai = f; }
	void SetPhysics(const Action& f) { physics = f; }
	void SetDestructions(const Action& f) { destruct = f; }
	void SetCollisionChecking(const Action& f) { collisions = f; }
	void SetUserCode(const Action& f) { user = f; }
	void SetIsFinished(const Pred& f) { done = f; }

	//Invokes
	void Render(void) { Invoke(render); }
	void ProgressAnimations(void) { Invoke(anim); }
	void Input(void) { Invoke(input); }
	void AI(void) { Invoke(ai); }
	void Physics(void) { Invoke(physics); }
	void CollisionChecking(void) { Invoke(collisions); }
	void CommitDestructions(void) { Invoke(destruct); }
	void UserCode(void) { Invoke(user); }
	bool IsFinished(void) const {
		if (done) {
			return done();
		}
		return false;
	}

	void MainLoop(void);
	void MainLoopIteration(void);
};

class App {
protected:
	Game game;
public:
	virtual void Initialise(void) = 0;
	virtual void Load(void) = 0;
	virtual void Run(void) { game.MainLoop(); }
	virtual void RunIteration(void)
	{
		game.MainLoopIteration();
	}
	Game& GetGame(void) { return game; }
	const Game& GetGame(void) const { return game; }
	virtual void Clear(void) = 0;
	void Main(void) {
		Initialise();
		Load();
		Run();
		Clear();
	}
};


void Game::MainLoop(void) {
	while (!IsFinished()) //todo
		MainLoopIteration();
}

void Game::MainLoopIteration(void) {
	Render();
	Input();
	ProgressAnimations();
	AI();
	Physics();
	CollisionChecking();
	UserCode(); // hook for custom code at end
	CommitDestructions();
}

#endif _GAME_H_

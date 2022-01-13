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

	void Invoke(const Action& f);
public:
	Game();

	//Setters
	void SetRender(const Action& f);
	void SetProgressAnimations(const Action& f);
	void SetInput(const Action& f);
	void SetAI(const Action& f);
	void SetPhysics(const Action& f);
	void SetDestructions(const Action& f);
	void SetCollisionChecking(const Action& f);
	void SetUserCode(const Action& f);
	void SetIsFinished(const Pred& f);

	//Invokes
	void Render(void);
	void ProgressAnimations(void);
	void Input(void);
	void AI(void);
	void Physics(void);
	void CollisionChecking(void);
	void CommitDestructions(void);
	void UserCode(void);
	bool IsFinished(void) const;

	void MainLoop(void);
	void MainLoopIteration(void);
};

void Game::Invoke(const Action& f) {
	if (!f) {
		std::cout << "Invoke: Could not map a function." << std::endl;
		exit(-1);
	}
	f();
}

Game::Game() {};

void  Game::SetRender(const Action& f) { render = f; }
void  Game::SetProgressAnimations(const Action& f) { anim = f; }
void  Game::SetInput(const Action& f) { input = f; }
void  Game::SetAI(const Action& f) { ai = f; }
void  Game::SetPhysics(const Action& f) { physics = f; }
void  Game::SetDestructions(const Action& f) { destruct = f; }
void  Game::SetCollisionChecking(const Action& f) { collisions = f; }
void  Game::SetUserCode(const Action& f) { user = f; }
void  Game::SetIsFinished(const Pred& f) { done = f; }

//Invokes
void Game::Render(void) { Invoke(render); }
void Game::ProgressAnimations(void) { Invoke(anim); }
void Game::Input(void) { Invoke(input); }
void Game::AI(void) { Invoke(ai); }
void Game::Physics(void) { Invoke(physics); }
void Game::CollisionChecking(void) { Invoke(collisions); }
void Game::CommitDestructions(void) { Invoke(destruct); }
void Game::UserCode(void) { Invoke(user); }
bool Game::IsFinished(void) const {
	if (done) {
		return done();
	}
	return false;
}

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

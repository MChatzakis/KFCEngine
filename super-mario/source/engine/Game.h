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


#endif _GAME_H_

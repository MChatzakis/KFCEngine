#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <functional>

#include "./FPSCalculator.h"

class Game { // app::Game namespace, the mother application
public:
	using Action = std::function<void(void)>;
	using Pred = std::function<bool(void)>;
private:
	Action render, anim, input, ai, physics, destruct, collisions, user;
	Pred done;

	Action	pauseResume;
	bool		isPaused = false;
	uint64_t	pauseTime = 0;

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
	void SetOnPauseResume(const Action& f);

	//Pause functionality
	void Pause(uint64_t t);
	void Resume(void);
	bool IsPaused(void) const;
	uint64_t GetPauseTime(void) const;

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

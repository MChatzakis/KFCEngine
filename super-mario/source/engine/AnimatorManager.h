#ifndef _ANIMATIONMANAGER_H_
#define _ANIMATIONMANAGER_H_

#include <iostream>
#include <set>

#include "./Animator.h"

class AnimatorManager {
private:
	std::set<Animator*> running, suspended;
	static AnimatorManager singleton;
	AnimatorManager(void) = default;
	AnimatorManager(const AnimatorManager&) = delete;
	AnimatorManager(AnimatorManager&&) = delete;
public:
	void Register(Animator* a);
	void Cancel(Animator* a);
	void MarkAsRunning(Animator* a);
	void MarkAsSuspended(Animator* a);
	void Progress(timestamp_t currTime);

	static auto GetSingleton(void) -> AnimatorManager& { return singleton; }
	static auto GetSingletonConst(void) -> const AnimatorManager& { return singleton; }
};

void
AnimatorManager::Register(Animator* a)
{
	assert(a->HasFinished()); suspended.insert(a);
}

void
AnimatorManager::Cancel(Animator* a)
{
	assert(a->HasFinished()); suspended.erase(a);
}

void
AnimatorManager::MarkAsRunning(Animator* a)
{
	assert(!a->HasFinished()); suspended.erase(a); running.insert(a);
}

void
AnimatorManager::MarkAsSuspended(Animator* a)
{
	assert(a->HasFinished()); running.erase(a); suspended.insert(a);
}

void
AnimatorManager::Progress(timestamp_t currTime) {
	auto copied(running);
	for (auto* a : copied)
		a->Progress(currTime);
}

#endif _ANIMATIONMANAGER_H_
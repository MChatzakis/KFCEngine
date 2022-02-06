#ifndef _ANIMATORNMANAGER_H_
#define _ANIMATORNMANAGER_H_

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
	void TimeShift(unsigned dt);

	static auto GetSingleton(void) -> AnimatorManager& { return singleton; }
	static auto GetSingletonConst(void) -> const AnimatorManager& { return singleton; }
};


#endif _ANIMATORNMANAGER_H_
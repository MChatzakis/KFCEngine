#include "./AnimatorManager.h"

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
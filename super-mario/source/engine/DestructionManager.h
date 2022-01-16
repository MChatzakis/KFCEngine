#ifndef _DESTRUCTIONMANAGER_H_
#define _DESTRUCTIONMANAGER_H_

#include <iostream>
#include <list>
#include <assert.h>

class LatelyDestroyable;
class DestructionManager {
	std::list<LatelyDestroyable*> dead;
	static DestructionManager singleton;
public:
	void Register(LatelyDestroyable* d);
	void Commit(void);
	static auto Get(void) -> DestructionManager& { return singleton; }
};

void DestructionManager::Register(LatelyDestroyable* d) {
	assert(!d->IsAlive());
	dead.push_back(d);
}
void DestructionManager::Commit(void) {
	for (auto* d : dead)
		d->Delete();
	dead.clear();
}

class LatelyDestroyable {
protected:
	friend class DestructionManager;
	bool alive = true;
	bool dying = false;
	virtual ~LatelyDestroyable() { assert(dying); }
	void Delete(void);
public:
	bool IsAlive(void) const;
	void Destroy(void);
	LatelyDestroyable(void) = default;
};

bool
LatelyDestroyable::IsAlive(void) const { return alive; }

void
LatelyDestroyable::Destroy(void) {
	if (alive) {
		alive = false;
		DestructionManager::Get().Register(this);
	}
}

void
LatelyDestroyable::Delete(void)
{
	assert(!dying); dying = true; delete this;
}
// may adopt this for animators in case we wish to Destroy() in callbacks
// and do not bother to have deleted pointers being used

/*class Animator : public LatelyDestroyable {
	…
};*/

#endif _DESTRUCTIONMANAGER_H_


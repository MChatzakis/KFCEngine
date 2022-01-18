#include "./DestructionManager.h"

DestructionManager DestructionManager::singleton;
auto DestructionManager::Get(void) -> DestructionManager& { return singleton; }

//Destruction Manager functions

void DestructionManager::Register(LatelyDestroyable* d) {
	assert(!d->IsAlive());
	dead.push_back(d);
}
void DestructionManager::Commit(void) {
	for (auto* d : dead)
		d->Delete();
	dead.clear();
}

//LatelyDestroyable functions

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
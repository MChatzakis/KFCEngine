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
	static auto Get(void)->DestructionManager&;
};

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

//DestructionManager DestructionManager::singleton;
#endif _DESTRUCTIONMANAGER_H_


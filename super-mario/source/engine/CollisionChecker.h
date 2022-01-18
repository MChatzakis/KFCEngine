#ifndef _COLLISIONCHECKER_H_
#define _COLLISIONCHECKER_H_

#include <iostream>
#include <functional>
#include <list>

#include "./General.h"
#include "./Sprite.h"

class CollisionChecker final
{
public:
	using Action = std::function<void(Sprite *s1, Sprite *s2)>;
	static CollisionChecker singleton;

protected:
	using Entry = std::tuple<Sprite *, Sprite *, Action>;
	std::list<Entry> entries;
	auto Find(Sprite *s1, Sprite *s2) -> std::list<Entry>::iterator;

public:
	void Register(Sprite *s1, Sprite *s2, const Action &f);
	void Cancel(Sprite *s1, Sprite *s2);
	void Check(void) const;
	bool In(Sprite* s1, Sprite* s2);
	static auto GetSingleton(void)->CollisionChecker&;
	static auto GetSingletonConst(void) -> const CollisionChecker&;
};

#endif _COLLISIONCHECKER_H_
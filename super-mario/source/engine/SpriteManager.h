#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

#include <iostream>
#include <list>
#include <map>

#include "./Sprite.h"

class SpriteManager final {
public:
	using SpriteList = std::list<Sprite*>;
	using TypeLists = std::map<std::string, SpriteList>;
private:
	SpriteList dpyList;
	TypeLists types;
	static SpriteManager singleton;
public:
	void Add(Sprite* s); // insert by ascending zorder
	void Remove(Sprite* s);
	auto GetDisplayList(void) -> const SpriteList&
	{
		return dpyList;
	}
	auto GetTypeList(const std::string& typeId) -> const SpriteList&
	{
		return types[typeId];
	}
	static auto GetSingleton(void) -> SpriteManager&
	{
		return singleton;
	}
	static auto GetSingletonConst(void) -> const SpriteManager&
	{
		return singleton;
	}
};

#endif _SPRITEMANAGER_H_
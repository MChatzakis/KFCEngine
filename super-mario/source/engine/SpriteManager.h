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

	auto GetDisplayList(void) -> const SpriteList&;
	auto GetTypeList(const std::string& typeId) -> const SpriteList&;
	static auto GetSingleton(void)->SpriteManager&;
	static auto GetSingletonConst(void) -> const SpriteManager&;
};


auto SpriteManager::GetDisplayList(void) -> const SpriteList&
{
	return dpyList;
}

auto SpriteManager::GetTypeList(const std::string& typeId) -> const SpriteList&
{
	return types[typeId];
}

auto SpriteManager::GetSingleton(void) -> SpriteManager&
{
	return singleton;
}

 auto SpriteManager::GetSingletonConst(void) -> const SpriteManager&
{
	return singleton;
}


#endif _SPRITEMANAGER_H_
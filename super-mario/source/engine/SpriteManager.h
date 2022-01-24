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

	void SortSpriteList();

	void CreateTypeList(std::string,std::list<Sprite*>);
	void RemoveList(std::string);

	auto GetDisplayList(void) -> const SpriteList&;
	auto GetTypeList(const std::string& typeId) -> const SpriteList&;
	static auto GetSingleton(void)->SpriteManager&;
	static auto GetSingletonConst(void) -> const SpriteManager&;
};


#endif _SPRITEMANAGER_H_
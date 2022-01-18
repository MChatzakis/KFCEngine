#include "SpriteManager.h"

SpriteManager SpriteManager::singleton;

void SpriteManager::Add(Sprite* s) {
	dpyList.push_back(s);
}

void SpriteManager::Remove(Sprite* s) {
	dpyList.remove(s);
}

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

#include "./SpriteManager.h"

SpriteManager SpriteManager::singleton;

bool compateSpriteZorder(Sprite* s1, Sprite* s2) {
	return s1->GetZorder() < s2->GetZorder();
}

void SpriteManager::SortSpriteList() {
	dpyList.sort(compateSpriteZorder);
}

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

void SpriteManager::CreateTypeList(std::string id, std::list<Sprite*> list) {
	types.insert({ id, list });
}

void SpriteManager::RemoveList(std::string id) {
	types.erase(id);
}
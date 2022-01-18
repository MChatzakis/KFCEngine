#ifndef _SOUNDSMANAGER_H_
#define _SOUNDSMANAGER_H_

#include "General.h"
#include <map>

class Sound {
	std::string id;
	//ALLEGRO_SAMPLE* sample;
	float gain;
	float pan;
	float speed;
	//ALLEGRO_PLAYMODE loop;
	//ALLEGRO_SAMPLE_ID* ret_id;
};

class SoundsManager {
private:
	using SoundList = std::map<std::string, Sound*>;
	SoundList sounds;
	static SoundsManager singleton;
public:
	using Parser = std::function<bool(std::map<std::string, Sound*>& output, const std::string& input)>; //change to list?

	SoundsManager(void);
	~SoundsManager();
	static SoundsManager& GetSingleton();
	static auto Get(void) -> const SoundsManager&;
	const Sound* GetSound(std::string id);
	bool LoadSounds(std::string filename, const SoundsManager::Parser& parser);
	void PlaySound(std::string id); //call al_play_sample
	void CleanUp();
};

SoundsManager::SoundsManager(void) {}

SoundsManager::~SoundsManager() { CleanUp(); }

SoundsManager& SoundsManager::GetSingleton()
{
	return singleton;
}

auto SoundsManager::Get(void) -> const SoundsManager& { return singleton; }

void SoundsManager::PlaySound(std::string id){} //todo

void SoundsManager::CleanUp()
{
	for (auto& i : sounds)
		delete(i.second);
	sounds.clear();
}

const Sound* SoundsManager::GetSound(std::string id) {
	auto i = sounds.find(id);
	return i != sounds.end() ? i->second : nullptr;
}

bool SoundsManager::LoadSounds(std::string filename, const SoundsManager::Parser& parser ) //todo + parsing function
{
	return false;
}

#endif _SOUNDSMANAGER_H_


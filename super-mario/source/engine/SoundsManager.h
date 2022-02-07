#ifndef _SOUNDSMANAGER_H_
#define _SOUNDSMANAGER_H_

//#include "General.h"
#include <map>
#include <list>
#include <string>
#include <functional>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

struct Sound {
	std::string id;
	ALLEGRO_SAMPLE* sample;
	std::string sample_path;
	float gain;
	float pan;
	float speed;
	ALLEGRO_PLAYMODE loop;
	ALLEGRO_SAMPLE_ID sampleId;

	Sound(std::string _id, ALLEGRO_SAMPLE* _sample, std::string _sample_path, float _gain, float _pan, float _speed, ALLEGRO_PLAYMODE _loop);
	Sound();
	std::string toString();
};

class SoundsManager {
private:
	using SoundList = std::map<std::string, Sound*>;
	SoundList sounds;
	static SoundsManager singleton;
public:
	using Parser = std::function<bool(std::list<Sound>& output, const std::string& input)>;

	SoundsManager(void);
	~SoundsManager();
	static SoundsManager& GetSingleton();
	static auto Get(void) -> const SoundsManager&;
	Sound* GetSound(std::string id);
	void LoadSounds(std::string filename, const SoundsManager::Parser& parser);
	void PlaySound(std::string id);
	void StopSound(std::string id);
	void CleanUp();
	void PrintSoundsList();
};

#endif _SOUNDSMANAGER_H_


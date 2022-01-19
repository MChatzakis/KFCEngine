#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

#define SOUNDS_PATH "resources/Sounds/sounds-config.json"

class SoundPlayer {
public:
	static void loadSounds() {
		SoundsManager::GetSingleton().LoadSounds(SOUNDS_PATH, getSoundsDataParser);
		//SoundsManager::GetSingleton().PrintSoundsList();
	}

	static void playSound(std::string id) {
		SoundsManager::GetSingleton().PlaySound(id); //magas
	}
};


#endif _SOUNDPLAYER_H_
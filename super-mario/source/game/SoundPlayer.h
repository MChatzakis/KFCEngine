#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

#include <string>
#include "../engine/SoundsManager.h"
#include "../utils/Utils.h"

#define SOUNDS_PATH "resources/Sounds/sounds-config.json"

class SoundPlayer {
public:
	static void loadSounds();
	static void playSound(std::string id);
	static void stopSound(std::string id);
};


#endif _SOUNDPLAYER_H_
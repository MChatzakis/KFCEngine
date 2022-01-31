#include "SoundPlayer.h"

void SoundPlayer::loadSounds() {
	SoundsManager::GetSingleton().LoadSounds(SOUNDS_PATH, getSoundsDataParser);
	//SoundsManager::GetSingleton().PrintSoundsList();
}

void SoundPlayer::playSound(std::string id) {
	SoundsManager::GetSingleton().PlaySound(id); //magas
}
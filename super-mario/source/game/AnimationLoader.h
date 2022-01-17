#ifndef _ANIMATIONLOADER_H_
#define _ANIMATIONLOADER_H_

#include <iostream>
#include <string>

#include "../utils/Utils.h"

#include "../engine/BitmapLoader.h"
#include "../engine/AnimationFilmHolder.h"

class AnimationLoader {

public:
	static void loadAnimations() {
		//using Parser = std::function<bool(std::list<AnimationFilm::Data>& output, const std::string& input)>;
		AnimationFilmHolder::GetSingleton().Load("../resources/characters/mario.json", (const AnimationFilmHolder::Parser &) getAnimationFilmDataParser);
		//AnimationFilmHolder::GetSingleton().Load("resources/characters/mario.json", (const AnimationFilmHolder::EntryParser &) getAnimationFilmDataEntryParser);
	}

};

#endif _ANIMATIONLOADER_H_
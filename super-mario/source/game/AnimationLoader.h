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
		AnimationFilmHolder::GetSingleton().Load(MARIO_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser &) getAnimationFilmDataParser);
		AnimationFilmHolder::GetSingleton().Load(KOOPA_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser &) getAnimationFilmDataParser);
		AnimationFilmHolder::GetSingleton().Load(GOOMBA_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser &) getAnimationFilmDataParser);
		
		AnimationFilmHolder::GetSingleton().printAnimationMap();
	}

};

#endif _ANIMATIONLOADER_H_
#include "AnimationLoader.h"

void AnimationLoader::loadAnimations() {
	AnimationFilmHolder::GetSingleton().Load(MARIO_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser&)getAnimationFilmDataParser);
	AnimationFilmHolder::GetSingleton().Load(KOOPA_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser&)getAnimationFilmDataParser);
	AnimationFilmHolder::GetSingleton().Load(GOOMBA_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser&)getAnimationFilmDataParser);
	AnimationFilmHolder::GetSingleton().Load(POWERUP_ANIMATIONS_PATH, (const AnimationFilmHolder::Parser&)getAnimationFilmDataParser);

	AnimationFilmHolder::GetSingleton().printAnimationMap();
}
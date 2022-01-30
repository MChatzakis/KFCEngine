#ifndef _ANIMATIONMANAGER_H_
#define _ANIMATIONMANAGER_H_

#include "../engine/AnimatorManager.h"
#include "../engine/Timing.h"

void ProgressAnimations() {
	AnimatorManager::GetSingleton().Progress(CurrTime());
}

#endif _ANIMATIONMANAGER_H_

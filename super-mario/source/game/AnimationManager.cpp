#include "AnimationManager.h"

void ProgressAnimations() {
	AnimatorManager::GetSingleton().Progress(CurrTime());
}
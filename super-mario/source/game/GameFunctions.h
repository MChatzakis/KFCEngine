#ifndef _GAMEFUNCTIONS_H_
#define _GAMEFUNCTIONS_H_

#include "./GameVars.h"
#include "./ExtraScreens.h"

#include "./InputManager.h"
#include "./AIManager.h"
#include "./RenderingManager.h"
#include "./UserCodeManager.h"
#include "./PhysicsManager.h"
#include "./AnimationManager.h"
#include "./CollisionManager.h"
#include "./DestructionManagement.h"

bool isFinished();
void setGameActions();
void InstallPauseResumeHandler(Game& game);
uint64_t GetGameTime();

#endif _GAMEFUNCTIONS_H_

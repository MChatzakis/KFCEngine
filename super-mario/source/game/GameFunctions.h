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
#include "./DestructionManager.h"

bool isFinished() {

	if (Mario::GetSingleton().getTotalLifes() == 0) {
		ExtraScreens::GetSingleton().DispScreen(DEATH_SCREEN_PATH);
		return true;
	}

	return false;
}

void setGameActions() {
	game->SetRender(Render);
	game->SetInput(Input);
	game->SetProgressAnimations(ProgressAnimations);
	game->SetAI(AI);
	game->SetPhysics(Physics);
	game->SetCollisionChecking(CollisionChecking);
	game->SetUserCode(UserCode);
	game->SetDestructions(CommitDestructions);
	game->SetIsFinished(isFinished);
}

#endif _GAMEFUNCTIONS_H_

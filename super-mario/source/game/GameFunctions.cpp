#include "./GameFunctions.h"
#include "./SoundPlayer.h"

bool isFinished() {



	if (GAME_HAS_ENDED == 1) {
		SoundPlayer::playSound("gameover");
		
		ExtraScreens::GetSingleton().DispScreen(DEATH_SCREEN_PATH);
		
		return true;
	}
	else if (GAME_HAS_ENDED == 2) {
		ExtraScreens::GetSingleton().DispScreen(WIN_SCREEN_PATH);
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
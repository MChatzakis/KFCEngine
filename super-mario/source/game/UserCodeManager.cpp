#include "UserCodeManager.h"
#include "SoundPlayer.h"

void UserCode() {
	if (Mario::GetSingleton().hasMarioWon())
		return;
	// hook for custom code at end
	JumpPatch();
	Mario::GetSingleton().SecretLevel(gameMap);
	
	EvaluateWin();
}



void JumpPatch() {
	//fix problem with stop animators on jump (animation delay but state changes immediately)
	Sprite* marioSprite = Mario::GetSingleton().GetCurrSprite();
	if (gameMap->GetGrid()->IsOnSolidGround(marioSprite->GetBox())) {
		if (marioSprite->GetStateId() == "falling_right") {
			//std::cout << "here we go again" << std::endl;
			marioSprite->SetStateId("idle_right");
			marioSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
		}
		else if (marioSprite->GetStateId() == "falling_left") {
			marioSprite->SetStateId("idle_left");
			marioSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);
		}
	}
}


void EvaluateWin() {
	Point marioPosition = Mario::GetSingleton().GetCurrSprite()->GetPosition();
	if (marioPosition.x >= WIN_TILE_POINT.x && marioPosition.x <= WIN_TILE_POINT.x + 3) { //on win tile
		SoundPlayer::stopSound("main_sound");
		SoundPlayer::playSound("stage_clear");
		if (marioPosition.y == WIN_TILE_POINT.y)
			Mario::GetSingleton().Win();
		else
			Mario::GetSingleton().DropFlag();
	}
}
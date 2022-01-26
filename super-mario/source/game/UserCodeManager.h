#ifndef _USERCODEMANAGER_H_
#define _USERCODEMANAGER_H_

#include"./Mario.h"

void UserCode() {
	// hook for custom code at end
	//fix problem with stop animators on jump (animation delay but state changes immediately)
	Sprite* marioSprite = Mario::GetSingleton().GetCurrSprite();
	if(gameMap->GetGrid()->IsOnSolidGround(marioSprite->GetBox())) {
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

#endif _USERCODEMANAGER_H_
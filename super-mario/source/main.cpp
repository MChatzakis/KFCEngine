#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*
//TODO
//Engine
1) SpriteManager -> store sprites
2) Animators Package -> Add animators for the rest of the animations //normal i guess
3) Check FilterMotion -> Fanou
4) BoundingAreas package-> Complete Circle-Box and Circle-Polygon intersect and test //hard ->Konto
5) TileUtilities/TileLayer -> Give empty indices as argument(we have engine)-> give to tileLayer constructior the indices -> Fanou

//Game
1) CollisionChecker-> Add pairs of sprites //easy 
2) Sprites-> Create BoundingAreas //normal
3) Gravity-> Add gravity (Add onStopFalling/OnStartFalling) //normal - hard -> [MANOS]
4) Mario -> sprite, animators, functions //easy-normal -> OLOI
5) Enemies -> same for troopas koopas kai loipes mlks
6) Mario-> Scroll based on mario position //normal
7) Game-> Complete Game Functions //easy but last step
8) AI -> Movement //normal-hard?
9) Mario-> New animation for Jump && Move (press w + d) //normal -> [MANOS]

//ADVICES
1) Animators-> Always initialize animators actions
Constructor => Registers in AnimatorManager
OnStart => MarkAsRunning
onFinish=> MarkAsSuspended
onAction=> Do action
Progress=> Do animation
2) AnimatorManager-> Calls progress for a list of animators
3) AnimationFilmHolder-> If you need animation film get it from this class
4) DestructionManager-> Never delete a sprite that dies. Put it and its animators to Destruction Manager List
Example: When sprite dies do Sprite.destroy() => Then DestructionManager does Commit() => Commit iterates list
and does sprite.delete()
5) Animations-> If game pauses, keep pause time and add it with TimeShift(offset) when the game resumes




*/

int main() {
	GameMain();
}
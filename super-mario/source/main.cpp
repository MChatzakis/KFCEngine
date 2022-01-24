#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*
	//TODO
//Engine
1) SpriteManager -> store sprites and extend add, remove to add/remove from typelist too //very easy
2) Animators Package -> Add animators for the rest of the animations //normal i guess
3) LatelyDestroyable -> make animators and sprites lately destroyable subclasses
						and add them to Destruction Manager list when they die //easy-normal
4) BoundingAreas package-> Complete Circle-Box and Circle-Polygon intersect and test //hard
5) Clipper-> Show sprites via clipper which is already implemented (see Sprite::Display and lec 12)
			 The only thing we may need is to give Mario/Sprites  position in pixels //easy
6) Animator -> Notify Function need a little extension (see lec 11), register/cancel on constructor/destructor //easy
7) Sprite-> Extend move to check if motionquantizer is used //very easy
8)  TileUtilities/TileLayer -> Give empty indices as argument(we have engine)

//Game
1) CollisionChecker-> Add pairs of sprites //easy
2) Sprites-> Create BoundingAreas //normal
3) Gravity-> Add gravity (Add onStopFalling/OnStartFalling) //normal - hard
4) Mario -> sprite, animators, functions //easy-normal
5) Enemies -> same for troopas koopas kai loipes mlks
6) Mario-> Scroll based on mario position //normal
7) Game-> Complete Game Functions //easy but last step
8) AI -> Movement //normal-hard?
9) Mario-> Maybe moving path animation for Jump && Move (press w + d) //normal
10)Clipper-> Give Clipper the View Window //super easy

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
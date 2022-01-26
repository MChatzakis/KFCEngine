#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*
//TODO
//Engine
2) Animators Package -> Add animators for the rest of the animations //normal i guess
4) BoundingAreas package-> Complete Circle-Box and Circle-Polygon intersect and test //hard ->Konto

//Game
1) CollisionChecker-> Add pairs of sprites //easy 
2) Sprites-> Create BoundingAreas //normal
4) Mario -> sprite, animators, functions //easy-normal -> OLOI on process
6) Mario-> Scroll based on mario position //normal
7) Game-> Complete Game Functions //easy but last step
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

--------------- CURRENT_TODO ---------------
1. Implement Jump for mario [FANOU, +together]
2. Add the rest of the animations for koopas goombas [MANOS]
3. View Window Alignment [FANOU, +together]
4. Implement MovingPath Animator [MANOS]
5. Implement FlashAnimator [KONTO]
6. Implement FrameList Animator [KONTO]
7. Collisions [MANOS]
8. Ta text tou mario panw panw (opt) -- opoios exei orexi
9. Implement Pause -- opoios exei orexi
10. Implement Item logic (coins, powerups)
11. Finish bareas [KONTO]
--
12. Start implementing game features (mario death, win messages, death screen)
13. Starting screen, death screen, win sreen, checkpoints
14. Need to make fixes-cleanups 
15. Split to CPPs ( :( ) 
--
16. Implement Scroll Animator
17. Enemy Positions, mario input, confs -> from json

*/

int main() {
	GameMain();
}
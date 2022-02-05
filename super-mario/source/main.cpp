#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*
1) Add shell animations and AI for koopas [Manos] --> DONE
2) Fine tune the mario delay, coin and enemy positions (though json) [Konto]
3) Stop jump animator on collisions [Fanou]
4) Add mario death animation [Manos] --> DONE
5) Pipes [all together at the end] --> DONE Functionality, must add sprites and fix coordinates!
6) Pause implemenetion [Fanou]
7) Timer at the top [Manos] --> DONE
8) Add remanining sounds [Konto] 
---------------
9) Add super mario, powerups

ChangeLog:
1) Patched scrolling to look more smooth
2) Added coins
3) Added enemy death animation
4) Fine tuned enemy positions, delays etc.
5) Added shell transformation to turtles
6) Added relocation to secret level
7) Added pipe functionality
8) Added top timer
9) Added Mario Death Animation
10) Added collisions between koopas and goombas

*/
int main() {
	GameMain();
}
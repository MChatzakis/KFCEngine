#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*

ChangeLog:
-- Bug Fixes:
1) Made Scrolling smoother
2) Resouce free-ing though commit

-- Improvements:
1) Coins added
2) Goomba and Mario Death animation added
3) Koopa shell transformation added
4) Secret level addition, and animation through pipes
5) Pause implemented
6) Top timer addition
7) Sound enrichement
8) Collisions between Goombas and Koopas
9) (Peripou) Win Animation

-- Changes:
1) Fine tuning on enemy speed, positions etc.

*/
int main() {
	GameMain();
}
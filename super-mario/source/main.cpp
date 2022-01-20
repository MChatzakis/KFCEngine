#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*
	1) Start creating character [manos]
		- Add all sprites to mario class
		- Add all sprites to koppas class
		- Add all sprites to goombas class
	2) Add supermario json [Konto] (+ all other json px items[coins, stars] klp)
	3) Engine: Fix bounding areas package [Manos] [ok]
	4) Read lectures 11,12 to understand better about sprites [all] 1.

	6) Split .h code to cpp [opoios exei orexi (fanou)] -> Engine Done except BoundingArea [ok]
	7) Add FPS calculation code [opoios exei orexi (manos)] -lec 5 6 7?
	8) Pass stis dialexeis mipws exoyme ksexasei kati
	9) Code for view window transitions based on mario 2.
	10) Implement Sprite::CollisionCheck [done], CollisionChecker::In [done], BoundingPolygon::In [done], BoundingPolygon::Intersects(Polygon) [done], BoundingCircle::Intersects(Polygon), BoundingCircle::Intersects(Box) 3.
*/

int main() {
	GameMain();
}
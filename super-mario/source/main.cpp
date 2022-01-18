#include <iostream>
#include <string>

#include "./game/GameMain.h"

/*
	1) Start creating character [manos]
		- Add all sprites to mario class
		- Add all sprites to koppas class
		- Add all sprites to goombas class
	2) Add supermario json [Konto] (+ all other json px items[coins, stars] klp)
	3) Engine: Fix bounding areas package [Manos]
	4) Read lectures 11,12 to understand better about sprites [all]
	5) Sounds [Fanou]
		- Fix a class to load all sounds
		- Sounds.play("coin") -> sound (map<string,sounds>)
	6) Split .h code to cpp [opoios exei orexi (fanou)]
	7) Add FPS calculation code [opoios exei orexi (manos)] -lec 5 6 7?
	8) Pass stis dialexeis mipws exoyme ksexasei kati
	9) Code for view window transitions based on mario
*/

int main() {
	GameMain();
}
# super-mario-csd
This repository contains a complete 2D Game Engine, called KFC Engine. It also contains an implementation of the classic Super Mario Bros - 1985 using the KFC engine.

# KFC Engine Layout
The KFC Engine contains the following packages and classes:

Engine:
* Animation
	* Animations
	* Animators
	* [OtherClasses]
* Game
* BoundingAreas
* Physics
* Sounds
* Sprites
* [OtherClasses]

To display the bitmaps, KFC Engine uses some basic functions of Allegro 5.

# Super Mario Bros
We implemented the classic Super Mario Bros game, created by Nintendo in 1985. The game using the KFC engine for every functionality, while it uses the classic sprites of the game. The implementation can be used as an example case of the KFC engine.

# Development
The engine and the game were developed by Manos Chatzakis, Nikos Fanourakis and Nikos Kontonasios (KFC) for the undergraduate course cs454 - Game Development of Dept. of Computer Science of the University of Crete

# How to Run
The whole project was developed Visual Studio. To run it, you need to import it in Visual Studio and install the following libraries:
* Allegro 5: https://github.com/liballeg/allegro5
* json: https://github.com/nlohmann/json

Then, you can build the project normally.

# References
Game Sounds: https://themushroomkingdom.net/media/smb/wav
Allegro 5: https://liballeg.org/

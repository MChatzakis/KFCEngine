#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "./GameVars.h"

#include "./AllegroInitializer.h"
#include "./VariableInitializer.h"

#include "./MapLoader.h"
#include "./AnimationLoader.h"

#include "./SoundPlayer.h"

#include "./GameFunctions.h"
#include "./GameCharacters.h"
#include "./TopTexts.h"
#include "./ExtraScreens.h"

#include "../engine/BoundingArea.h"
#include "../engine/BoundingCircle.h"

void Initialise();
void Load();
void Clear();
void Run();
void GameMain();

#endif _GAMEMAIN_H_
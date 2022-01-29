#ifndef _AIMANAGER_H_
#define _AIMANAGER_H_

#include "./Goomba.h"
#include "./Koopa.h"

void AI() {
	GoombaHolder::GetSingleton().WalkGoombas();
	KoopaHolder::GetSingleton().WalkKoopas();
}

#endif _AIMANAGER_H_
#ifndef _AIMANAGER_H_
#define _AIMANAGER_H_

#include "./Goomba.h"

void AI() {
	GoombaHolder::GetSingleton().walkGoombas();

	//Mario::GetSingleton().walkRight();
}

#endif _AIMANAGER_H_
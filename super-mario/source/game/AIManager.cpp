#include "AIManager.h"

void AI() {
	GoombaHolder::GetSingleton().WalkGoombas();
	KoopaHolder::GetSingleton().WalkKoopas();
}
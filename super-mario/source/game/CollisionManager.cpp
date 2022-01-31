#include "CollisionManager.h"

void CollisionChecking() {
	//update all bareas
	UpdateBoundingAreas();
	CollisionChecker::GetSingleton().Check();
}

void UpdateBoundingAreas() {
	std::list<Sprite*>activeSprites = SpriteManager::GetSingleton().GetDisplayList();

	for (Sprite* c : activeSprites) {

		//Version 1
		/*int x1 = c->GetPosition().x - c->GetBox().w/2;
		int y1 = c->GetPosition().y + c->GetBox().h/2;

		int x2 = x1 + c->GetBox().w;
		int y2 = y1 + c->GetBox().h;*/

		//Version 2
		int x1 = c->GetBox().x;
		int y1 = c->GetBox().y;

		int x2 = x1 + c->GetBox().w;
		int y2 = y1 + c->GetBox().h;

		BoundingBox box = BoundingBox(x1, y1, x2, y2);
		c->SetBoundingArea(box);
	}

}
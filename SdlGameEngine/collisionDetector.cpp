#include "collisionDetector.h"

CollisionDetector::CollisionDetector(int w, int h, std::vector<std::unique_ptr<IGameObject>>* objects)
{
	this->windowW_ = w;
	this->windowH_ = h;
	this->objects_ = objects;
}

bool CollisionDetector::FindCollisions()
{
	bool collisionDetected = false;
	for (std::vector<std::unique_ptr<IGameObject>>::iterator itA = this->objects_->begin(); itA != this->objects_->end(); itA++)
	{
		ICollideable* collA = null;
		if (!(collA = dynamic_cast<ICollideable*>(itA->get())))
		{
			continue;
		}

		for (std::vector<std::unique_ptr<IGameObject>>::iterator itB = itA + 1; itB != this->objects_->end(); itB++)
		{
			ICollideable* collB = null;
			if (!(collB = dynamic_cast<ICollideable*>(itB->get())))
			{
				continue;
			}

			if (itA->get() == itB->get())
			{
				continue;
			}

			SDL_Rect* a = collA->GetDestination();
			SDL_Rect* b = collB->GetDestination();

			if (((a->x < (b->x + b->w)) && // left face right of rightmost
				 ((a->x + a->w) > b->x) && // right face left of leftmost
				 ((a->y + a->h) > b->y) &&
				 (a->y < (b->y + b->h))))
			{
				collisionDetected = true;
				collA->ResolveCollision(collB);
				collB->ResolveCollision(collA);
			}
		}
	}

	return collisionDetected;
}
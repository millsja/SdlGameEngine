#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <vector>
#include <memory>
#include "iGameObject.h"
#include "iCollideable.h"

class CollisionDetector
{
public:
	CollisionDetector() {}
	CollisionDetector(int w, int h, std::vector<std::unique_ptr<IGameObject>>* objects);
	bool FindCollisions();
	void SetW(int w) { this->windowW_ = w; }
	void SetH(int h) { this->windowH_ = h; }
	void SetObjects(std::vector<std::unique_ptr<IGameObject>>* objects) { this->objects_ = objects; }
private:
	int windowW_;
	int windowH_;
	std::vector<std::unique_ptr<IGameObject>>* objects_;
};

#endif
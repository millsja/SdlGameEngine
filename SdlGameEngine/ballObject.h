#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "iGameObject.h"
#include "iEveryFrame.h"
#include "iCollideable.h"
#include <math.h>
#include "iHasVelocity.h"

class BallObject : public IGameObject, public IEveryFrame, public ICollideable 
{
public:
	BallObject(int textureId, int x, int y, int w, int h, float xVelocity, float yVelocity);
	void SetLocation(int x, int y) { this->dest_.x = x; this->dest_.y = y; }
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	void HandleNewFrame();
private:
	float xCharge_;
	float yCharge_;
	float xVelocity_; // pixel/frame
	float yVelocity_; // pixel/frame
	struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
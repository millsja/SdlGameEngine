#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "iGameObject.h"
#include "iEveryFrame.h"
#include "iCollideable.h"
#include <math.h>
#include "iHasVelocity.h"
#include "iObservableBall.h"
#include "iBallObserver.h"
#include <algorithm>
#include <vector>

class BallObject : public IGameObject, public IEveryFrame, public ICollideable, public IObservableBall
{
public:
	BallObject(int textureId, int x, int y, int w, int h, float xVelocity, float yVelocity, bool accelerate, float maxSpeed);
	void SetLocation(int x, int y) { this->dest_.x = x; this->dest_.y = y; }
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	void HandleNewFrame();
	void AttachObserver(IBallObserver* observer) { this->observers_.push_back(observer); }
	void DetachObserver(IBallObserver* observer) { this->observers_.erase(std::remove(this->observers_.begin(), this->observers_.end(), observer)); };
	void Notify();
private:
	int initialX_;
	int initialY_;
	float maxSpeed_;
	bool accelerate_;
	std::vector<IBallObserver*> observers_;
	float xCharge_;
	float yCharge_;
	float xVelocity_; // pixel/frame
	float yVelocity_; // pixel/frame
	struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
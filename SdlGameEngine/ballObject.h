#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "sdlClient.h"
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
	BallObject(
		SdlClient* sdlClient,
		int textureId,
		int x,
		int y,
		int w,
		int h,
		struct Velocity xVelocity,
		struct Velocity yVelocity,
		bool accelerate,
		float maxSpeed);
	void SetLocation(int x, int y) { this->dest_.x = x; this->dest_.y = y; }
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	void HandleNewFrame();
	void AttachObserver(IBallObserver* observer) { this->observers_.push_back(observer); }
	void DetachObserver(IBallObserver* observer) { this->observers_.erase(std::remove(this->observers_.begin(), this->observers_.end(), observer)); };
	void Notify();
private:
	SdlClient* sdlClient_;
	int initialX_;
	int initialY_;
	float maxSpeed_;
	bool accelerate_;
	std::vector<IBallObserver*> observers_;
	Uint64 timeOfLastXUpdate_;
	Uint64 timeOfLastYUpdate_;
	// float xCharge_;
	// float yCharge_;
	struct Velocity xVelocity_; // pixel/frame
	struct Velocity yVelocity_; // pixel/frame
	struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
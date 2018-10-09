#include "ballObject.h"

BallObject::BallObject(
	SdlClient* sdlClient,
	int textureId,
	int x,
	int y,
	int w,
	int h,
	struct Velocity xVelocity,
	struct Velocity yVelocity,
	bool accelerate,
	float maxSpeed)
{
	this->sdlClient_ = sdlClient;
	this->initialX_ = x;
	this->initialY_ = y;
	this->maxSpeed_ = maxSpeed;
	this->accelerate_ = accelerate;
	this->sdlClient_->GetElapsedTime(0, this->timeOfLastXUpdate_);
	this->timeOfLastYUpdate_ = this->timeOfLastXUpdate_;
	this->xVelocity_ = xVelocity;
	this->yVelocity_ = yVelocity;
	this->textureId_ = textureId;
	this->dest_.x = x;
	this->dest_.y = y;
	this->dest_.w = w;
	this->dest_.h = h;
	this->lastLocation_.x = x;
	this->lastLocation_.y = y;
}

void BallObject::ResolveCollision(ICollideable* object)
{
	if (this->xVelocity_.pixels > 0
		&& this->lastLocation_.x + this->dest_.w <= object->GetDestination()->x
		&& this->dest_.x + this->dest_.w > object->GetDestination()->x)
	{
		this->dest_.x -= 1;
		this->xVelocity_.pixels = -1 * this->xVelocity_.pixels;
		this->xVelocity_.ms = 1.25 * this->xVelocity_.ms;
	}

	if (this->xVelocity_.pixels < 0 
		&& this->lastLocation_.x >= object->GetDestination()->x + object->GetDestination()->w
		&& this->dest_.x < object->GetDestination()->x + object->GetDestination()->w)
	{
		this->dest_.x += 1;
		this->xVelocity_.pixels = -1 * this->xVelocity_.pixels;
		this->xVelocity_.ms = 1.25 * this->xVelocity_.ms;
	}

	if (this->yVelocity_.pixels < 0
		&& this->lastLocation_.y >= object->GetDestination()->y + object->GetDestination()->h
		&& this->dest_.y < object->GetDestination()->y + object->GetDestination()->h)
	{
		this->dest_.y += 1;
		this->yVelocity_.pixels = -1 * this->yVelocity_.pixels;
	}

	if (this->yVelocity_.pixels > 0
		&& (this->lastLocation_.y + this->dest_.h) <= object->GetDestination()->y
		&& (this->dest_.y + this->dest_.h) > object->GetDestination()->y)
	{
		this->dest_.y -= 1;
		this->yVelocity_.pixels = -1 * this->yVelocity_.pixels;
	}

	// IHasVelocity* h = null;
	// if (h = dynamic_cast<IHasVelocity*>(object))
	// {
	// 	this->xVelocity_ += .25 * h->GetXVelocity();
	// }

	// if (this->accelerate_ && this->yVelocity_ < this->maxSpeed_)
	// {
	// 	this->yVelocity_ *= 1.010;
	// }
}

void BallObject::HandleNewFrame()
{
	Uint64 now = 0;
	double msElapsedSinceX = this->sdlClient_->GetElapsedTime(this->timeOfLastXUpdate_, now);
	double msElapsedSinceY = this->sdlClient_->GetElapsedTime(this->timeOfLastYUpdate_, now);

	if (this->xVelocity_.ms > 0 && msElapsedSinceX >= this->xVelocity_.ms)
	{
		this->lastLocation_.x = this->dest_.x;
		this->dest_.x += (msElapsedSinceX / this->xVelocity_.ms) * this->xVelocity_.pixels;
		this->Notify();
		this->timeOfLastXUpdate_ = now;
	}

	if (this->yVelocity_.ms > 0 && msElapsedSinceY >= this->yVelocity_.ms)
	{
		this->lastLocation_.y = this->dest_.y;
		this->dest_.y += (msElapsedSinceY / this->yVelocity_.ms) * this->yVelocity_.pixels;
		this->Notify();
		this->timeOfLastYUpdate_ = now;
	}
}

void BallObject::Notify()
{
	for (std::vector<IBallObserver*>::iterator it = this->observers_.begin(); it != this->observers_.end(); it++)
	{
		(*it)->Update(this->dest_.x, this->dest_.y);
	}
}
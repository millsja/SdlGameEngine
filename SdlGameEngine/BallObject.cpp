#include "ballObject.h"

BallObject::BallObject(int textureId, int x, int y, int w, int h, float xVelocity, float yVelocity, bool accelerate, float maxSpeed)
{
	this->initialX_ = x;
	this->initialY_ = y;
	this->maxSpeed_ = maxSpeed;
	this->accelerate_ = accelerate;
	this->xCharge_ = 0;
	this->yCharge_ = 0;
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
	if (this->lastLocation_.x + this->dest_.w <= object->GetDestination()->x
		&& this->dest_.x + this->dest_.w > object->GetDestination()->x)
	{
		this->dest_.x -= 1;
		this->xVelocity_ = -0.75 * this->xVelocity_;
		this->xCharge_ = 0;
	}

	if (this->lastLocation_.x >= object->GetDestination()->x + object->GetDestination()->w
		&& this->dest_.x < object->GetDestination()->x + object->GetDestination()->w)
	{
		this->dest_.x += 1;
		this->xVelocity_ = -0.75 * this->xVelocity_;
		this->xCharge_ = 0;
	}

	if (this->lastLocation_.y >= object->GetDestination()->y + object->GetDestination()->h
		&& this->dest_.y < object->GetDestination()->y + object->GetDestination()->h)
	{
		this->dest_.y += 1;
		this->yVelocity_ = -1 * this->yVelocity_;
		this->yCharge_ = 0;
	}

	if ((this->lastLocation_.y + this->dest_.h) <= object->GetDestination()->y
		&& (this->dest_.y + this->dest_.h) > object->GetDestination()->y)
	{
		this->dest_.y -= 1;
		this->yVelocity_ = -1 * this->yVelocity_;
		this->yCharge_ = 0;
	}

	IHasVelocity* h = null;
	if (h = dynamic_cast<IHasVelocity*>(object))
	{
		this->xVelocity_ += .25 * h->GetXVelocity();
	}

	if (this->accelerate_ && this->yVelocity_ < this->maxSpeed_)
	{
		this->yVelocity_ *= 1.010;
	}
}

void BallObject::HandleNewFrame()
{
	this->xCharge_ += this->xVelocity_;
	this->yCharge_ += this->yVelocity_;

	if (fabs(this->xCharge_) >= 1)
	{
		this->lastLocation_.x = this->dest_.x;
		this->dest_.x += this->xCharge_;
		this->xCharge_ *= 0;
		this->Notify();
	}

	if (fabs(this->yCharge_) >= 1)
	{
		this->lastLocation_.y = this->dest_.y;
		this->dest_.y += this->yCharge_;
		this->yCharge_ *= 0;
		this->Notify();
	}
}

void BallObject::Notify()
{
	for (std::vector<IBallObserver*>::iterator it = this->observers_.begin(); it != this->observers_.end(); it++)
	{
		(*it)->Update(this->dest_.x, this->dest_.y);
	}
}
#include "ballObject.h"

BallObject::BallObject(
	SdlClient* sdlClient,
	int textureId,
	int x,
	int y,
	int w,
	int h,
	double xVelocity,
	double yVelocity,
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
	if (this->xVelocity_ > 0
		&& this->lastLocation_.x + this->dest_.w <= object->GetDestination()->x
		&& this->dest_.x + this->dest_.w > object->GetDestination()->x)
	{
		this->dest_.x -= 1;
		this->xVelocity_ *= -1;
	}

	if (this->xVelocity_ < 0 
		&& this->lastLocation_.x >= object->GetDestination()->x + object->GetDestination()->w
		&& this->dest_.x < object->GetDestination()->x + object->GetDestination()->w)
	{
		this->dest_.x += 1;
		this->xVelocity_ *= -1;
	}

	if (this->yVelocity_ < 0
		&& this->lastLocation_.y >= object->GetDestination()->y + object->GetDestination()->h
		&& this->dest_.y < object->GetDestination()->y + object->GetDestination()->h)
	{
		this->dest_.y += 1;
		this->yVelocity_ *= -1;
	}

	if (this->yVelocity_ > 0
		&& (this->lastLocation_.y + this->dest_.h) <= object->GetDestination()->y
		&& (this->dest_.y + this->dest_.h) > object->GetDestination()->y)
	{
		this->dest_.y -= 1;
		this->yVelocity_ *= -1;
	}

	IHasVelocity* h = null;
	if (h = dynamic_cast<IHasVelocity*>(object))
	{
		double newV = h->GetXVelocity();
		this->xVelocity_ =  newV != 0 ? newV : this->xVelocity_;
	}
	else
	{
		this->xVelocity_ *= 0.75;
	}

	if (this->accelerate_ && this->yVelocity_ < this->maxSpeed_)
	{
		this->yVelocity_ *= 1.01;
	}
}

void BallObject::Reset()
{
	this->dest_.x = this->initialX_;
	this->dest_.y = this->initialY_;
}

void BallObject::HandleNewFrame()
{
	Uint64 now = 0;
	double msElapsedSinceX = this->sdlClient_->GetElapsedTime(this->timeOfLastXUpdate_, now);
	double msElapsedSinceY = this->sdlClient_->GetElapsedTime(this->timeOfLastYUpdate_, now);

	double vX = IHasVelocity::GetTimePerPixel(this->xVelocity_);
	double vY = IHasVelocity::GetTimePerPixel(this->yVelocity_);
	if (fabs(this->xVelocity_) > 1 && msElapsedSinceX >= fabs(vX))
	{
		this->lastLocation_.x = this->dest_.x;
		this->dest_.x += (int)(msElapsedSinceX / vX);
		this->Notify();
		this->timeOfLastXUpdate_ = now;
	}
	else if (fabs(this->xVelocity_) <= 1)
	{
		this->timeOfLastXUpdate_ = now;
	}

	if (fabs(this->yVelocity_) > 1 && msElapsedSinceY >= fabs(vY))
	{
		// if (vY < 0)
		// {
		// 	vY *= 1.3;
		// }

		this->lastLocation_.y = this->dest_.y;
		this->dest_.y += (int)(msElapsedSinceY / vY);
		this->Notify();
		this->timeOfLastYUpdate_ = now;
	}
	else if (fabs(this->yVelocity_) <= 1)
	{
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
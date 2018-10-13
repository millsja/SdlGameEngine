#include "playerObject.h"

PlayerObject::PlayerObject(SdlClient* sdlClient, int textureId, int x, int y, int w, int h)
{
	this->sdlClient_ = sdlClient;
	this->textureId_ = textureId;
	this->dest_.x = x;
	this->dest_.y = y;
	this->dest_.w = w;
	this->dest_.h = h;
	// this->lastLocation_.x = x;
	// this->lastLocation_.y = y;
	this->locationAsOfLastFrame_.x = x;
	this->locationAsOfLastFrame_.y = y;
	this->xVelocity_ = 0;
	this->yVelocity_ = 0;
	this->sdlClient_->GetElapsedTime(0, this->velocityLastCheck_);
	this->moved_ = false;
}

void PlayerObject::HandleEvents(SDL_Event* event, const Uint8* keystates)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		this->moved_ = true;

		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		this->dest_.x = x - (this->dest_.w / 2);

		// Uint64 now = 0;
		// double elapsed = this->sdlClient_->GetElapsedTime(this->velocityLastCheck_, now);
		// this->velocityLastCheck_ = now;

		int diff = this->dest_.x - this->locationAsOfLastFrame_.x;
		double absdiff = fabs(diff);
		if (absdiff > 1)
		{
			this->xVelocity_ = fmin(log(absdiff) * 50, 500);
			this->xVelocity_ *= diff / absdiff;
		}
		// this->xVelocity_.ms = 0.85 * this->xVelocity_.ms + 0.25 * elapsed;

		this->locationAsOfLastFrame_.x = this->dest_.x;
		this->locationAsOfLastFrame_.y = this->dest_.y;
	}
}

void PlayerObject::SetLocation(int x, int y)
{
	this->dest_.x = x;
	this->dest_.y = y;
}

void PlayerObject::ResolveCollision(ICollideable* object)
{
	if (this->moved_)
	{
		if (this->locationAsOfLastFrame_.x + this->dest_.w <= object->GetDestination()->x
			&& this->dest_.x + this->dest_.w > object->GetDestination()->x)
		{
			this->dest_.x -= 1;
		}

		if (this->locationAsOfLastFrame_.x >= object->GetDestination()->x + object->GetDestination()->w
			&& this->dest_.x < object->GetDestination()->x + object->GetDestination()->w)
		{
			this->dest_.x += 1;
		}
	}
}

void PlayerObject::HandleNewFrame()
{
	Uint64 now = 0;
	double elapsed = this->sdlClient_->GetElapsedTime(this->velocityLastCheck_, now);

	if (!this->moved_ && elapsed > 100)
	{
		this->xVelocity_ *= 0.8;
	}

	this->moved_ = false;
}
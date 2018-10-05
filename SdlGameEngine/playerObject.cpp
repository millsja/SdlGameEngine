#include "playerObject.h"

PlayerObject::PlayerObject(int textureId, int x, int y, int w, int h)
{
	this->textureId_ = textureId;
	this->dest_.x = x;
	this->dest_.y = y;
	this->dest_.w = w;
	this->dest_.h = h;
	// this->lastLocation_.x = x;
	// this->lastLocation_.y = y;
	this->locationAsOfLastFrame_.x = x;
	this->locationAsOfLastFrame_.y = y;
}

void PlayerObject::HandleEvents(SDL_Event* event, const Uint8* keystates)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		this->dest_.x = x - (this->dest_.w / 2);
	}
}

void PlayerObject::SetLocation(int x, int y)
{
	this->dest_.x = x;
	this->dest_.y = y;
}

void PlayerObject::ResolveCollision(ICollideable* object)
{
	if (this->Moved(this->dest_.x, this->dest_.y))
	{
		// SDL_Rect* otherD = object->GetDestination();
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

		if (this->locationAsOfLastFrame_.y >= object->GetDestination()->y + object->GetDestination()->h
			&& this->dest_.y < object->GetDestination()->y + object->GetDestination()->h)
		{
			this->dest_.y += 1;
		}

		if ((this->locationAsOfLastFrame_.y + this->dest_.h) <= object->GetDestination()->y
			&& (this->dest_.y + this->dest_.h) > object->GetDestination()->y)
		{
			this->dest_.y -= 1;
		}

		// if (this->lastLocation_.x < otherD->x)
		// {
		// 	this->dest_.x = otherD->x - 1 - this->dest_.w;
		// }
		// else if (this->lastLocation_.x > otherD->x)
		// {
		// 	this->dest_.x = otherD->x + otherD->w + 1;
		// }
	}
}

bool PlayerObject::Moved(int x, int y)
{
	return !(x == this->locationAsOfLastFrame_.x && y == this->locationAsOfLastFrame_.y);
}

void PlayerObject::HandleNewFrame()
{
	this->xVelocity_ = 0.25 * (this->dest_.x - this->locationAsOfLastFrame_.x) + .85 * this->xVelocity_;
	this->yVelocity_ = 0.25 * (this->dest_.y - this->locationAsOfLastFrame_.y) + .85 * this->yVelocity_;

	this->locationAsOfLastFrame_.x = this->dest_.x;
	this->locationAsOfLastFrame_.y = this->dest_.y;
}
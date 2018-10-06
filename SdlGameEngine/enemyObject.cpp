#include "enemyObject.h"

EnemyObject::EnemyObject(int textureId, int x, int y, int w, int h, float velocityCoefficient)
{
	this->velocityCoefficient_ = velocityCoefficient;
	this->textureId_ = textureId;
	this->dest_.x = x;
	this->dest_.y = y;
	this->dest_.w = w;
	this->dest_.h = h;
	this->locationAsOfLastFrame_.x = x;
	this->locationAsOfLastFrame_.y = y;
	this->xCharge_ = 0;
	this->yCharge_ = 0;
	this->xVelocity_ = 0;
	this->yVelocity_ = 0;
}

void EnemyObject::SetLocation(int x, int y)
{
	this->dest_.x = x;
	this->dest_.y = y;
}

void EnemyObject::ResolveCollision(ICollideable* object)
{
	if (this->Moved(this->dest_.x, this->dest_.y))
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
	}
}

bool EnemyObject::Moved(int x, int y)
{
	return !(x == this->locationAsOfLastFrame_.x && y == this->locationAsOfLastFrame_.y);
}

void EnemyObject::HandleNewFrame()
{
	this->xCharge_ += this->xVelocity_;

	if (fabs(this->xCharge_) >= 1)
	{
		this->locationAsOfLastFrame_.x = this->dest_.x;
		this->dest_.x += this->xCharge_;
		this->xCharge_ *= 0;
	}
}

void EnemyObject::Update(int x, int y)
{
	if (x > this->dest_.x + this->dest_.w / 2)
	{
		this->xVelocity_ = this->velocityCoefficient_;
	}
	else if (x < this->dest_.x + this->dest_.w / 2)
	{
		this->xVelocity_ = -1 * this->velocityCoefficient_;
	}
	else
	{
		this->xVelocity_ = 0;
		this->xCharge_ = 0;
	}
}
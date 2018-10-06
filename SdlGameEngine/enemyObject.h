#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "iGameObject.h"
#include "iCollideable.h"
#include "iHasVelocity.h"
#include "iBallObserver.h"
#include "iEveryFrame.h"
#include "SDL.h"

class EnemyObject : public IGameObject, public ICollideable, public IHasVelocity, public IBallObserver, public IEveryFrame
{
public:
	EnemyObject(int textureId, int x, int y, int w, int h, float velocityCoefficient);
	void SetLocation(int x, int y);
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	float GetXVelocity() { return this->xVelocity_; }
	float GetYVelocity() { return this->yVelocity_; }
	void Update(int x, int y);
	void HandleNewFrame();
private:
	float velocityCoefficient_;
	float xCharge_;
	float yCharge_;
	float xVelocity_;
	float yVelocity_;
	struct Coords locationAsOfLastFrame_;
	bool Moved(int x, int y);
	// struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
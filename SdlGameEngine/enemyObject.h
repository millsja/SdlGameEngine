#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "iGameObject.h"
#include "iCollideable.h"
#include "iHasVelocity.h"
#include "iBallObserver.h"
#include "iEveryFrame.h"
#include "SDL.h"
#include "sdlClient.h"

class EnemyObject : public IGameObject, public ICollideable, public IHasVelocity, public IBallObserver, public IEveryFrame
{
public:
	EnemyObject(SdlClient* sdlClient, int textureId, int x, int y, int w, int h, float velocityCoefficient);
	void SetLocation(int x, int y);
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	double GetXVelocity() { return this->xVelocity_; }
	double GetYVelocity() { return this->yVelocity_; }
	void Update(int x, int y);
	void HandleNewFrame();
private:
	SdlClient* sdlClient_;
	float velocityCoefficient_;
	// float xCharge_;
	// float yCharge_;
	Uint64 timeOfLastVelocityCheck_;
	double xVelocity_;
	double yVelocity_;
	struct Coords locationAsOfLastFrame_;
	bool Moved(int x, int y);
	// struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
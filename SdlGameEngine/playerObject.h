#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "iGameObject.h"
#include "iCollideable.h"
#include "iControllable.h"
#include "iEveryFrame.h"
#include "iHasVelocity.h"
#include "SDL.h"

class PlayerObject : public IGameObject, public ICollideable, public IControllable, public IHasVelocity, public IEveryFrame
{
public:
	PlayerObject(int textureId, int x, int y, int w, int h);
	void HandleEvents(SDL_Event* e, const Uint8* keystates = null);
	void SetLocation(int x, int y);
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	float GetXVelocity() { return this->xVelocity_; }
	float GetYVelocity() { return this->yVelocity_; }
	void HandleNewFrame();
private:
	float xVelocity_;
	float yVelocity_;
	struct Coords locationAsOfLastFrame_;
	bool Moved(int x, int y);
	struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
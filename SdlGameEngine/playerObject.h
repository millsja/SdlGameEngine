#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "SDL.h"
#include "sdlClient.h"
#include "soundManager.h"
#include "iGameObject.h"
#include "iCollideable.h"
#include "iControllable.h"
#include "iEveryFrame.h"
#include "iHasVelocity.h"
#include "ballObject.h"

class PlayerObject : public IGameObject, public ICollideable, public IControllable, public IHasVelocity, public IEveryFrame
{
public:
	PlayerObject(SdlClient* sdlClient, int textureId, int x, int y, int w, int h, SoundManager* soundManager, int soundId);
	void HandleEvents(SDL_Event* e, const Uint8* keystates = null);
	void SetLocation(int x, int y);
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
	double GetXVelocity() { return this->xVelocity_; }
	double GetYVelocity() { return this->yVelocity_; }
	void HandleNewFrame();
private:
	int soundId_;
	SoundManager* soundManager_;
	SdlClient* sdlClient_;
	Uint64 velocityLastCheck_;
	double xVelocity_;
	double yVelocity_;
	struct Coords locationAsOfLastFrame_;
	bool moved_;
	// struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
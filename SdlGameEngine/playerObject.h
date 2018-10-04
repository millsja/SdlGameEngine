#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "iGameObject.h"
#include "iCollideable.h"
#include "iControllable.h"
#include "SDL.h"

class PlayerObject : public IGameObject, public ICollideable, public IControllable
{
public:
	PlayerObject(int textureId, int x, int y, int w, int h);
	void HandleEvents(SDL_Event* e, const Uint8* keystates = null);
	void SetLocation(int x, int y);
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object);
private:
	bool Moved(int x, int y);
	struct Coords lastLocation_;
	int textureId_;
	SDL_Rect dest_;
};

#endif
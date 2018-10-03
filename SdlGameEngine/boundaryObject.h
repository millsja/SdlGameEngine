#ifndef BOUNDARYOBJECT_H
#define BOUNDARYOBJECT_H

#include "iGameObject.h"
#include "iCollideable.h"
#include "SDL.h"

class BoundaryObject : public IGameObject, public ICollideable 
{
public:
	BoundaryObject(int textureId, int x, int y, int w, int h) 
	{
		this->textureId_ = textureId;
		this->dest_.x = x;
		this->dest_.y = y;
		this->dest_.w = w;
		this->dest_.h = h;
	}
	void HandleEvents(SDL_Event* e, const Uint8* keystates = null) {}
	void SetLocation(int x, int y) { this->dest_.x = x; this->dest_.y = y; }
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object) {}
private:
	int textureId_;
	SDL_Rect dest_;
};

#endif

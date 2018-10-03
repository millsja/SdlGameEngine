#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "utilities.h"

class IGameObject 
{
public:
	virtual void HandleEvents(SDL_Event* e, const Uint8* keystates = null) = 0;
	virtual void SetLocation(int x, int y) = 0;
	virtual SDL_Rect* GetDestination() = 0;
	virtual int GetTextureId() = 0;
};

#endif
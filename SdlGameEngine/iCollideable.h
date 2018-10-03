#ifndef ICOLLIDEABLE_H
#define ICOLLIDEABLE_H

#include "SDL.h"

class ICollideable 
{
public:
	virtual void ResolveCollision(ICollideable* object) = 0;
	virtual SDL_Rect* GetDestination() = 0;
};

#endif
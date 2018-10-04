#ifndef ICONTROLLABLE_H
#define ICONTROLLABLE_H

#include "SDL.h"
#include "utilities.h"

class IControllable 
{
public:
	virtual void HandleEvents(SDL_Event* e, const Uint8* keystates = null) = 0;
};

#endif
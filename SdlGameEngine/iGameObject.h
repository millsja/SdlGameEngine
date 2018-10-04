#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "utilities.h"

class IGameObject 
{
public:
	virtual void SetLocation(int x, int y) = 0;
	virtual SDL_Rect* GetDestination() = 0;
	virtual int GetTextureId() = 0;
};

#endif
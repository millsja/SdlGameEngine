#ifndef IGAMESTATE_H
#define IGAMESTATE_H

class IGameState
{
public:
	virtual void Start() = 0;
	virtual void Sleep() = 0;
};

#endif
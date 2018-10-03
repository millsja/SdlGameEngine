#ifndef STATESTACK_H
#define STATESTACK_H

#include <stack>
#include "iGameState.h"
#include "utilities.h"

class StateStack 
{
public:
	~StateStack();
	void Push(IGameState* gameState);
	void Run();
private:
	std::stack<IGameState*> stack_;
};

#endif
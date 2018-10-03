#include "stateStack.h"

StateStack::~StateStack()
{
	IGameState* top = null;
	while (!this->stack_.empty())
	{
		top = this->stack_.top();
		this->stack_.pop();
		if (top != null)
		{
			delete top;
			top = null;
		}
	}
}

void StateStack::Push(IGameState* gameState)
{
	IGameState* top = null;
	if (gameState != null)
	{
		if (!this->stack_.empty())
		{
			top = this->stack_.top();
			if (top != null)
			{
				top->Sleep();
			}
		}

		this->stack_.push(gameState);
	}
}

void StateStack::Run()
{
	IGameState* top = null;
	while (!this->stack_.empty())
	{
		top = this->stack_.top();
		top->Start();
		this->stack_.pop();
		top = null;
	}
}
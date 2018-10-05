#ifndef IHASVELOCITY_H
#define IHASVELOCITY_H

class IHasVelocity
{
public:
	virtual float GetXVelocity() = 0;
	virtual float GetYVelocity() = 0;
};

#endif
#ifndef IOBSERVABLEBALL_H 
#define IOBSERVABLEBALL_H

#include "iBallObserver.h"

class IObservableBall
{
public:
	virtual void AttachObserver(IBallObserver* observer) = 0;
	virtual void DetachObserver(IBallObserver* observer) = 0;
	virtual void Notify() = 0;
};

#endif
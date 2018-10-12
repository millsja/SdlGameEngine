#ifndef IHASVELOCITY_H
#define IHASVELOCITY_H

#include "utilities.h"
#include <math.h>

class IHasVelocity
{
public:
	static double GetTimePerPixel(double velocity)
	{ 
		double absV = fabs(velocity);
		if (absV <= 1)
		{
			return 0;
		}
		else
		{
			double sign = velocity / absV;
			return sign * 5 / (log10(absV));
		}
	}

	virtual double GetXVelocity() = 0;
	virtual double GetYVelocity() = 0;
};

#endif
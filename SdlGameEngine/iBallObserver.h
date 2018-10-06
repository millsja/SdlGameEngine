#ifndef IBALLOBSERVER_H
#define IBALLOBSERVER_H

class IBallObserver
{
public:
	virtual void Update(int x, int y) = 0;
};

#endif
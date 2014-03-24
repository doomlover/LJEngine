#ifndef LJTIMER_H
#define LJTIMER_H
#include "LJGeneralHeaders.h"
/*
 * A time inferface
 */
class LJTimer
{
public:
	virtual ~LJTimer(void){}
	virtual void Update()= 0;
	virtual float GetTimePerFrame() = 0;
	virtual void Reset() = 0;
	virtual float GetTime() = 0;
	virtual void SetTime(double time) = 0;
};

#endif

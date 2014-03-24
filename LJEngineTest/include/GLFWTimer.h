#ifndef GLFWTIMER_H
#define GLFWTIMER_H
#include "LJTimer.h"
class GLFWTimer : public LJTimer
{
	float m_Tpf;
	float m_PreviousTime;
public:
	GLFWTimer();
	~GLFWTimer(void);
	void Update();
	float GetTimePerFrame();
	void Reset();
	float GetTime();
	void SetTime(double time);
};//~GLFWTimer

#endif

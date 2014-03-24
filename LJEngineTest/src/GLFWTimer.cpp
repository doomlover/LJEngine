#include <GLFW/glfw3.h>
#include "GLFWTimer.h"
GLFWTimer::GLFWTimer()
	:m_Tpf(1.f/60.f),
	 m_PreviousTime(0)
{

}

GLFWTimer::~GLFWTimer(void)
{

}

void GLFWTimer::Update()
{
	float curTime = glfwGetTime();
	m_Tpf = curTime - m_PreviousTime;
	m_PreviousTime = curTime;
}

float GLFWTimer::GetTimePerFrame()
{
	return m_Tpf;
}

void GLFWTimer::Reset()
{
	m_PreviousTime = glfwGetTime();
	m_Tpf = 1.f/60.f;
}

float GLFWTimer::GetTime()
{
	return glfwGetTime();
}

void GLFWTimer::SetTime(double time)
{
	glfwSetTime(time);
}

#include <GLFW/glfw3.h>
#include "GLFWFrameListener.h"
#include "LJApplication.h"
#include "LJ1stPerCtrller.h"

double GLFWFrameListener::sw2 = 0;
double GLFWFrameListener::sh2 = 0;

GLFWFrameListener::GLFWFrameListener(void)
	:m_pWindow(NULL),
	 w2(0),
	 h2(0)
{
}


GLFWFrameListener::~GLFWFrameListener(void)
{
}

void GLFWFrameListener::FrameStarted(float tpf, LJApplication *app)
{
	if(glfwGetWindowAttrib(m_pWindow, GLFW_FOCUSED))
	{
		UpdateCamera(tpf, app);
	}
}

void GLFWFrameListener::FrameEnded(float tpf, LJApplication *app)
{
	if(m_pWindow)
	{
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
		if(glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_pWindow, GL_TRUE);
		}
		if(glfwWindowShouldClose(m_pWindow))
		{
			if(app)
				app->Stop();
		}
	}
}

void GLFWFrameListener::UpdateCamera(float tpf, LJApplication *app)
{
	/*app->UpdateCamera(tpf);*/
}

void GLFWFrameListener::SetGlfwWindow(GLFWwindow *window, double w, double h)
{
	m_pWindow = window;
	w2 = w/2.0;
	h2 = h/2.0;
	sw2 = w2;
	sh2 = h2;
	glfwSetWindowFocusCallback(window, GLFWFrameListener::GLFWWindwoFocusCB);
}

void GLFWFrameListener::GLFWWindwoFocusCB(GLFWwindow *window, int hasFocus)
{
	if(hasFocus)
	{
		glfwSetCursorPos(window, sw2, sh2);
	}
}

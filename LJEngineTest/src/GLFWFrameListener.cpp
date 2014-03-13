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
				app->m_bStop = true;
		}
	}
}

void GLFWFrameListener::UpdateCamera(float tpf, LJApplication *app)
{
	LJ1stPerCtrller *m_Camera = app->m_FirstPerCamera;
	bool update = false;
	double posx, posy;
	glfwGetCursorPos(m_pWindow, &posx, &posy);
	glfwSetCursorPos(m_pWindow, w2, h2);
	posx = w2-posx;
	posy = h2-posy;
	if(posx != 0)
	{
		// camera reverse rotate around Y
		if(posx < 0)
		{
			m_Camera->SetRotationSpeedY(-0.9f);
		}
		else {
			m_Camera->SetRotationSpeedY(0.9f);
		}
		update = true;
	}
	if(posy != 0)
	{
		// camera reverse rotate around X
		if(posy < 0)
		{
			m_Camera->SetRotationSpeedX(-0.9f);
		}
		else {
			m_Camera->SetRotationSpeedX(0.9f);
		}
		update = true;
	}
	if((glfwGetKey(m_pWindow, GLFW_KEY_W)) == GLFW_PRESS)
	{
		m_Camera->SetSpeed(-5);
		update = true;
	}
	if((glfwGetKey(m_pWindow, GLFW_KEY_S)) == GLFW_PRESS)
	{
		m_Camera->SetSpeed(5);
		update = true;
	}
	if((glfwGetKey(m_pWindow, GLFW_KEY_A)) == GLFW_PRESS)
	{
		m_Camera->SetSlideSpeed(-5);
		update = true;
	}
	if((glfwGetKey(m_pWindow, GLFW_KEY_D)) == GLFW_PRESS)
	{
		m_Camera->SetSlideSpeed(5);
		update = true;
	}
	if(glfwGetKey(m_pWindow, GLFW_KEY_UP) == GLFW_PRESS)
	{
		m_Camera->SetPos(m_Camera->GetPos() + LJVector3(0.f, 0.05f, 0.f));
		update = true;
	}
	if(glfwGetKey(m_pWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		m_Camera->SetPos(m_Camera->GetPos() - LJVector3(0.f, 0.05f, 0.f));
		update = true;
	}
	if (update) {
		m_Camera->Update(tpf);
		m_Camera->SetSpeed(0);
		m_Camera->SetSlideSpeed(0);
		m_Camera->SetRotationSpeedX(0);
		m_Camera->SetRotationSpeedY(0);
	}
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

void GLFWKeyCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return ;
	}
	
}

void GLFWFrameListener::GLFWWindwoFocusCB(GLFWwindow *window, int hasFocus)
{
	if(hasFocus)
	{
		glfwSetCursorPos(window, sw2, sh2);
	}
}

#pragma once
#include "LJFrameListener.h"

struct GLFWwindow;
class LJApplication;
class LJ1stPerCtrller;

class GLFWFrameListener :
	public LJFrameListener
{
	friend void GLFWKeyCB(GLFWwindow* window, int key, int scancode, int action, int mods);
	GLFWwindow *m_pWindow;
	double w2;
	double h2;
	static double sw2;
	static double sh2;
public:
	GLFWFrameListener(void);
	~GLFWFrameListener(void);
	void FrameStarted(float tpf, LJApplication *app);
	void FrameEnded(float tpf, LJApplication *app);

	void SetGlfwWindow(GLFWwindow *window, double w, double h);

	void UpdateCamera(float tpf, LJApplication *app);

	void static GLFWWindwoFocusCB(GLFWwindow *window, int hasFocus);
};

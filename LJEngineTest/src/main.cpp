#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "LJApplication.h"
#include "Utils.h"
#include "GLFWFrameListener.h"
#include "GLFWTimer.h"

LJApplication *g_pApp;
GLFWwindow *g_pGLFWwindow;

void OnDestroy();
void LJGlfwErrorCB(int error, const char *description);

UINT Width = 800;
UINT Height = 600;

int main(int argc, char **argv)
{
	glfwSetErrorCallback(LJGlfwErrorCB);
	if(!glfwInit()) {
		fprintf(stderr, "creating glfw window failed");
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	g_pGLFWwindow = glfwCreateWindow(Width, Height, "Test Window", NULL, NULL);
	if(!g_pGLFWwindow)
	{
		glfwTerminate();
	}
	glfwSetInputMode(g_pGLFWwindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetWindowPos(g_pGLFWwindow, 500, 30);
	glfwMakeContextCurrent(g_pGLFWwindow);
	glfwSetKeyCallback(g_pGLFWwindow, GLFWKeyCB);

	GLFWFrameListener *listener = new GLFWFrameListener();
	listener->SetGlfwWindow(g_pGLFWwindow, Width, Height);
	LJTimer *timer = new GLFWTimer();

	g_pApp = &LJApplication::GetApp("OpenGL");
	g_pApp->AddFrameListener(listener);
	g_pApp->m_Timer = timer;
	g_pApp->WindowWidth = Width;
	g_pApp->WindowHeight = Height;
	g_pApp->SetOnStartCallback(SceneInit);
	g_pApp->SetOnDestroyCallback(OnDestroy);
	g_pApp->m_pWindow = reinterpret_cast<HWND>(g_pGLFWwindow);
	g_pApp->Initialize();
	g_pApp->Run();

	extern vector<LJMesh*> gMeshes;
	vector<LJMesh*>::iterator it = gMeshes.begin();
	while(it != gMeshes.end()){
		delete *it;
		++it;
	}
	return 0;
}


void OnDestroy()
{
	glfwDestroyWindow(g_pGLFWwindow);
	glfwTerminate();
}


void LJGlfwErrorCB(int error, const char *description)
{
	fprintf(stderr, "%s\n", description);
}

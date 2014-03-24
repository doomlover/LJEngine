#include <GL/glew.h>

#include "Scene.h"
#include "SimpleApp.h"
#include "Utils.h"
#include "GLFWFrameListener.h"
#include "GLFWTimer.h"

int main(int argc, char **argv)
{

	SimpleApp *pApp = new SimpleApp();
	pApp->Run();

	delete pApp;
	return 0;
}

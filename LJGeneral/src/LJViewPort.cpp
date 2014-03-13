#include "LJViewPort.h"

LJViewPort::LJViewPort(float n, float f, float fov, float ar, 
		LJDIMENSIONMODE m, LJSTAGE s)
:fNear(n),
 fFar(f),
 fFov(fov),
 fAspectRatio(ar),
 mode(m),
 stage(s),
 Camera(NULL),
 scene(NULL)
{
}

LJViewPort::~LJViewPort(void)
{
	if(Camera)
	{
		delete Camera;
	}
}

void LJViewPort::SetupScene(LJNode& scene)
{
	this->scene = &scene;
}

LJNode* LJViewPort::GetScene()
{
	return scene;
}

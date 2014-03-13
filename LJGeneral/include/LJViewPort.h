#ifndef LJVIEWPORT_H
#define LJVIEWPORT_H

#include "LJGeneralHeaders.h"
#include "LJRenderDevice.h"
#include "LJSpatial.h"
#include "LJNode.h"
#include "LJGeometry.h"
#include "LJMoveController.h"

class _LJExport LJViewPort
{
public:
	float fNear;
	float fFar;
	float fFov;
	float fAspectRatio;
	LJVIEWPORT viewPort;
	LJDIMENSIONMODE mode;
	LJSTAGE stage;
	LJMoveController *Camera;
	void SetupScene(LJNode& scene);
	LJNode* GetScene();
	LJViewPort():fNear(0.1f),fFar(100.f),fFov(45.f),fAspectRatio(1.f),mode(LJ_DM_PERSPECTIVE),stage(LJ_STAGE_MAX),Camera(NULL),scene(NULL){};
	LJViewPort(float n, float f, float fov, float ar, 
		LJDIMENSIONMODE m, LJSTAGE s);
	~LJViewPort(void);
private:
	LJNode *scene;
};//~LJViewPort

#endif

#ifndef LJRENDERPASS_H
#define LJRENDERPASS_H

#include "LJGeneralHeaders.h"
#include "LJRenderDevice.h"
#include "LJSpatial.h"
#include "LJNode.h"
#include "LJGeometry.h"
#include "LJMoveController.h"
#include "LJFramebuffer.h"

class _LJExport LJRenderPass
{
public:
	LJRenderPass(UINT index);
	~LJRenderPass(void);

	void SetupScene(LJNode& scene);
	LJNode* GetScene();

	void SetIndex(UINT ind) { m_Index = ind; }
	UINT GetIndex() const { return m_Index;}

	void SetPerspective(float fFov, float fAspect, float fNear, float fFar);
	void SetProjectionMode(LJDIMENSIONMODE mode);
public:
	float fNear;
	float fFar;
	float fFov;
	float fAspectRatio;
	LJVIEWPORT viewPort;
	LJDIMENSIONMODE mode;
	LJMoveController *Camera;
	LJFramebuffer fb;
private:
	LJNode *scene;
	UINT m_Index;
};//~LJViewPort

#endif

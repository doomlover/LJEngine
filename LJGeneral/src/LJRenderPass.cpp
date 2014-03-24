#include "LJRenderPass.h"

LJRenderPass::LJRenderPass(UINT index)
:fNear(0.1f),fFar(100.f),fFov(45.f),fAspectRatio(1.f),
 mode(LJ_DM_PERSPECTIVE),Camera(NULL),scene(NULL),m_Index(index)
{
}

LJRenderPass::~LJRenderPass(void)
{
}

void LJRenderPass::SetupScene(LJNode& scene)
{
	this->scene = &scene;
}

LJNode* LJRenderPass::GetScene()
{
	return scene;
}

void LJRenderPass::SetPerspective(float fFov, float fAspect, float fNear, float fFar)
{
	this->fFov = fFov;
	this->fAspectRatio = fAspect;
	this->fNear = fNear;
	this->fFar = fFar;
}
void LJRenderPass::SetProjectionMode(LJDIMENSIONMODE mode)
{
	this->mode = mode;
}

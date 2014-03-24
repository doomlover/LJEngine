#ifndef SCENE_H
#define SCENE_H
#include "LJApplication.h"
#include "LJRenderDevice.h"

void SceneInit(LJApplication& app);
void UpdateCamera();

class MyApp : public LJApplication
{
	LJRenderDevice *m_pDevice;
	LJMaterialManager *m_pMatManager;
	LJRenderManager *m_pRenderManager;
	LJTextureManager *m_pTexManager;

	vector<LJMesh*> m_Meshes;
};

#endif

#include "Scene.h"
#include "LJGeneralType.h"
#include "LJTextureManager.h"
#include "LJMaterialManager.h"
#include "LJRenderManager.h"
#include "LJMesh.h"
#include "LJMaterial.h"
#include "LJTechnique.h"
#include "LJPass.h"
#include "Utils.h"
#include "LJ1stPerCtrller.h"
#include "LJShader.h"
#include "LJRenderState.h"
#include "LJGeometry.h"
#include "LJViewPort.h"
#include "GLFWFrameListener.h"
#include "LJCameraTools.h"
#include "LJEffectFileParser.h"

LJ1stPerCtrller *g_pFirstPersonCamera;
LJRenderDevice *g_pDevice;
LJMaterialManager *g_pMatManager;
LJRenderManager *g_pRenderManager;

vector<LJMesh*> gMeshes;

void SceneInit(LJApplication& app) {
	g_pDevice = app.m_pDevice;
	g_pMatManager = app.MaterialManager;
	g_pRenderManager = app.RenderManager;

	g_pFirstPersonCamera = app.m_FirstPerCamera;
	g_pFirstPersonCamera->SetPos(LJVector3(-10.f, 10.f, 0.f));
	g_pFirstPersonCamera->SetRotation(DegreeToRadian(-45.f), DegreeToRadian(-90.f), 0.f);
	LJMatrix4 view = BuildViewMatrix(g_pFirstPersonCamera->GetRight(),
			g_pFirstPersonCamera->GetUp(), g_pFirstPersonCamera->GetDir(),
			g_pFirstPersonCamera->GetPos());
	LJViewPort aVP(0.01f, 1000.f, 45.f, 4.0f / 3.0f, LJ_DM_PERSPECTIVE,
			LJ_STAGE_3D0);
	LJViewPort *vp = g_pRenderManager->CreateViewPort();
	*vp = aVP;
	vp->Camera = g_pFirstPersonCamera;
	vp->SetupScene(*app.m_RootNode);
	/* Set Near & Far clip planes and initialize 2D settings */
	g_pDevice->SetNearFarClip(vp->fNear, vp->fFar);
	/* initialize 3D projection matrix for LJ_STAGE_3D0 */
	g_pDevice->InitStage(vp->fFov, vp->fAspectRatio, vp->stage);
	/* Set 3D view-port */
	LJVIEWPORT viewport = { 0, 0, app.WindowWidth, app.WindowHeight };
	g_pDevice->SetViewport(vp->stage, viewport);
	g_pDevice->SetClearColor(0.1f, 0.0f, 0.1f);

	UINT nMat0 = g_pMatManager->CreateMaterial("Assets/Effectfiles/CubeMap.ef");
	UINT nMat1 = g_pMatManager->CreateMaterial("Assets/Effectfiles/Lighting.ef");
	UINT nMat2 = g_pMatManager->CreateMaterial("Assets/Effectfiles/NormalMap.ef");
	UINT nMat3 = g_pMatManager->CreateMaterial("Assets/Effectfiles/ProjectTexture.ef");

	// TEAPOT0
	LJMesh *pMesh = LoadMode("Assets/Modes/teapot.obj");
	gMeshes.push_back(pMesh);
	LJGeometry *pGeo0 = new LJGeometry();
	app.m_RootNode->AttachChild(*pGeo0);
	pGeo0->SetMesh(pMesh);
	pGeo0->SetMaterial(nMat0);
	pGeo0->SetTranslation(3, 0, 0);

	// SKY BOX
	LJMesh *pMesh1 = LoadMode("Assets/Modes/skybox.obj");
	gMeshes.push_back(pMesh1);
	LJGeometry *pGeo2 = new LJGeometry();
	app.m_RootNode->AttachChild(*pGeo2);
	pGeo2->SetMesh(pMesh1);
	pGeo2->SetMaterial(nMat0);
	int paramVal = 1;
	pGeo2->SetAdditionalMatParam(LJMaterial::LJMatParam("DrawSkyBox", LJBOOL, &paramVal, sizeof(int)));

	// CYLINDER
	LJMesh *pMesh2 = LoadMode("Assets/Modes/cylinder.obj");
	gMeshes.push_back(pMesh2);
	LJGeometry *pGeo4 = new LJGeometry();
	pGeo4->SetMesh(pMesh2);
	pGeo4->SetMaterial(nMat1);
	app.m_RootNode->AttachChild(*pGeo4);

	// PLANE
//	LJMesh *pMesh3 = LoadMode("Assets/Modes/plane.obj");
//	gMeshes.push_back(pMesh3);
//	LJGeometry *pGeo5 = new LJGeometry();
//	pGeo5->SetMesh(pMesh3);
//	pGeo5->SetMaterial(nMat3);
//	LJVector3 color(0.5f, 0.5f, 1.0f);
//	app.m_RootNode->AttachChild(*pGeo5);

	// TEAPOT1
	LJGeometry *pGeo3 = new LJGeometry();
	pGeo3->SetMesh(pMesh);
	pGeo3->SetMaterial(nMat1);
	pGeo3->SetLocalTranslation(-3, 0, -4);
	pGeo3->SetAdditionalMatParam(LJMaterial::LJMatParam("Color", LJVECTOR3f, new LJVector3(1.0f, 0.5f, 0.5f), sizeof(LJVector3)));
	app.m_RootNode->AttachChild(*pGeo3);

	// Texture Projection
/*	LJ1stPerCtrller cam;
	cam.SetPos(LJVector3(0.f, 0.f, 10.f));
	LJMatrix4 camView = BuildViewMatrix(cam.GetRight(), cam.GetUp(), cam.GetDir(), cam.GetPos());
	LJMatrix4 camProj, camOrth;
	BuildPersMatrix(30.f, 1.f, 0.01f, 1000.f, camProj, camOrth);
	LJMatrix4 camScale(0.5f, 0.f, 0.f, 0.f,
			           0.0f, 0.5f,0.f, 0.f,
			           0.0f, 0.0f,0.5f,0.f,
			           0.5f, 0.5f,0.5f,1.f);
	LJMatrix4 camSPV = camScale * camProj * camView;
	LJMaterial *pMat3 = g_pMatManager->GetMaterial(nMat3);
	pMat3->SetParam("ProjectorMatrix", LJMATRIX4f, camSPV);
	LJTexture *pTex3 = pMat3->GetTexture("projectMap");
	if(!pTex3) throw "Texture set fialed";
	pTex3->SetParameter(LJ_TEXTURE_WRAP_S, LJ_CLAMP_TO_BORDER);
	pTex3->SetParameter(LJ_TEXTURE_WRAP_T, LJ_CLAMP_TO_BORDER);
*/
}

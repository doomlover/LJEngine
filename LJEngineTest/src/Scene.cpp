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
#include "LJRenderPass.h"
#include "GLFWFrameListener.h"
#include "LJCameraTools.h"
#include "LJEffectFileParser.h"
#include "LJRenderTexture.h"

LJRenderDevice *g_pDevice;
LJMaterialManager *g_pMatManager;
LJRenderManager *g_pRenderManager;
LJTextureManager *g_pTexManager;

vector<LJMesh*> gMeshes;

void SceneInit(LJApplication& app) {
	g_pDevice = app.m_pDevice;
	g_pMatManager = app.MaterialManager;
	g_pRenderManager = app.RenderManager;
	g_pTexManager = app.TextureManager;

	app.m_FirstPerCamera->SetPos(LJVector3(-10.f, 10.f, 10.f));
	app.m_FirstPerCamera->SetRotation(-atan(1.f/1.414f), DegreeToRadian(-45.f), 0.f);
	LJMatrix4 view = BuildViewMatrix(app.m_FirstPerCamera->GetRight(),
			app.m_FirstPerCamera->GetUp(), app.m_FirstPerCamera->GetDir(),
			app.m_FirstPerCamera->GetPos());

	LJRenderPass *renderPass0 = g_pRenderManager->CreateRenderPass();
	renderPass0->SetPerspective(45.f, 4.0f / 3.0f, 0.01f, 1000.f);
	renderPass0->SetProjectionMode(LJ_DM_PERSPECTIVE);
	renderPass0->Camera = app.m_FirstPerCamera;
	renderPass0->viewPort = LJVIEWPORT(0, 0, app.WindowWidth, app.WindowHeight);
	renderPass0->SetupScene(*app.m_RootNode);
	// offscreen framebuffer
	UINT nOffTex0;
	LJTexture *offTex0 = g_pTexManager->CreateTexture(&nOffTex0);
	offTex0->SetTarget(LJ_TEXTURE_2D);
	LJRenderTexture renderTex0(app.WindowWidth, app.WindowHeight, LJ_RGBA, nOffTex0, offTex0);
	LJRenderTexture depthTex0(app.WindowWidth, app.WindowHeight, LJ_DEPTH_COMPONENT);
	renderPass0->fb.AddRenderTexture(renderTex0);
	renderPass0->fb.SetDepthTexture(depthTex0);

	UINT nMat0 = g_pMatManager->CreateMaterial("Assets/Effectfiles/CubeMap.ef", g_pTexManager);
	UINT nMat1 = g_pMatManager->CreateMaterial("Assets/Effectfiles/Lighting.ef", g_pTexManager);
	UINT nMat2 = g_pMatManager->CreateMaterial("Assets/Effectfiles/NormalMap.ef", g_pTexManager);
	UINT nMat3 = g_pMatManager->CreateMaterial("Assets/Effectfiles/ProjectTexture.ef", g_pTexManager);

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
	// Rectangle scene
	static const float rect_vertex_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
	};
	static const float rect_texcoord_data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f, 
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	LJMesh *pMeshRect = new LJMesh();
	pMeshRect->SetBuffer((void*)rect_vertex_data, 3, sizeof(rect_vertex_data)/sizeof(float), LJVertexBuffer::Float, "inPosition",
		LJVertexBuffer::LJ_ARRAY_BUFFER, LJVertexBuffer::LJ_STATIC_DRAW);
	pMeshRect->SetBuffer((void*)rect_texcoord_data, 2, sizeof(rect_texcoord_data)/sizeof(float), LJVertexBuffer::Float, "inTexcoord",
		LJVertexBuffer::LJ_ARRAY_BUFFER, LJVertexBuffer::LJ_STATIC_DRAW);
	LJGeometry *pGeoRect = new LJGeometry();
	pGeoRect->SetMesh(pMeshRect);
	UINT nMatRect = g_pMatManager->CreateMaterial("Assets/Effectfiles/Post.ef", g_pTexManager);
	LJMaterial *pMatRect = g_pMatManager->GetMaterial(nMatRect);
	pMatRect->SetParam("renderTex", nOffTex0);
	pGeoRect->SetMaterial(nMatRect);
	LJRenderPass *renderPass1 = g_pRenderManager->CreateRenderPass();
	// no camera, no projection, on screen framebuffer(default)
	renderPass1->viewPort = LJVIEWPORT(0, 0, app.WindowWidth, app.WindowHeight);
	LJNode *scene = new LJNode();
	scene->AttachChild(*pGeoRect);
	renderPass1->SetupScene(*scene);
}

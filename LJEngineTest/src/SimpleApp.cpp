/*
 * SimpleApp.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: liu
 */
#include <GLFW/glfw3.h>
#include "SimpleApp.h"

SimpleApp::SimpleApp()
:nMainSceneTex(LJ_MAX_ID),
 glfwWindow(NULL),
 m_Camera(NULL),
 m_MainSceneNode(NULL),
 m_WindowSceneNode(NULL)
{
	// create GLFW window
	WindowWidth = 1024;
	WindowHeight = 768;
	w2 = WindowWidth/2.0;
	h2 = WindowHeight/2.0;
	AppCreateWindow();
}

SimpleApp::~SimpleApp(void)
{
	vector<LJMesh*>::iterator it = pMeshes.begin();
	while(it != pMeshes.end()){
		delete *it;
		++it;
	}
	if(m_MainSceneNode)
	{
		delete m_MainSceneNode;
	}
	if(m_WindowSceneNode)
	{
		delete m_WindowSceneNode;
	}
	if(m_Camera)
	{
		delete m_Camera;
	}
}

void SimpleApp::SimpleInit()
{
	// create main node
	m_MainSceneNode = new LJNode();
	// create camera
	m_Camera = new LJ1stPerCtrller();
	// create a GLFW timer and set timer
	m_Timer = new GLFWTimer();
	// create and register a frame listener
	SimpleFrameListener *listener = new SimpleFrameListener(this);
	/*listener->SetGlfwWindow(glfwWindow, WindowWidth, WindowHeight);*/
	AddFrameListener(listener);
	// setup scene
	SetBasicScene();
	SetWindowScene();
}

void SimpleApp::SimpleCleanUp()
{
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}

void LJGlfwErrorCB(int error, const char *description)
{
	fprintf(stderr, "%s\n", description);
}

void SimpleApp::AppCreateWindow()
{
	glfwSetErrorCallback(LJGlfwErrorCB);
	if(!glfwInit()) {
		fprintf(stderr, "creating glfw window failed");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindow = glfwCreateWindow(WindowWidth, WindowHeight, "Test Window", NULL, NULL);
	if(!glfwWindow)
	{
		glfwTerminate();
	}
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetWindowPos(glfwWindow, 500, 30);
	glfwMakeContextCurrent(glfwWindow);
}

SimpleApp::SimpleFrameListener::SimpleFrameListener(SimpleApp *app)
{
	this->app = app;
	glfwSetWindowFocusCallback(app->glfwWindow, GLFWFrameListener::GLFWWindwoFocusCB);
}

void SimpleApp::SimpleFrameListener::FrameStarted(float tpf, LJApplication *app_)
{

	if(glfwGetWindowAttrib(app->glfwWindow, GLFW_FOCUSED))
	{
		UpdateCamera(tpf, app);
	}
}

void SimpleApp::SimpleFrameListener::FrameEnded(float tpf, LJApplication *app_)
{
	if(app->glfwWindow)
	{
		glfwSwapBuffers(app->glfwWindow);
		glfwPollEvents();
		if(glfwGetKey(app->glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(app->glfwWindow, GL_TRUE);
		}
		if(glfwWindowShouldClose(app->glfwWindow))
		{
			if(app)
				app->Stop();
		}
	}
}

void SimpleApp::SimpleFrameListener::WindwoFocusCB(GLFWwindow *window, int hasFocus)
{
	if(hasFocus)
	{
		glfwSetCursorPos(window, app->w2, app->h2);
	}
}


void SimpleApp::SetBasicScene()
{
	// setup camera
	m_Camera->SetPos(LJVector3(-10.f, 10.f, 10.f));
	m_Camera->SetRotation(-atan(1.f/1.414f), DegreeToRadian(-45.f), 0.f);
	// setup render pass for main scene
	LJRenderPass *renderPass0 = RenderManager->CreateRenderPass();
	renderPass0->SetPerspective(45.f, 4.0f / 3.0f, 0.01f, 1000.f);
	renderPass0->SetProjectionMode(LJ_DM_PERSPECTIVE);
	renderPass0->Camera = m_Camera;
	renderPass0->viewPort = LJVIEWPORT(0, 0, WindowWidth, WindowHeight);
	renderPass0->SetupScene(*m_MainSceneNode);
	// OFFSCREEN TEXTURE
	LJTexture *offTex0 = TextureManager->CreateTexture(&nMainSceneTex);
	offTex0->SetTarget(LJ_TEXTURE_2D);
	LJRenderTexture renderTex0(WindowWidth, WindowHeight, LJ_RGBA, nMainSceneTex, offTex0);
	LJRenderTexture depthTex0(WindowWidth, WindowHeight, LJ_DEPTH_COMPONENT);
	// FRAMEBUFFER SET RENDERTEXTURE
	renderPass0->fb.AddRenderTexture(renderTex0);
	// FRAMEBUFFER SET DEPTH
	renderPass0->fb.SetDepthTexture(depthTex0);

	UINT nMat0 = MaterialManager->CreateMaterial("Assets/Effectfiles/CubeMap.ef", TextureManager);
	UINT nMat1 = MaterialManager->CreateMaterial("Assets/Effectfiles/Lighting.ef", TextureManager);

	// TEAPOT0
	LJMesh *pMesh = LoadMode("Assets/Modes/teapot.obj");
	pMeshes.push_back(pMesh);
	LJGeometry *pGeo0 = new LJGeometry();
	m_MainSceneNode->AttachChild(*pGeo0);
	pGeo0->SetMesh(pMesh);
	pGeo0->SetMaterial(nMat0);
	pGeo0->SetTranslation(3, 0, 0);

	// SKY BOX
	LJMesh *pMesh1 = LoadMode("Assets/Modes/skybox.obj");
	pMeshes.push_back(pMesh1);
	LJGeometry *pGeo2 = new LJGeometry();
	m_MainSceneNode->AttachChild(*pGeo2);
	pGeo2->SetMesh(pMesh1);
	pGeo2->SetMaterial(nMat0);
	int paramVal = 1;
	pGeo2->SetAdditionalMatParam(LJMaterial::LJMatParam("DrawSkyBox", LJBOOL, &paramVal, sizeof(int)));

	// CYLINDER
	LJMesh *pMesh2 = LoadMode("Assets/Modes/cylinder.obj");
	pMeshes.push_back(pMesh2);
	LJGeometry *pGeo4 = new LJGeometry();
	pGeo4->SetMesh(pMesh2);
	pGeo4->SetMaterial(nMat1);
	m_MainSceneNode->AttachChild(*pGeo4);

	// TEAPOT1
	LJGeometry *pGeo3 = new LJGeometry();
	pGeo3->SetMesh(pMesh);
	pGeo3->SetMaterial(nMat1);
	pGeo3->SetLocalTranslation(-3, 0, -4);
	pGeo3->SetAdditionalMatParam(LJMaterial::LJMatParam("Color", LJVECTOR3f, new LJVector3(1.0f, 0.5f, 0.5f), sizeof(LJVector3)));
	m_MainSceneNode->AttachChild(*pGeo3);
}

void SimpleApp::SetWindowScene()
{
	// Rectangle
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
	// setup material
	UINT nMatRect = MaterialManager->CreateMaterial("Assets/Effectfiles/Post.ef", TextureManager);
	LJMaterial *pMatRect = MaterialManager->GetMaterial(nMatRect);
	pMatRect->SetParam("renderTex", nMainSceneTex);
	pGeoRect->SetMaterial(nMatRect);
	LJRenderPass *renderPass1 = RenderManager->CreateRenderPass();
	// no camera, no projection, on screen framebuffer(default)
	renderPass1->viewPort = LJVIEWPORT(0, 0, WindowWidth, WindowHeight);
	m_WindowSceneNode = new LJNode();
	m_WindowSceneNode->AttachChild(*pGeoRect);
	renderPass1->SetupScene(*m_WindowSceneNode);
}

void SimpleApp::SimpleFrameListener::UpdateCamera(float tpf, LJApplication *app_)
{
	LJ1stPerCtrller *m_Camera = app->m_Camera;
	bool update = false;
	double posx, posy;
	glfwGetCursorPos(app->glfwWindow, &posx, &posy);
	glfwSetCursorPos(app->glfwWindow, app->w2, app->h2);
	posx = app->w2-posx;
	posy = app->h2-posy;
	if(posx != 0)
	{
		// camera reverse rotate around Y
		if(posx < 0)
		{
			m_Camera->SetRotationSpeedY(-0.9f);
		}
		else {
			m_Camera->SetRotationSpeedY(0.9f);
		}
		update = true;
	}
	if(posy != 0)
	{
		// camera reverse rotate around X
		if(posy < 0)
		{
			m_Camera->SetRotationSpeedX(-0.9f);
		}
		else {
			m_Camera->SetRotationSpeedX(0.9f);
		}
		update = true;
	}
	if((glfwGetKey(app->glfwWindow, GLFW_KEY_W)) == GLFW_PRESS)
	{
		m_Camera->SetSpeed(-5);
		update = true;
	}
	if((glfwGetKey(app->glfwWindow, GLFW_KEY_S)) == GLFW_PRESS)
	{
		m_Camera->SetSpeed(5);
		update = true;
	}
	if((glfwGetKey(app->glfwWindow, GLFW_KEY_A)) == GLFW_PRESS)
	{
		m_Camera->SetSlideSpeed(-5);
		update = true;
	}
	if((glfwGetKey(app->glfwWindow, GLFW_KEY_D)) == GLFW_PRESS)
	{
		m_Camera->SetSlideSpeed(5);
		update = true;
	}
	if(glfwGetKey(app->glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
	{
		m_Camera->SetPos(m_Camera->GetPos() + LJVector3(0.f, 0.05f, 0.f));
		update = true;
	}
	if(glfwGetKey(app->glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		m_Camera->SetPos(m_Camera->GetPos() - LJVector3(0.f, 0.05f, 0.f));
		update = true;
	}
	if (update) {
		m_Camera->Update(tpf);
		m_Camera->SetSpeed(0);
		m_Camera->SetSlideSpeed(0);
		m_Camera->SetRotationSpeedX(0);
		m_Camera->SetRotationSpeedY(0);
	}
}


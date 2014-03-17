#include "LJApplication.h"
#include "LJFrameListener.h"
#include "LJ1stPerCtrller.h"
#include "LJFreeCtrller.h"
#include <assert.h>
#include <time.h>

float LJApplication::targetTpf = 16.6666f;

LJApplication::LJApplication(const char* chAPI = "OpenGL")
	:RenderManager(NULL),
	MaterialManager(NULL),
	TextureManager(NULL),
	m_pDevice(NULL),
	WindowWidth(800),
	WindowHeight(600),
	m_bStop(false),
	m_pWindow(NULL),
	m_Timer(NULL),
	m_pRenderer(NULL),
	m_OnDestroyFunc(NULL),
	m_OnStartFunc(NULL),
	m_OnUpdateFunc(NULL),
	m_OnDrawFunc(NULL),
	m_pFrameListeners(NULL)
{
	m_strAPI = new string(chAPI);
	m_RootNode = new LJNode();
	m_pFrameListeners = new FRAMELISTENERS();
	m_FirstPerCamera = new LJ1stPerCtrller();
	m_FreeCamera = new LJFreeCtrller();
}

LJApplication::~LJApplication(void)
{
	if(m_strAPI)
	{
		delete m_strAPI;
	}
	if(m_pFrameListeners)
	{
		FRAMELISTENERS::iterator it = m_pFrameListeners->begin();
		while(it != m_pFrameListeners->end())
		{
			delete *it;
			++it;
		}
	}
	if(m_RootNode)
	{
		delete m_RootNode;
	}
	if(m_Timer)
	{
		delete m_Timer;
	}
	if(m_FirstPerCamera)
	{
		delete m_FirstPerCamera;
	}
	if(m_FreeCamera)
	{
		delete m_FreeCamera;
	}
}

void LJApplication::Initialize()
{
	if(*m_strAPI != string("OpenGL"))
	{
		throw "Only support OpenGL";
	}

	m_pRenderer = new LJRenderer();
	if(LJFailed(m_pRenderer->CreateDevice(m_strAPI->c_str())))
	{
		throw "Create render device failed";
	}
	m_pDevice = m_pRenderer->GetDevice();
	if(m_pDevice == NULL)
	{
		throw "Retrieve device failed";
	}
	if(LJFailed(m_pDevice->Init(NULL, NULL, 0, 32, 24, true, WindowWidth, WindowHeight)))
	{
		throw "Device initialization failed";
	}
	MaterialManager = m_pDevice->GetMaterialManager();
	RenderManager = m_pDevice->GetRenderManager();
	TextureManager = m_pDevice->GetTextureManager();

	if(m_OnStartFunc)
		m_OnStartFunc(*this);
	if(m_Timer)
		m_Timer->Reset();
}

void LJApplication::Update()
{
	m_Timer->Update();
}

void LJApplication::SetOnDestroyCallback(LJOnDestroyListener func)
{
	m_OnDestroyFunc = func;
}

void LJApplication::SetOnStartCallback(LJOnStartListener func)
{
	m_OnStartFunc = func;
}

void LJApplication::SetOnUpdateCallback(LJOnUpdateListener func)
{
	m_OnUpdateFunc = func;
}

void LJApplication::SetOnDrawCallback(LJOnDrawListener func)
{
	m_OnDrawFunc = func;
}

void LJApplication::AddFrameListener(LJFrameListener *listener)
{
	if(listener)
	{
		m_pFrameListeners->push_back(listener);
	}
}

void LJApplication::CleanUp()
{
	if(m_OnDestroyFunc)
		m_OnDestroyFunc();

	if(m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

void LJApplication::Run(void)
{
	if(!m_Timer)
	{
		CleanUp();
		return;
	}
	while(!m_bStop)
	{
		float tpf = m_Timer->GetTimePerFrame();
		FRAMELISTENERS::iterator it = m_pFrameListeners->begin();

		while(it != m_pFrameListeners->end())
		{
			(*it)->FrameStarted(tpf, this);
			++it;
		}
		// render scene once
		RenderManager->ForcedFlushAll();

		it = m_pFrameListeners->begin();
		while(it != m_pFrameListeners->end())
		{
			(*it)->FrameEnded(tpf, this);
			++it;
		}

		Update();
		float sleepTime = targetTpf - tpf * 1000;
		if(sleepTime > 0)
		{
			LJSleep((DWORD)sleepTime);
		}
	}

	CleanUp();
}

LJApplication& LJApplication::GetApp(const char *chAPI)
{
	static LJApplication *gpSingleton = NULL;
	if(gpSingleton == NULL)
	{
		gpSingleton = new LJApplication(chAPI);
	}
	assert(gpSingleton);
	return *gpSingleton;
}

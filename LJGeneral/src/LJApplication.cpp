#include "LJApplication.h"
#include "LJFrameListener.h"
#include "LJ1stPerCtrller.h"
#include "LJFreeCtrller.h"
#include <assert.h>
#include <time.h>

LJApplication::LJApplication()
	:RenderManager(NULL),
	MaterialManager(NULL),
	TextureManager(NULL),
	m_pDevice(NULL),
	WindowWidth(800),
	WindowHeight(600),
	m_bStop(false),
	m_Timer(NULL),
	m_pRenderer(NULL),
	m_pFrameListeners(NULL),
	m_bInitialized(false)
{
	m_strAPI = new string("OpenGL");
	m_pFrameListeners = new FRAMELISTENERS();
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
	if(m_Timer)
	{
		delete m_Timer;
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

	SimpleInit();

	if(m_Timer)
		m_Timer->Reset();
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
	SimpleCleanUp();

	if(m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

void LJApplication::Run(void)
{
	if(!m_bInitialized)
	{
		Initialize();
		m_bInitialized = true;
	}
	if(!m_Timer)
	{
		CleanUp();
		return;
	}
	while(!m_bStop)
	{
		float tpf = m_Timer->GetTimePerFrame();
		// previous frame
		FRAMELISTENERS::iterator it = m_pFrameListeners->begin();
		while(it != m_pFrameListeners->end())
		{
			(*it)->FrameStarted(tpf, this);
			++it;
		}
		// render scene once
		RenderManager->ForcedFlushAll();
		// post frame
		it = m_pFrameListeners->begin();
		while(it != m_pFrameListeners->end())
		{
			(*it)->FrameEnded(tpf, this);
			++it;
		}

		float sleepTime = 16.6666 - tpf * 1000;
		if(sleepTime > 0)
		{
			LJSleep((DWORD)sleepTime);
		}
		m_Timer->Update();
	}

	CleanUp();
}

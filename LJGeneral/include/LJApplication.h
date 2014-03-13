#ifndef APPLICATION_H
#define APPLICATION_H

#include "LJGeneralHeaders.h"
#include "LJRenderManager.h"
#include "LJTextureManager.h"
#include "LJMaterialManager.h"
#include "LJRenderDevice.h"
#include "LJRenderer.h"
#include "LJNode.h"
#include "LJTimer.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

class LJApplication;
class LJFrameListener;
class LJ1stPerCtrller;
class LJFreeCtrller;

typedef void(*LJOnStartListener)(LJApplication& app);
typedef void(*LJOnDestroyListener)(void);
typedef void (*LJOnUpdateListener)(float tpf);
typedef void (*LJOnDrawListener)(void);

class _LJExport LJApplication
{
public:
	~LJApplication(void);
	static LJApplication& GetApp(const char *chAPI);

	void Run(void);
	void SetOnDestroyCallback(LJOnDestroyListener func);
	void SetOnStartCallback(LJOnStartListener func);
	void SetOnUpdateCallback(LJOnUpdateListener func);
	void SetOnDrawCallback(LJOnDrawListener func);
	void AddFrameListener(LJFrameListener *listener);
	void Initialize();

	LJRenderManager *RenderManager;
	LJMaterialManager *MaterialManager;
	LJRenderDevice *m_pDevice;
	int WindowWidth;
	int WindowHeight;
	bool m_bStop;
	LJNode *m_RootNode;
	HWND m_pWindow;
	LJTimer *m_Timer;
	LJ1stPerCtrller *m_FirstPerCamera;
	LJFreeCtrller *m_FreeCamera;
	typedef vector<LJFrameListener*> FRAMELISTENERS;
private:
	LJRenderer *m_pRenderer;
	LJOnDestroyListener m_OnDestroyFunc;
	LJOnStartListener m_OnStartFunc;
	LJOnUpdateListener m_OnUpdateFunc;
	LJOnDrawListener m_OnDrawFunc;
	string *m_strAPI;
	FRAMELISTENERS *m_pFrameListeners;
	void Update();
	void CleanUp();
	LJApplication(const char* chAPI);
	LJApplication(LJApplication& app);

	static float targetTpf;
};//~LJApplication

#endif

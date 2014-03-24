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

class _LJExport LJApplication
{
public:
	LJApplication();
	virtual ~LJApplication(void);
	void Run(void);
	void Stop() { m_bStop = true; }
	void AddFrameListener(LJFrameListener *listener);

protected:
	virtual void SimpleInit() = 0;
	virtual void SimpleCleanUp() = 0;

	LJRenderManager *RenderManager;
	LJMaterialManager *MaterialManager;
	LJTextureManager *TextureManager;
	LJRenderDevice *m_pDevice;
	int WindowWidth;
	int WindowHeight;
	bool m_bStop;
	LJTimer *m_Timer;
	typedef vector<LJFrameListener*> FRAMELISTENERS;

private:
	LJRenderer *m_pRenderer;
	string *m_strAPI;
	FRAMELISTENERS *m_pFrameListeners;
	bool m_bInitialized;

	void Initialize();
	void CleanUp();
};//~LJApplication

#endif

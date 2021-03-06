#ifndef LJOGLVCMANAGER_H
#define LJOGLVCMANAGER_H

#include "LJRenderDevice.h"
#include "LJRenderManager.h"
#include "LJOpenGL.h"
#include "LJRenderPass.h"

#include <vector>
using std::vector;
/* Forward Declaration */
class LJOGLVCache;

#define NUM_CACHES 10
class LJOGLRenderManager: public LJRenderManager {
public:
	LJOGLRenderManager(LJOpenGL *pLJOGL, FILE *pLog);
	~LJOGLRenderManager(void);
	// flush all caches
	HRESULT ForcedFlushAll(void);
	/* get render device */
	LJOpenGL* GetLJOGL(void) {return m_pLJOGL;}
	/* add a geometry to the render list */
	HRESULT Render(LJSpatial& scene);
	/* Create a view-port */
	LJRenderPass* CreateRenderPass();
	/* invalid id value */
	static const UINT MAX_ID = 65536;
	/* cache list type */
	typedef vector<LJOGLVCache*> VCACHES;
	typedef vector<LJRenderPass*> RenderPasses;
private:
	/* render device */
	LJOpenGL* m_pLJOGL;
	/* logging file */
	FILE* m_pLog;
	/* cache list */
	VCACHES *m_pVCaches;
	/* ViewPorts */
	RenderPasses *m_pViewPorts;
	/* number of viewports */
	int m_nNumViewPorts;
	/* inter render scene */
	HRESULT _Render(LJSpatial& scene);
};

#endif

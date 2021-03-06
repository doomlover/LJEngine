#ifndef LJVERTEXCACHEMANAGER
#define LJVERTEXCACHEMANAGER

class LJSpatial;
class LJRenderPass;

/*
 * Render Manager Interface
 */
class LJRenderManager {
public:
	LJRenderManager(void) {
	}

	virtual ~LJRenderManager(void) {
	}
	/* flush all meshes */
	virtual HRESULT ForcedFlushAll(void) = 0;
	/* render geometry to the render list */
	virtual HRESULT Render(LJSpatial& scene) = 0;
	/* Create a view-port */
	virtual LJRenderPass* CreateRenderPass() = 0;
};
#endif

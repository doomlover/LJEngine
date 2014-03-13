/*
 * OpenGL device render manager
 */
#include "LJOGLVCache.h"
#include "LJOGLRenderManager.h"
#include "LJUtil.h"
#include "LJSpatial.h"
#include "LJGeometry.h"
#include "LJNode.h"
#include "LJMoveController.h"
#include <cstdlib>

LJOGLRenderManager::LJOGLRenderManager(LJOpenGL *pLJOGL,
							   FILE *pLog)
:m_nNumViewPorts(0)
{
	m_pLog = pLog;
	m_pLJOGL = pLJOGL;
	m_pVCaches = new VCACHES();
	m_pViewPorts = new VIEWPORTS();
}

LJOGLRenderManager::~LJOGLRenderManager(void)
{
	if(m_pVCaches)
	{
		VCACHES::iterator it = m_pVCaches->begin();
		while(it != m_pVCaches->end())
		{
			delete *it;
			++it;
		}
		delete m_pVCaches;
		m_pVCaches = NULL;
	}
	if(m_pViewPorts)
	{
		VIEWPORTS::iterator it = m_pViewPorts->begin();
		while(it != m_pViewPorts->end())
		{
			delete *it;
			++it;
		}
		delete m_pViewPorts;
	}
}
/*
 * For every spatial in scene, if it is LJNode,
 * call _Render recursively. Else, if it is
 * LJGeometry, caches it in a geometry cacher
 * having the same material id.
 */
HRESULT LJOGLRenderManager::_Render(LJSpatial& scene)
{
	LJGeometry *g = dynamic_cast<LJGeometry*>(&scene);
	if(g)
	{
		// find a proper cache
		VCACHES::iterator it = m_pVCaches->begin();
		while(it != m_pVCaches->end())
		{
			// found a cache with the same material
			if((*it)->GetMaterial() == g->GetMaterial())
			{
				 if(LJFailed((*it)->Add(g)))
				 {
					 return LJ_FAIL;
				 }
				 return LJ_OK;
			}
			++it;
		}
		// not found, create new cache to store the geometry
		LJOGLVCache *newCache = new LJOGLVCache(m_pLJOGL, m_pLog);
		newCache->Add(g);
		newCache->SetMaterial(g->GetMaterial());
		m_pVCaches->push_back(newCache);
		return LJ_OK;
	}
	else
	{
		LJNode *n = dynamic_cast<LJNode*>(&scene);
		if(n)
		{
			LJNode::CHILDLIST childList = n->GetChildList();
			LJNode::CHILDLIST::iterator it = childList.begin();
			while(it != childList.end())
			{
				if( LJFailed( _Render(*(*it)) ) )
					return LJ_FAIL;
				++it;
			}
			return LJ_OK;
		}
	}
	return LJ_FAIL;
}

/*
 * add a geometry to the render list
 */
HRESULT LJOGLRenderManager::Render(LJSpatial& scene)
{
	HRESULT hr = LJ_OK;
	hr = _Render(scene);
	return hr;
}

HRESULT LJOGLRenderManager::ForcedFlushAll(void)
{
	m_pLJOGL->BeginRendering(true, true, true);
	VIEWPORTS::iterator it = m_pViewPorts->begin();
	
	while(it != m_pViewPorts->end())
	{

		// render view port scene
		m_pLJOGL->UseStage((*it)->mode, (*it)->stage);
		LJMoveController *camera = (*it)->Camera;
		if(camera)
		{
			m_pLJOGL->SetCamera(camera->GetRight(),
							camera->GetUp(),
							camera->GetDir(),
							camera->GetPos());
			m_pLJOGL->m_CamPos = camera->GetPos();
		}
		if( LJFailed( Render( *(*it)->GetScene() ) ) )
		{
			LJLog("LJOGLRenderManager", "Render failed");
			return LJ_FAIL;
		}

		// flush all caches
		VCACHES::iterator cache_it = m_pVCaches->begin();
		while(cache_it != m_pVCaches->end())
		{
			if( LJFailed( (*cache_it)->Flush() ) )
			{
				LJLog("LJOGLRenderManager", "Flush cache failed");
				return LJ_FAIL;
			}
			++cache_it;
		}

		// move to next view-port
		++it;
	}

	m_pLJOGL->EndRendering();
	return LJ_OK;
}

/*
 * Create a view-port
 */
LJViewPort* LJOGLRenderManager::CreateViewPort()
{
	if(m_nNumViewPorts < MAX_VIEWPORTS)
	{
		LJViewPort *vp = new LJViewPort();
		m_pViewPorts->push_back(vp);
		++m_nNumViewPorts;
		return vp;
	}
	LJLog("LJOGLRenderManager", "MAX NUMBER OF VIEWPORTS");
	return NULL;
}

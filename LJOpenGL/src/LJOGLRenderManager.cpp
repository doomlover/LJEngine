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
	m_pViewPorts = new RenderPasses();
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
		RenderPasses::iterator it = m_pViewPorts->begin();
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
		// empth cache
		LJOGLVCache *emptyCache = NULL;
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
			if((*it)->IsEmpty())
			{
				emptyCache = *it;
			}
			++it;
		}
		if(emptyCache)
		{
			emptyCache->SetMaterial(g->GetMaterial());
			emptyCache->Add(g);
			return LJ_OK;
		}
		//create new cache to store the geometry
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
	RenderPasses::iterator it = m_pViewPorts->begin();
	while(it != m_pViewPorts->end())
	{
		LJRenderPass *renderPass = *it;
		m_pLJOGL->SetPerspective(renderPass->fFov, renderPass->fAspectRatio, renderPass->fNear, renderPass->fFar);
		LJMoveController *camera = (*it)->Camera;
		if(camera)
		{
			m_pLJOGL->SetCamera(camera->GetRight(),
							camera->GetUp(),
							camera->GetDir(),
							camera->GetPos());
			m_pLJOGL->m_CamPos = camera->GetPos();
		}
		else
		{
			m_pLJOGL->SetCamera(LJMatrix4());
			m_pLJOGL->m_CamPos = LJVector3();
		}
		m_pLJOGL->SetViewport(renderPass->viewPort);
		m_pLJOGL->SetMode(renderPass->mode);
		m_pLJOGL->SetFramebuffer(renderPass->fb, renderPass->GetIndex());
		if( LJFailed( Render( *(*it)->GetScene() ) ) )
		{
			LJLog("LJOGLRenderManager", "Render failed");
			return LJ_FAIL;
		}
		m_pLJOGL->BeginRendering(true, true, true);
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
		m_pLJOGL->EndRendering();
		// move to next view-port
		++it;
	}
	return LJ_OK;
}

/*
 * Create a render pass
 */
LJRenderPass* LJOGLRenderManager::CreateRenderPass()
{
	if(m_nNumViewPorts < LJ_MAX_RENDER_PASSES)
	{
		LJRenderPass *renderPass = new LJRenderPass(m_nNumViewPorts);
		m_pViewPorts->push_back(renderPass);
		++m_nNumViewPorts;
		return renderPass;
	}
	LJLog("LJOGLRenderManager", "MAX NUMBER OF VIEWPORTS");
	return NULL;
}

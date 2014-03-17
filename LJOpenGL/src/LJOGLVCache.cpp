#include "LJOpenGL.h"
#include "LJOGLVCache.h"
#include "LJGeometry.h"

LJOGLVCache::LJOGLVCache(LJOpenGL *pDevice, FILE *pLog)
{
//	m_pLog = pLog; // Logging file is not used
	m_nMaterialID = LJ_MAX_ID;
	m_pDevice = pDevice;
	m_pGeometrys = new GEOMETRYS();
}

LJOGLVCache::~LJOGLVCache(void)
{
	if(m_pGeometrys)
	{
		delete m_pGeometrys;
	}
}

HRESULT LJOGLVCache::Add(LJGeometry* pGeometry)
{
	m_pGeometrys->push_back(pGeometry);
	return LJ_OK;
}

void LJOGLVCache::SetMaterial(int nMatID)
{
	if(m_nMaterialID != LJ_MAX_ID && m_nMaterialID != nMatID)
	{
		Flush(true);
	}
	m_nMaterialID = nMatID;
}

HRESULT LJOGLVCache::Flush(bool bUseShaders)
{
	if(m_pGeometrys->size() == 0)
		return LJ_OK;
	// Notice: bUseShaders is ignored for now. We always use shader.
	if(LJFailed(m_pDevice->ApplyMaterial(m_nMaterialID)))
	{
		return LJ_FAIL;
	}

	LJOGLVCache::GEOMETRYS::iterator it = m_pGeometrys->begin();
	while(it != m_pGeometrys->end())
	{
		if(LJFailed(m_pDevice->RenderGeometry(**it)))
		{
			return LJ_FAIL;
		}
		++it;
	}
	// remove all cached geometries
	m_pGeometrys->clear();
	return LJ_OK;
}

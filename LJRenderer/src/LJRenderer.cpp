/*
 * LJRenderer.cpp
 *
 *  Created on: 2013��7��28��
 *      Author: Liu
 */
#include <LJRenderer.h>
#include <LJUtil.h>
#include <cstring>
#ifdef _LJ_WIN32
	#include <Windows.h>
#endif
#ifdef _LJ_LINUX
	#include <dlfcn.h>
#endif
/*
 * Constructor
*/
LJRenderer::LJRenderer(void)
{
	m_pDevice = NULL;
	m_hDLL = NULL;
}
/*
 * Destructor
 */
LJRenderer::~LJRenderer(void)
{
	LJLog("LJRenderer", "destructor");
	Release();
}
/*
 * Release
 */
void LJRenderer::Release(void)
{
	HRESULT hr;
	if(m_pDevice)
	{
		RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
#ifdef _LJ_WIN32
		_ReleaseRenderDevice = (RELEASERENDERDEVICE) GetProcAddress(m_hDLL, "ReleaseRenderDevice");
#endif
#ifdef _LJ_LINUX
		_ReleaseRenderDevice = (RELEASERENDERDEVICE) dlsym(m_hDLL, "ReleaseRenderDevice");
#endif
		hr = _ReleaseRenderDevice(&m_pDevice);
		if(LJFailed(hr))
		{
			m_pDevice = NULL;
		}
	}
}//~Release

HRESULT LJRenderer::CreateDevice(const char *chAPI)
{
	LJLog("LJRenderer", "CreateDevice");

	HRESULT ret = false;

	if (strcmp(chAPI, "OpenGL") == 0) 
	{
#ifdef _LJ_WIN32
	m_hDLL = LoadLibrary("LJOpenGL.dll");
#endif
#ifdef _LJ_LINUX
	m_hDLL = dlopen("libLJOpenGL.so", RTLD_LAZY);
#endif
	}
	else {
		return LJ_FAIL;
	}

	if (m_hDLL == NULL) {
		LJLog("CreateDevice", "Load Dynamic Library Failed");
		return LJ_FAIL;
	}

	CREATERENDERDEVICE _CreateRenderDevice = 0;

	_CreateRenderDevice = (CREATERENDERDEVICE)LJGetProcAddress("CreateRenderDevice");
	if(!_CreateRenderDevice) {
		LJLog("LJRenderer", "CreateDevice Failed");
		return LJ_FAIL;
	}

	ret = _CreateRenderDevice(&m_pDevice);
	if(LJFailed(ret)) {
		fprintf(stderr, "%s\n", "CreateRenderDevice failed");
		m_pDevice = NULL;
		return LJ_FAIL;
	}

	return ret;
}//~CreateDevice

/* ============================================================ 
			        PRIVATE FUNCTIONS
 * ============================================================ */
void* LJRenderer::LJGetProcAddress(const char* chProcName)
{
#ifdef _LJ_WIN32
	return GetProcAddress(m_hDLL, chProcName);
#endif
#ifdef _LJ_LINUX
	return dlsym(m_hDLL, chProcName);
#endif
}




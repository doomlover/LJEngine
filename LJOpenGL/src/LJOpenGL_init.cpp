/*
 * LJOpenGL_init.cpp
 *
 *  Created on: 2013��7��28��
 *      Author: Liu
 */

#include "LJOpenGL.h"

HRESULT CreateRenderDevice(LJRenderDevice **pDevice)
{
	if(!(*pDevice))
	{
		*pDevice = LJOpenGL::GetInstance();
		return LJ_OK;
	}
	return LJ_FAIL;
}

HRESULT ReleaseRenderDevice(LJRenderDevice **pDevice)
{
	if(!*pDevice)
	{
		return LJ_FAIL;
	}
	delete *pDevice;
	*pDevice = NULL;
	return LJ_OK;
}


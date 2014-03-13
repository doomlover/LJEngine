/*
 * LJRenderer.h
 *
 *  Created on: 2013.7.28
 *      Author: Liu
 */

#ifndef LJRENDERER_H_
#define LJRENDERER_H_
#include "LJRenderDevice.h"
class LJRenderer
{
public :
	LJRenderer(void);
	~LJRenderer(void);

	HRESULT CreateDevice(const char *chAPI);
	void Release(void);
	LPLJRENDERDEVICE GetDevice(void) {return m_pDevice;}

private:
	LJRenderDevice *m_pDevice;
	HMODULE m_hDLL;

	void* LJGetProcAddress(const char* chProcName);
};
typedef LJRenderer *LPLJRENDERER;

#endif /* LJRENDERER_H_ */

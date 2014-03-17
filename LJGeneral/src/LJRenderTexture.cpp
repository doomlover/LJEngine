/*
 * LJRenderTexture.cpp
 *
 *  Created on: Mar 14, 2014
 *      Author: liu
 */
#include "LJRenderTexture.h"

LJRenderTexture::LJRenderTexture(UINT w, UINT h, TextureFormat fmt)
:m_nSizeW(w), m_nSizeH(h), m_Fmt(fmt), m_pTexture(NULL), m_TexID(LJ_MAX_ID)
{
}

LJRenderTexture::LJRenderTexture(UINT w, UINT h, TextureFormat fmt,
								 UINT id, 
								 LJTexture *tex):
m_nSizeW(w), m_nSizeH(h), m_Fmt(fmt), m_TexID(id), m_pTexture(tex)
{
	m_pTexture->SetNeedUpdate(true);
}

void LJRenderTexture::SetFormat(TextureFormat fmt)
{
	if(fmt != LJ_INVALID_FORMAT)
	{
		m_Fmt = fmt;
	}
	LJLog("Warning", "Set invalid value as format");
}

TextureFormat LJRenderTexture::GetFormat() const
{
	return m_Fmt;
}

void LJRenderTexture::SetSize(UINT w, UINT h)
{
	m_nSizeW = w;
	m_nSizeH = h;
	m_pTexture->SetNeedUpdate(true);
}

HRESULT LJRenderTexture::GetSize(UINT *w, UINT *h) const
{
	if(!w || !h)
		return LJ_FAIL;
	*w = m_nSizeW;
	*h = m_nSizeH;
	return LJ_OK;
}

const LJTexture* LJRenderTexture::GetTexture(UINT *id) const
{
	if(id)
		*id = m_TexID;
	return m_pTexture;
}

LJTexture* LJRenderTexture::GetTexture(UINT *id)
{
	if(id)
		*id = m_TexID;
	return m_pTexture;
}

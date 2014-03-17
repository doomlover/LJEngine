#ifndef LJRENDERTEXTURE_H
#define LJRENDERTEXTURE_H

#include "LJGeneralHeaders.h"
#include "LJTexture.h"

class _LJExport LJRenderTexture
{
	UINT m_nSizeW;
	UINT m_nSizeH;
//	TextureFormat m_interFmt;
	TextureFormat m_Fmt;
	LJTexture *m_pTexture;
	UINT m_TexID;
	//void init();
public:
	LJRenderTexture(UINT w, UINT h, TextureFormat fmt, UINT id, LJTexture *tex);
	LJRenderTexture(UINT w, UINT h, TextureFormat fmt);

	void SetFormat(TextureFormat fmt);
	TextureFormat GetFormat() const;

	void SetSize(UINT w, UINT h);
	HRESULT GetSize(UINT *w, UINT *h) const;

	const LJTexture* GetTexture(UINT *id) const;
	LJTexture* GetTexture(UINT *id);
};//~LJRenderTexture

#endif

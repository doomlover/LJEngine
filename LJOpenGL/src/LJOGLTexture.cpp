#include <GL/glew.h>
#include <LJUtil.h>
#include <LJOGLTexture.h>
#include "LJImageManager.h"
#include <FreeImage.h>
#include <cstdio>

LJOGLTexture::LJOGLTexture(LJTexture *pTex, LJImage *pImg)
:m_Tex(pTex),
 m_Img(pImg)
{
}

LJOGLTexture::~LJOGLTexture(void)
{
}

HRESULT LJOGLTexture::SetAlphaKey(UCHAR R, UCHAR G, UCHAR B, UCHAR A)
{
	FIBITMAP* dib = m_Img->GetData();
	if(dib == NULL) {
		return LJ_FAIL;
	}

	UINT bpp = m_Img->GetBPP();
	if(bpp != 32) {
		return LJ_INVALID_TEXTURE_FORMAT;
	}
	// the new color
	UCHAR _R = R, _G = G, _B = B, _A = A;
	if(A <= 0) {
		_R = _G = _B = 0;
	}
	// the target color
	DWORD tarColor = MakeOGLColor(R, G, B, 255);

	UINT width = m_Img->GetWidth();
	UINT height = m_Img->GetHeight();
	UINT pitch = FreeImage_GetPitch(dib);

	BYTE* bits = static_cast<BYTE*>(m_Img->GetBits());
	for(UINT j = 0; j < height; ++j) {
		BYTE* pixel = bits;
		for(UINT i = 0; i < width; ++i) {
			if(*(reinterpret_cast<DWORD*>(pixel)) == tarColor) {
				pixel[FI_RGBA_RED] = _R;
				pixel[FI_RGBA_GREEN] = _G;
				pixel[FI_RGBA_BLUE] = _B;
				pixel[FI_RGBA_ALPHA] = _A;
			}
			pixel += 4;
		}
		bits += pitch;
	}

	return LJ_OK;
}

HRESULT LJOGLTexture::SetTransparency(UCHAR alpha)
{
	FIBITMAP *dib = m_Img->GetData();
	if(m_Img->GetBPP() == 24)
	{
		return LJ_INVALID_TEXTURE_FORMAT;
	}
	UINT width, height, pitch;
	BYTE *bits;
	// pixel width
	width = m_Img->GetWidth();
	// pixel height
	height = m_Img->GetHeight();
	// 32-bit aligned byte width
	pitch = FreeImage_GetPitch(dib);
	// Image data start position
	bits = static_cast<BYTE*>(m_Img->GetBits());
	for(UINT h = 0; h < height; ++h)
	{// For every row
		// Get row pixels
		BYTE *pixel = bits;
		for(UINT w = 0; w < width; ++w)
		{// For every pixel, change alpha
			if(pixel[FI_RGBA_ALPHA] > alpha)
			{
				pixel[FI_RGBA_ALPHA] = alpha;
			}
			// Go next pixel
			pixel += 4;
		}
		// Go next row
		bits += pitch;
	}
	return LJ_OK;
}

void LJOGLTexture::Update()
{
	DWORD num;
	LJCOLOR *pClrKeys = m_Tex->GetColorKeys(&num);
	for (DWORD i = 0; i < num; ++i)
	{
		HRESULT res = SetAlphaKey((char) (pClrKeys[i].fR * 255),
				(char) (pClrKeys[i].fG * 255), (char) (pClrKeys[i].fB * 255),
				(char) (pClrKeys[i].fA * 255));
		if (LJFailed(res))
		{
			throw "LJOGLTexture, ERROR, AN COLOR KEY CANT BE SET";
			return;
		}
	}
	if(m_Tex->GetAlpha() < 1.0f)
	{
		if (!SetTransparency((char) (m_Tex->GetAlpha() * 255)))
		{
			throw "LJOGLTexture, ERROR, SET TRANSPARENT FAILED";
		}
	}
}


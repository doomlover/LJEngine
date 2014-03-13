#include <GL/glew.h>
#include "LJImageManager.h"
#include <FreeImage.h>

LJImage::LJImage()
:m_pData(NULL),
 m_nWidth(0),
 m_nHeight(0),
 m_nFormat(0),
 m_nInterFormat(0),
 m_nBPP(0),
 m_bNeedUpdate(false),
 m_pBits(NULL)
{
}

LJImageManager::LJImageManager()
{
}

LJImageManager::~LJImageManager(void)
{
	// free all image data
	IMAGES::iterator it = m_Images.begin();
	while(it != m_Images.end())
	{
		FIBITMAP *data = it->second.m_pData;
		if(data)
		{
			FreeImage_Unload(data);
		}
		++it;
	}
	m_Images.clear();
}
LJImage& LJImageManager::CreateImage(const char* chImage)
{
	if(!chImage)
	{
		throw "Invalid image file path";
	}
	IMAGES::iterator it = m_Images.find(string(chImage));
	// if not found
	if(it == m_Images.end())
	{
		LJImage img;
		// store the file path
		img.m_strName.assign(chImage);
		// load the image file
		LoadImage(img);
		// cache the image object
		m_Images[img.m_strName] = img;
		// return to user
		return m_Images[img.m_strName];
	}
	// if found
	return it->second;
}

bool LJImageManager::DeleteImage(const char* chImage)
{
	IMAGES::iterator it = m_Images.find(string(chImage));
	if(it != m_Images.end())
	{
		m_Images.erase(it);
		return true;
	}
	return false;
}

HRESULT LJImageManager::LoadImage(LJImage& img)
{
	FIBITMAP *dib = NULL;
	const char* file = img.m_strName.c_str();
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file, 0);
	if(fif == FIF_UNKNOWN) {
		fif = FreeImage_GetFIFFromFilename(file);
	}
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, file, 0);
		FREE_IMAGE_TYPE fit = FreeImage_GetImageType(dib);
		if(fit != FIT_BITMAP) {
			LJLog("LJOpenGL", "Only support bitmap for now");
			return LJ_INVALID_TEXTURE_FORMAT;
		}
	}
	if(!dib)
	{
		return LJ_INVALID_TEXTURE_FORMAT;
	}
	UINT bpp = FreeImage_GetBPP(dib);
	if(bpp != 24 && bpp != 32)
	{
		FreeImage_Unload(dib);
		return LJ_INVALID_TEXTURE_FORMAT;
	}
	if(bpp == 24)
	{
		img.m_nFormat = GL_BGR;
		img.m_nInterFormat = GL_RGB8;
	}
	else
	{
		img.m_nFormat = GL_BGRA;
		img.m_nInterFormat = GL_RGBA8;
	}
	img.m_pData = dib;
	img.m_pBits = FreeImage_GetBits(dib);
	img.m_nWidth = FreeImage_GetWidth(dib);
	img.m_nHeight = FreeImage_GetHeight(dib);
	img.m_nBPP = bpp;
	img.m_bNeedUpdate = true;
	return LJ_OK;
}

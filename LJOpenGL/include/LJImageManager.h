#ifndef LJIMAGEMANAGER_H_
#define LJIMAGEMANAGER_H_

#include "LJGeneralHeaders.h"
#include <FreeImage.h>
#include <string>
using std::string;
#include <map>
using std::map;
/*
 * Class to storing a newly loaded
 * FreeImage bitmap
 */
class LJImage
{
	friend class LJImageManager;
public:
	LJImage();
	~LJImage(void){};
	const FIBITMAP*	GetData()const		{return m_pData;}
	FIBITMAP* 		GetData()			{return m_pData;}

	const void* GetBits()const		{return m_pBits;}
	void*		GetBits()			{return m_pBits;}

	int 		GetWidth()const		{return m_nWidth;}
	void 		SetWidth(int w)		{m_nWidth = w;}

	int 		GetHeight()const	{return m_nHeight;}
	void		SetHeight(int h)	{m_nHeight = h;}

	UINT 		GetFormat()const	{return m_nFormat;}
	void		SetFormat(UINT format){m_nFormat = format;}

	UINT 		GetInterFormat()const		{return m_nInterFormat;}
	void		SetInterFormat(UINT format)	{m_nInterFormat = format;}

	void 		SetNeedUpdate(bool bNeed) {m_bNeedUpdate = bNeed;}
	bool 		IsNeedUpdate() 		{return m_bNeedUpdate;}

	int 		GetBPP() const		{return m_nBPP;}
	void 		SetBPP(int bpp)		{m_nBPP = bpp;}
private:
	FIBITMAP *m_pData;
	int m_nWidth;
	int m_nHeight;
	UINT m_nFormat;
	UINT m_nInterFormat;
	string m_strName;
	int m_nBPP;
	bool m_bNeedUpdate;
	void *m_pBits;
};//~LJImage

typedef map<string, LJImage> IMAGES;

/*
 * FreeImage bitmap manager
 */
class LJImageManager
{
	IMAGES m_Images;
	HRESULT LoadImage(LJImage& img);
public:
	LJImageManager();
	~LJImageManager(void);
	LJImage& CreateImage(const char* chImage);
	bool DeleteImage(const char* chImage);
};//~ LJImageManager


#endif /* LJIMAGEMANAGER_H_ */

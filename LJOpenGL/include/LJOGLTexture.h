#ifndef LJOGLTEXTURE_H_
#define LJOGLTEXTURE_H_

#include <LJTexture.h>
#include <FreeImage.h>
/* Forward Declaration */
class LJImage;
/*
 * FreeImage implemented texture helper class
 */
class LJOGLTexture
{
public:
	LJOGLTexture(LJTexture *tex, LJImage *img);
	~LJOGLTexture(void);
	// update image data
	void Update();
private:
	LJTexture *m_Tex;
	LJImage *m_Img;

	// replace alpha value of pixel having the same RGB value
	HRESULT SetAlphaKey(UCHAR R, UCHAR G, UCHAR B, UCHAR A);
	// set the total alpha value
	HRESULT SetTransparency(UCHAR alpha);
};


#endif /* LJOGLTEXTURE_H_ */

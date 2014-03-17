/*
 * LJOGLTextureManager.h
 *
 *  Created on: Mar 14, 2014
 *      Author: liu
 */

#ifndef LJOGLTEXTUREMANAGER_H_
#define LJOGLTEXTUREMANAGER_H_

#include "LJTextureManager.h"
#include <vector>
using std::vector;

class LJTexture;
/*
 * Manager of all textures used by device
 */
class LJOGLTextureManager : public LJTextureManager
{
	typedef vector<LJTexture*> Textures;

	Textures m_Textures;
	UINT m_nNumTextures;
public:
	LJOGLTextureManager():m_nNumTextures(0){}

	~LJOGLTextureManager(void);

	UINT AddTexture(const LJTexture& tex);

	LJTexture* CreateTexture(UINT *id);

	LJTexture* GetTexture(UINT id);
};

#endif /* LJOGLTEXTUREMANAGER_H_ */

#ifndef LJTEXTUREMANAGER_H
#define LJTEXTUREMANAGER_H

#include "LJGeneralHeaders.h"

class LJTexture;
/*
 * Interface of texture manager
 */
class LJTextureManager
{
public:
	virtual ~LJTextureManager(void){}
	/* Add a user created texture. A copy is generated */
	virtual UINT AddTexture(const LJTexture& tex) = 0;
	/* return a newly created texture which is owned by manager */
	virtual LJTexture* CreateTexture(UINT *id) = 0;
	/* Retrieve the texture by the specified id */
	virtual LJTexture* GetTexture(UINT id) = 0;
};//~LJTextureManager;
#endif

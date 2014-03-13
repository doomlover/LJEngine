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
	/*
	 * Return a newly created texture and the
	 * id to caller. Users should never delete
	 * the returned texture by themselves.
	 */
	virtual LJTexture* CreateTexture(const char* imageFile, UINT *id) = 0;
	/*
	 * Retrieve the texture which has the specific id
	 */
	virtual LJTexture* GetTexture(UINT id) = 0;
};//~LJTextureManager;
#endif

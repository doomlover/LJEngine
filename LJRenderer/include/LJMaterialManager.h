#ifndef LJMATERIALMANAGER_H
#define LJMATERIALMANAGER_H

#include "LJGeneralHeaders.h"

class LJMaterial;
class LJTextureManager;

class LJMaterialManager
{
public:
	virtual ~LJMaterialManager(void){}
	/* Create an empty material */
	virtual LJMaterial* CreateMaterial(UINT *id) = 0;
	/* Create a material from effect file */
	virtual UINT CreateMaterial(const char* effectFile, LJTextureManager *texMgr) = 0;
	/* Get material by id */
	virtual LJMaterial* GetMaterial(UINT id) = 0;
};//~LJMaterialManager

#endif

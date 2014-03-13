#ifndef LJOGLMATERIALMANAGER_H_
#define LJOGLMATERIALMANAGER_H_

#include "LJMaterialManager.h"
#include "LJMaterial.h"

class LJOGLMaterialManager : public LJMaterialManager
{
public:
	LJOGLMaterialManager();

	~LJOGLMaterialManager(void);
	/* Return a newly created material and its id */
	LJMaterial* CreateMaterial(UINT *id);
	/* Create a new material from a effect file and return its id */
	UINT CreateMaterial(const char* effectFile);
	/* Retrieve the material which has the specified id */
	LJMaterial* GetMaterial(UINT id);
	/* Material container type */
	typedef vector<LJMaterial*> LJMATERIALS;
private:
	LJMATERIALS m_Materials;	// material container
	UINT m_nNumMaterials;		// number of materials
};//~LJMaterialManager



#endif /* LJMATERIAL_H_ */

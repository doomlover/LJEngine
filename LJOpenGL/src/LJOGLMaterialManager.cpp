#include "LJOGLMaterialManager.h"
#include "LJEffectFileParser.h"

LJOGLMaterialManager::LJOGLMaterialManager()
:m_nNumMaterials(0)
{

}

LJOGLMaterialManager::~LJOGLMaterialManager(void)
{
	LJMATERIALS::iterator it = m_Materials.begin();
	while(it != m_Materials.end())
	{
		delete *it;
		++it;
	}
}

LJMaterial* LJOGLMaterialManager::CreateMaterial(UINT *id)
{
	LJMaterial* newMat = new LJMaterial();
	m_Materials.push_back(newMat);
	*id = m_nNumMaterials;
	m_nNumMaterials++;
	return newMat;
}

UINT LJOGLMaterialManager::CreateMaterial(const char* effectFile, LJTextureManager *texMgr)
{
	if(!effectFile)
		throw "Invalid effect file path";
	LJEffectFileParser parser(this, texMgr);
	try{
		return parser.Parse(effectFile);
	}catch(const char* error)
	{
		LJLog("LJOGLMaterialManager", error);
	}
	return LJ_MAX_ID;
}

LJMaterial* LJOGLMaterialManager::GetMaterial(UINT id)
{
	if(id < m_nNumMaterials)
	{
		return m_Materials[id];
	}
	return NULL;
}




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

UINT LJOGLMaterialManager::CreateMaterial(const char* effectFile)
{
	if(!effectFile)
		throw "Invalid effect file path";
	LJMaterial *newMat;
	UINT id;
	newMat = CreateMaterial(&id);
	LJEffectFileParser parser(effectFile);
	try{
		parser.Parse(*newMat);
	}catch(const char* error)
	{
		LJLog("LJOGLMaterialManager", error);
	}
	return id;
}

LJMaterial* LJOGLMaterialManager::GetMaterial(UINT id)
{
	if(id < m_nNumMaterials)
	{
		return m_Materials[id];
	}
	return NULL;
}




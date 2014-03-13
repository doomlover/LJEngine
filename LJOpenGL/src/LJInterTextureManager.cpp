#include <GL/glew.h>
#include "LJInterTextureManager.h"

LJInterTextureManager::LJInterTextureManager(){}

LJInterTextureManager::~LJInterTextureManager(void)
{
	Clear();
}

int LJInterTextureManager::GetTexObj(int texId)
{
	TEXOBJMAP::iterator it = m_TexObjs.find(texId);
	// found
	if(it != m_TexObjs.end())
	{
		return it->second;
	}
	return -1;
}

void LJInterTextureManager::SetTexObj(int texId)
{
	TEXOBJMAP::iterator it = m_TexObjs.find(texId);

	if(it == m_TexObjs.end())
	{
		m_TexObjs[texId] = texId;
	}
}

void LJInterTextureManager::Clear()
{
	TEXOBJMAP::iterator it = m_TexObjs.begin();
	while(it != m_TexObjs.end())
	{
		GLuint texObj = it->second;
		glDeleteTextures(1, &texObj);
		++it;
	}
	m_TexObjs.clear();
}

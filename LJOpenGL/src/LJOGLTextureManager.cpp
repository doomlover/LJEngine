/*
 * LJOGLTextureManager.cpp
 *
 *  Created on: Mar 14, 2014
 *      Author: liu
 */
#include "LJOGLTextureManager.h"
#include "LJTexture.h"

LJOGLTextureManager::~LJOGLTextureManager(void)
{
	Textures::iterator it = m_Textures.begin();
	while(it != m_Textures.end())
	{
		delete *it;
		++it;
	}
}

UINT LJOGLTextureManager::AddTexture(const LJTexture& tex)
{
	LJTexture *newTex = new LJTexture(tex);
	m_Textures.push_back(newTex);
	++m_nNumTextures;
	return m_nNumTextures-1;
}

LJTexture* LJOGLTextureManager::CreateTexture(UINT *id)
{
	LJTexture *newTex = new LJTexture();
	m_Textures.push_back(newTex);
	++m_nNumTextures;
	if(id)
	{
		*id = m_nNumTextures-1;
	}
	return newTex;
}

LJTexture* LJOGLTextureManager::GetTexture(UINT id)
{
	if(id < m_nNumTextures)
	{
		return m_Textures[id];
	}
	return NULL;
}


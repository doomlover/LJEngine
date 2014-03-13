#include "LJGeometry.h"
#include "LJMesh.h"
#include <cstdio>
LJGeometry::LJGeometry()
	:m_pMesh(NULL),
	 m_nMaterial(-1),
	 m_pAdditionalMatParams(NULL)
{
}
/*
 * LJGeometry has a member LJMesh, but
 * does not own it.
 */
LJGeometry::~LJGeometry(void)
{
	LJLog("~LJGeometry", "");

	if(m_pAdditionalMatParams)
	{
		delete m_pAdditionalMatParams;
	}
}

void LJGeometry::SetMesh(LJMesh *pMesh)
{
	m_pMesh = pMesh;
}

void LJGeometry::SetMaterial(int nMaterial)
{
	m_nMaterial = nMaterial;
}

LJMesh* LJGeometry::GetMesh()
{
	return m_pMesh;
}

const LJMesh* LJGeometry::GetMesh() const
{
	return m_pMesh;
}

int LJGeometry::GetMaterial() const
{
	return m_nMaterial;
}

void LJGeometry::SetAdditionalMatParam(const LJMaterial::LJMatParam& param)
{
	if(!m_pAdditionalMatParams)
	{
		m_pAdditionalMatParams = new LJMaterial::LJMatParams();
	}
	(*m_pAdditionalMatParams)[param.Name()] = param;
}
LJMaterial::LJMatParams* LJGeometry::GetAdditionalMatParams()
{
	return m_pAdditionalMatParams;
}

const LJMaterial::LJMatParams* LJGeometry::GetAdditionalMatParams()const
{
	return m_pAdditionalMatParams;
}

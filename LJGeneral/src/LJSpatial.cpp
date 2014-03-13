#include "LJSpatial.h"
#include "LJUtil.h"
#include <cstdio>

LJSpatial::LJSpatial()
:m_bUpdateLocal(false),
m_pParent(NULL)
{
	m_pTranslate = new LJVector3();
	m_pQuat = new LJQuat();
	m_pScaMatr = new LJMatrix3();
	m_pWorldMatrix = new LJMatrix4();
	m_pName = new string();
}

LJSpatial::~LJSpatial(void)
{
	LJLog("~LJSpatial", "");
	if(m_pTranslate)
	{
		delete m_pTranslate;
	}
	if(m_pQuat)
	{
		delete m_pQuat;
	}
	if(m_pScaMatr)
	{
		delete m_pScaMatr;
	}
	if(m_pWorldMatrix)
	{
		delete m_pWorldMatrix;
	}
	if(m_pName)
	{
		delete m_pName;
	}
}

void LJSpatial::SetLocalRotation(float rx, float ry, float rz)
{
	*m_pQuat = LJQuat(LJVector3(rx, ry, rz));
	m_bUpdateLocal = true;
}

void LJSpatial::SetLocalRotation(const LJVector3& v, float angle)
{
	LJVector3 _v = ljm::normalize(v);
	float a2 = angle/2.0f;
	float sina2 = sin(a2);
	float cosa2 = cos(a2);
	_v *= sina2;
	*m_pQuat = LJQuat(cosa2, _v);
	m_bUpdateLocal = true;
}

void LJSpatial::SetLocalScale(float kx, float ky, float kz)
{
	*m_pScaMatr = ljm::S(kx, ky, kz);
	m_bUpdateLocal = true;
}

void LJSpatial::SetLocalScale(const LJVector3& v, float k)
{
	*m_pScaMatr = ljm::S(v, k);
	m_bUpdateLocal = true;
}

void LJSpatial::SetLocalTranslation(float tx, float ty, float tz)
{
	*m_pTranslate = LJVector3(tx, ty, tz);
	m_bUpdateLocal = true;
}

void LJSpatial::UpdateLocalMatrix()
{
	if (m_bUpdateLocal)
	{
		// 3x3 local-rotation matrix
		LJMatrix3 rot33 = ljm::R(*m_pQuat);
		// local 33 matrix
		LJMatrix3 localMat3 = *m_pScaMatr * rot33;
		// local 44 matrix
		*m_pWorldMatrix = LJMatrix4(localMat3);
		(*m_pWorldMatrix)[3][0] = m_pTranslate->x;
		(*m_pWorldMatrix)[3][1] = m_pTranslate->y;
		(*m_pWorldMatrix)[3][2] = m_pTranslate->z;

		m_bUpdateLocal = false;
	}
}

void LJSpatial::SetTranslation(float tx, float ty, float tz)
{
	UpdateLocalMatrix();
	(*m_pWorldMatrix)[3][0] += tx;
	(*m_pWorldMatrix)[3][1] += ty;
	(*m_pWorldMatrix)[3][2] += tz;
}

void LJSpatial::SetRotation(float rx, float ry, float rz)
{
	UpdateLocalMatrix();
	LJQuat aQuat(LJVector3(rx, ry, rz));
	*m_pWorldMatrix = LJMatrix4(ljm::R(aQuat)) * *m_pWorldMatrix;
}
void LJSpatial::SetRotation(const LJVector3& v, float angle)
{
	UpdateLocalMatrix();
	*m_pWorldMatrix = LJMatrix4(ljm::R(v, angle)) * *m_pWorldMatrix;
}
void LJSpatial::SetScale(float kx, float ky, float kz)
{
	UpdateLocalMatrix();
	*m_pWorldMatrix = LJMatrix4(ljm::S(kx, ky, kz)) * *m_pWorldMatrix;
}
void LJSpatial::SetScale(const LJVector3& v, float k)
{
	UpdateLocalMatrix();
	*m_pWorldMatrix = LJMatrix4(ljm::S(v, k)) * *m_pWorldMatrix;
}

LJMatrix4 LJSpatial::GetWorldMatrix()
{
	UpdateLocalMatrix();
	return *m_pWorldMatrix;
}

void LJSpatial::SetName(const char* chName)
{
	if(chName)
	{
		if(!m_pName)
		{
			m_pName = new string();
		}
		m_pName->assign(chName);
	}
}

const char* LJSpatial::GetName() const
{
	return m_pName->c_str();
}

const LJNode* LJSpatial::GetParent() const
{
	return m_pParent;
}

LJNode* LJSpatial::GetParent()
{
	return m_pParent;
}

void LJSpatial::SetParent(LJNode* parent)
{
	m_pParent = parent;
}

#include <LJFreeCtrller.h>
#include <LJUtil.h>
#include <cstring>

LJFreeCtrller::~LJFreeCtrller(void)
{
	LJLog("LJFreeCtrller", "~LJFreeCtrller");
}

void LJFreeCtrller::Update(float fElapsedtime)
{
	m_fAngX += m_fPitchSpeed * fElapsedtime;
	m_fAngY += m_fYawSpeed * fElapsedtime;
	m_fAngZ += m_fRollSpeed * fElapsedtime;
	// Set the velocity. Use old dir to update the moving distance
	*m_v3Velocity = *m_v3Dir*m_fThrust*fElapsedtime;
	// Calculate the new position
	*m_v3Pos += *m_v3Velocity;
	// Calculate the new local axes
	RecalculateAxes();
}//~RecalculateAxes

void LJFreeCtrller::AddRotationSpeed(float fX, float fY, float fZ)
{
	m_fPitchSpeed += fX;
	m_fYawSpeed += fY;
	m_fRollSpeed += fZ;
}//~AddRotationSpeed

void LJFreeCtrller::SetRotationSpeed(float fX, float fY, float fZ)
{
	m_fPitchSpeed = fX;
	m_fYawSpeed = fY;
	m_fRollSpeed = fZ;
}//~SetRotationSpeed

void LJFreeCtrller::SetRotation(float fAngX, float fAngY, float fAngZ)
{
	m_fAngX = fAngX;
	m_fAngY = fAngY;
	m_fAngZ = fAngZ;
	RecalculateAxes();
}//~SetRotation
  
void LJFreeCtrller::SetPos(const LJVector3& v3Pos)
{
	memcpy(m_v3Pos, &v3Pos, sizeof(LJVector3));
}//~SetPos
void LJFreeCtrller::SetRight(LJVector3& v3Right)
{
	memcpy(m_v3Right, &v3Right, sizeof(LJVector3));
}//~SetRight
void LJFreeCtrller::SetUp(LJVector3& v3Up)
{
	memcpy(m_v3Up, &v3Up, sizeof(LJVector3));
}//~SetUp
void LJFreeCtrller::SetDir(LJVector3& v3Dir)
{
	memcpy(m_v3Dir, &v3Dir, sizeof(LJVector3));
}//~SetDir

#include <LJ1stPerCtrller.h>
#include <LJUtil.h>
#include <LJMath.h>
#include <cstring>

using namespace ljm;

LJ1stPerCtrller::~LJ1stPerCtrller(void)
{
}

void LJ1stPerCtrller::Update(float fElapTime)
{
	// update angles
	m_fAngX += fElapTime * m_fPitchSpeed;
	m_fAngY += fElapTime * m_fYawSpeed;
	m_fAngZ += fElapTime * m_fRollSpeed;

	*m_v3Velocity = *m_v3Dir * m_fSpeed * fElapTime;
	vec3f v3Slide = *m_v3Right * m_fSlide * fElapTime;
	*m_v3Pos += *m_v3Velocity + v3Slide;
	RecalculateAxes();
}

void LJ1stPerCtrller::SetRotation(float fAngX, float fAngY, float fAngZ)
{
	m_fAngX = fAngX;
	m_fAngY = fAngY;
	m_fAngZ = fAngZ;
	RecalculateAxes();
}//~SetRotation

void LJ1stPerCtrller::SetPos( const vec3f& v3Pos)
{
	memcpy(m_v3Pos, &v3Pos, sizeof(vec3f));
}//~SetPos
void LJ1stPerCtrller::SetRight( const vec3f& v3Right)
{
	memcpy(m_v3Right, &v3Right, sizeof(vec3f));
}//~SetRight
void LJ1stPerCtrller::SetUp( const vec3f& v3Up)
{
	memcpy(m_v3Up, &v3Up, sizeof(vec3f));
}//~SetUp
void LJ1stPerCtrller::SetDir( const vec3f& v3Dir)
{
	memcpy(m_v3Dir, &v3Dir, sizeof(vec3f));
}//~SetDir

void LJ1stPerCtrller::GetRotation(float *fAngX, float *fAngY, float *fAngZ) const
{
	if(fAngX) *fAngX = m_fAngX;
	if(fAngY) *fAngY = m_fAngY;
	if(fAngZ) *fAngZ = m_fAngZ;
}


/* =================================
 *           Private Functions
 * =================================*/
/*
 * ���ȶ�Y����ת��Yaw��������ת����Ȼ��
 * ����תʩ�ӵ������������ϣ��Ա���ת��X��
 * Ϊ��������X�ᣨPitch���ϵ���ת����
 * ����תʩ�ӵ������������ϡ����任������
 * ������λ��������ϵ�����?
 * �����������ת��Ĺ���У���ʹ����Ԫ����
 * ��ɽ��ԭ����ÿ����׼���ϵ���ת�ļ���
 * ������Ӱ����һ����ת��ʹ�õ��ᣬ���ڵ�һ
 * �˳�������תҪ����ת��������ᣬ��Ԫ��
 * ����������һ����Ҫ��
*/
void LJ1stPerCtrller::RecalculateAxes(void)
{
	static float f2PI = 3.1415926f*2.0f;
	// limited to not beyong [-80, +80]
	float rad80 = static_cast<float>(DegreeToRadian(80.f));
	if(m_fAngX > rad80) {
		m_fAngX = rad80;
	}
	else if(m_fAngX < -rad80) {
		m_fAngX = -rad80;
	}
	// limited to not beyond 2PI
	if(m_fAngY > f2PI) {
		m_fAngY -= f2PI;
	}
	else if(m_fAngY < -f2PI) {
		m_fAngY += f2PI;
	}
	// Every time recalculating , align to world space first
	*m_v3Up = vec3f(0, 1, 0);
	*m_v3Right = vec3f(1, 0, 0);
	*m_v3Dir = vec3f(0, 0, 1);
	// then firstly, rotate along the Up axis
	// this will make sure the Y-rotation is always along the world-Y axis
	mat33f mat = ljm::R(*m_v3Up, (double)m_fAngY);
	// apply the rotation to right and dir axiss
	*m_v3Right = mat * *m_v3Right;
	*m_v3Dir = mat * *m_v3Dir;
	// then rotate along the Right axis
	mat = ljm::R(*m_v3Right, m_fAngX);
	// apply the X-rotation to up and dir axis
	*m_v3Up = mat * *m_v3Up;
	*m_v3Dir = mat * *m_v3Dir;
	// Normalize Direction
	*m_v3Dir = ljm::normalize(*m_v3Dir);
	// Recreate Right
	*m_v3Right = ljm::normalize(ljm::cross(*m_v3Up, *m_v3Dir));
	// Recreate Up
	*m_v3Up = ljm::normalize(ljm::cross(*m_v3Dir, *m_v3Right));
}

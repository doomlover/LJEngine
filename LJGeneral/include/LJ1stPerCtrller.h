#ifndef LJ1STPERCTRLLER_H
#define LJ1STPERCTRLLER_H

#include "LJGeneralHeaders.h"
#include <LJMoveController.h>

class _LJExport LJ1stPerCtrller: public LJBaseMoveController
{
public:
	LJ1stPerCtrller(void) :
			m_fSpeed(0), m_fSlide(0)
	{
	}
	virtual ~LJ1stPerCtrller(void);
	virtual void Update(float fElapsedTime);

	void SetRotation(float fAngX, float fAngY, float fAngZ);
	void SetPos(const vec3f& v3Pos);
	void SetRight(const vec3f& v3Right);
	void SetUp(const vec3f& v3Up);
	void SetDir(const vec3f& v3Dir);

	void GetRotation(float *fAngX, float *fAngY, float *fAngZ) const;
	void SetRotationSpeedX(float fP)
	{
		m_fPitchSpeed = fP;
	}
	void SetRotationSpeedY(float fY)
	{
		m_fYawSpeed = fY;
	}
	void SetSpeed(float fSpd)
	{
		m_fSpeed = fSpd;
	}
	void SetSlideSpeed(float fSldSpd)
	{
		m_fSlide = fSldSpd;
	}

private:
	float m_fSpeed;
	float m_fSlide;
	void RecalculateAxes(void);
};

#endif /* LJ1STPERCTRLLER_H */

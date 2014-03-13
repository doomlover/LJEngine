#ifndef LJFREECTRLLER_H_
#define LJFREECTRLLER_H_

#include <LJMoveController.h>

class _LJExport LJFreeCtrller : public LJBaseMoveController
{
public:
	virtual ~LJFreeCtrller(void);
	virtual void Update(float fElapsedtime);

	void AddRotationSpeed(float fX, float fY, float fZ);
	void SetRotationSpeed(float fX, float fY, float fZ);
	void SetRotationSpeedX(float fP) {
		m_fPitchSpeed = fP;
	}
	void SetRotationSpeedY(float fY) {
		m_fYawSpeed = fY;
	}
	void SetRotationSpeedZ(float fR) {
		m_fRollSpeed = fR;
	}
	void AddThrust(float fThrust) {
		m_fThrust += fThrust;
	}
	void SetThrust(float fThrust) {
		m_fThrust = fThrust;
	}
	void SetRotation(float fAngX, float fAngY, float fAngZ);
	void SetPos(const LJVector3& v3Pos);
	void SetRight(LJVector3& v3Right);
	void SetUp(LJVector3& v3Up);
	void SetDir(LJVector3& v3Dir);
};//~LJFreeCtrller


#endif /* LJFREECTRLLER_H_ */

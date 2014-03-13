#ifndef LJMOVECONTROLLER_H_
#define LJMOVECONTROLLER_H_

#include "LJGeneralHeaders.h"
using namespace ljm;
/*
 * Take care of the View Matrix as well as
 * movement of objects
 */
class _LJExport LJMoveController
{
public:
	virtual ~LJMoveController(void){};
	/* update movement and rotation */
	virtual void Update(float fElapsedtime) = 0;
	virtual vec3f GetPos(void) const = 0;
	virtual vec3f GetDir(void) const = 0;
	virtual vec3f GetRight(void) const = 0;
	virtual vec3f GetUp(void) const = 0;
	virtual vec3f GetVelocity(void) const = 0;
protected:
	virtual void RecalculateAxes(void) = 0;
	virtual void init(void) = 0;
};

class _LJExport LJBaseMoveController : public LJMoveController
{
public:
	LJBaseMoveController();
	virtual ~LJBaseMoveController(void);
	virtual void Update(float fElapsedtime) = 0;
	vec3f GetPos(void) const;
	vec3f GetDir(void) const {return *m_v3Dir;}
	vec3f GetRight(void) const{return *m_v3Right;}
	vec3f GetUp(void) const {return *m_v3Up;}
	vec3f GetVelocity(void) const {return *m_v3Velocity;}
protected:
	virtual void RecalculateAxes(void);
	virtual void init(void);

	vec3f *m_v3Pos;
	vec3f *m_v3Dir;
	vec3f *m_v3Right;
	vec3f *m_v3Up;
	vec3f *m_v3Velocity; // Speed
	// quaternion
	LJQuat *m_Quat;


	// rotation speed on local axe
	float m_fRollSpeed; 		// 滚动
	float m_fPitchSpeed; 	// 俯仰
	float m_fYawSpeed; 		// 偏转
	// max limite
	float m_fRollSpeedMax; 		// 滚动
	float m_fPitchSpeedMax; 		// 俯仰
	float m_fYawSpeedMax; 		// 偏转
	// rotation angle on local axe
	float m_fAngX;
	float m_fAngY;
	float m_fAngZ;
	// The force used in pushing, 推力
	float m_fThrust;
};


#endif /* LJMOVECONTROLLER_H_ */

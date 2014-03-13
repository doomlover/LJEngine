#include <LJMoveController.h>
#include <LJUtil.h>
#include <string>
using std::string;

static string Tag("LJMoveController");

LJBaseMoveController::LJBaseMoveController()
{
	LJLog(Tag.c_str(), "LJBaseMoveController");
	init();
}//~constructor

LJBaseMoveController::~LJBaseMoveController(void)
{
	if(m_v3Pos) delete m_v3Pos;
	if(m_v3Dir) delete m_v3Dir;
	if(m_v3Right) delete m_v3Right;
	if(m_v3Up) delete m_v3Up;
	if(m_v3Velocity) delete m_v3Velocity;
	if(m_Quat) delete m_Quat;
}//~destructor

float cutTo2PI(float fAng)
{
	static float fPI = 3.1415926f;
	float f2PI = fPI*2.0f;
	if(fAng > f2PI) {
		fAng -= f2PI;
	}else if (fAng < -f2PI) {
		fAng += f2PI;
	}
	return fAng;
}

vec3f LJBaseMoveController::GetPos(void) const
{return *m_v3Pos;}

/* =====================================
 * 			 Private Function
 * =====================================*/

void LJBaseMoveController::RecalculateAxes(void)
{
	// cut range to 2PI
	m_fAngX = cutTo2PI(m_fAngX);
	m_fAngY = cutTo2PI(m_fAngY);
	m_fAngZ = cutTo2PI(m_fAngZ);
	// update quaternion
	*m_Quat = LJQuat(vec3f(m_fAngX, m_fAngY, m_fAngZ));
	// get rotation matrix
	LJMatrix3 quatMat = R(*m_Quat);
	// extract the local axes
	*m_v3Right = quatMat[0];
	*m_v3Up = quatMat[1];
	*m_v3Dir = quatMat[2];
}

void LJBaseMoveController::init(void)
{
	m_v3Pos = new vec3f(0, 0, 0);
	m_v3Dir = new vec3f(0, 0, 1);
	m_v3Right = new vec3f(1, 0, 0);
	m_v3Up = new vec3f(0, 1, 0);
	m_v3Velocity = new vec3f(0, 0, 0);
	m_fRollSpeed = 0.f;
	m_fPitchSpeed = 0.f;
	m_fYawSpeed = 0.f;
	m_fAngX = m_fAngY = m_fAngZ = 0.f;
	m_fThrust= 0.f;
	// quaternion initialize
	m_Quat = new LJQuat(1.0f, vec3f(0, 0, 0));
} //~ init



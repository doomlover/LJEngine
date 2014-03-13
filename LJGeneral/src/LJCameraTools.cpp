#include <LJCameraTools.h>
#include <LJUtil.h>

LJMatrix4 BuildViewMatrix(const LJVector3& v3Right, const LJVector3& v3Up, const LJVector3& v3Dir, const LJVector3& v3Pos)
{
	LJMatrix4 matView;
	matView[0][0] = v3Right.x;
	matView[1][0] = v3Right.y;
	matView[2][0] = v3Right.z;

	matView[0][1] = v3Up.x;
	matView[1][1] = v3Up.y;
	matView[2][1] = v3Up.z;

	matView[0][2] = v3Dir.x;
	matView[1][2] = v3Dir.y;
	matView[2][2] = v3Dir.z;

	matView[3][0] = -dot(v3Right, v3Pos);
	matView[3][1] = -dot(v3Up, v3Pos);
	matView[3][2] = -dot(v3Dir, v3Pos);
	return matView;
}

LJMatrix4 BuildViewMatrix(const LJVector3& pos, const LJVector3& center, const LJVector3& up)
{
	LJVector3 d = ljm::normalize(pos - center);
	LJVector3 u = ljm::normalize(up);
	LJVector3 r = ljm::normalize(ljm::cross(u, d));
	u = ljm::cross(d, r);
	return BuildViewMatrix(r, u, d, pos);
}

void BuildPersMatrix(float fFov, float fAspRatio, float fNear, float fFar, LJMatrix4& matPersers, LJMatrix4& matOrth)
{
	float r, l, t, b;
	r = static_cast<float>(fNear*static_cast<float>(tan(DegreeToRadian(fFov/2.0))));
	l = -r;
	t = r/fAspRatio;
	b = -t;
	BuildPersMatrix(l, r, t, b, fNear, fFar, matPersers, matOrth);
}
// Set from Right, Left, Top, Bottom clip planes
void BuildPersMatrix(float fL, float fR, float fT, float fB, float fN, float fF, LJMatrix4& matPers, LJMatrix4& matOrth)
{
	/*
	 * Calculate Projection Matrix
	 */
	float raddl = fR+fL;
	float rsubl = fR-fL;
	float tsubb = fT - fB;
	float taddb = fT + fB;
	float faddn = fF + fN;
	float fsubn = fF - fN;
	/*
	 * Perspective Matrix
	 */
	matPers[0] = LJVector4(2*fN/rsubl, 0, 0, 0);
	matPers[1] = LJVector4(0, 2*fN/tsubb, 0, 0);
	matPers[2] = LJVector4(raddl/rsubl, taddb/tsubb, -faddn/fsubn, -1.f);
	matPers[3] = LJVector4(0, 0, -2*fN*fF/fsubn, 0);
	/*
	 * Orthogonal Matrix
	 */
	matOrth[0] = LJVector4(2.0f/rsubl, 0, 0, 0);
	matOrth[1] = LJVector4(0, 2.0f/tsubb, 0, 0);
	matOrth[2] = LJVector4(0, 0, -2.0f/fsubn, 0);
	matOrth[3] = LJVector4(-raddl/rsubl, -taddb/tsubb, -faddn/fsubn, 1.f);
}



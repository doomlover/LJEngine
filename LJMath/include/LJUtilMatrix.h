#ifndef LJUTILMATRIX_H_
#define LJUTILMATRIX_H_
#include <cmath>
namespace ljm
{
typedef enum AXIS_TYPE {
	LJ_AXIS_X,
	LJ_AXIS_Y,
	LJ_AXIS_Z
} LJAXIS;
//==================================//
// 			DECLARATIONS
//==================================//

/*
 * Rotate about X/Y/Z axis
 */
template <typename T>
LJMat33<T> R(LJAXIS AXIS, double rad);

/*
 * Rotate about an arbitrary axis
 */
template <typename T>
mat33f R(const LJVector3t<T>& v, double rad);

/*
 * Extract the rotation matrix from a quaternion
 */
template <typename T>
LJMat33<T> R(const LJQuaternion<T>& q);

//==================================//
// 			DEFINITIONS
//==================================//
template <typename T>
mat33f R(const LJVector3t<T>& v, double rad)
{
	LJVector3t<T> n = normalize(v);
	float _cos = static_cast<float>(cos(rad));
	float _sin = static_cast<float>(sin(rad));
	float nxx = n.x*n.x;
	float nxy = n.x*n.y;
	float nxz = n.x*n.z;
	float nyy = n.y*n.y;
	float nyz = n.y*n.z;
	float nzz = n.z*n.z;
	return mat33f(nxx*(1-_cos)+_cos, nxy*(1-_cos)+n.z*_sin, nxz*(1-_cos)-n.y*_sin,
			      nxy*(1-_cos)-n.z*_sin, nyy*(1-_cos)+_cos, nyz*(1-_cos)+n.x*_sin,
			      nxz*(1-_cos)+n.y*_sin, nyz*(1-_cos)-n.x*_sin, nzz*(1-_cos)+_cos);
}
template <typename T>
LJMat33<T> R(LJAXIS AXIS, double rad)
{
	T _sin = T(sin(rad));
	T _cos = T(cos(rad));
	T _1 = T(1);
	T _0 = T(0);
	switch(AXIS)
	{
	case LJ_AXIS_X:
		return LJMat33<T>(_1, _0, _0,
				      _0, _cos, -_sin,
				      _0, _sin, _cos);
	case LJ_AXIS_Y:
		return mat33f(_cos, _0, _sin,
				      _0, _1, _0,
				      -_sin, _0, _cos);
	case LJ_AXIS_Z:
		return mat33f(_cos, -_sin, _0,
				      _sin, _cos, _0,
				      _0, _0, _1);
	default:
		/* Should not be here */
		return mat33f();
	}
}
template <typename T>
LJMat33<T> R(const LJQuaternion<T>& q)
{
	T yy2 = T(2)*q.y*q.y;
	T zz2 = T(2)*q.z*q.z;
	T xx2 = T(2)*q.x*q.x;
	T xy2 = T(2)*q.x*q.y;
	T xz2 = T(2)*q.x*q.z;
	T wx2 = T(2)*q.w*q.x;
	T wz2 = T(2)*q.w*q.z;
	T wy2 = T(2)*q.w*q.y;
	T yz2 = T(2)*q.y*q.z;

	return LJMat33<T>(
			1-yy2-zz2, xy2+wz2, xz2-wy2,
			xy2-wz2, 1-xx2-zz2, yz2+wx2,
			xz2+wy2, yz2-wx2, 1-xx2-yy2
			);
}

template<typename T>
LJMat33<T> S(const T& kx, const T& ky, const T& kz)
{
	return LJMat33<T>(
		kx, 0, 0,
		0, ky, 0,
		0,  0, kz
		);
}

template<typename T>
LJMat33<T> S(const LJVector3t<T>& n, const T& k)
{
	T xx = n.x*n.x;
	T yy = n.y*n.y;
	T zz = n.z*n.z;
	T xy = n.x*n.y;
	T xz = n.x*n.z;
	T yz = n.y*n.z;
	T k1 = k-1;
	return LJMat33<T>(
		1+k1*xx, k1*xy, k1*xz,
		k1*xy, 1+k1*yy, k1*yz,
		k1*xz, k1*yz, 1+k1*zz
		);
}
}

#endif /* LJUTILMATRIX_H_ */

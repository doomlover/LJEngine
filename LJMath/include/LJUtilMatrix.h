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
/*
 * Calculate eigenvalues and eigenvectors of 3x3 matrix
 * Section 16.3 of Mathematics for 3D Game Programming and Computer Graphics
 */
template<typename T>
LJMat33<T> EigenSystem(const LJMat33<T>& m, float *eigenVals)
{
	float epsilon = 1.0e-10F;
	int maxSweeps = 32;

	float m11 = m[0][0];
	float m12 = m[1][0];
	float m13 = m[2][0];
	float m22 = m[1][1];
	float m23 = m[2][1];
	float m33 = m[2][2];

	LJMat33<T> r;
	for(int i = 0; i < maxSweeps; ++i)
	{
		if((absT(m12) < epsilon) &&
		    (absT(m13) < epsilon) &&
		    (absT(m23) < epsilon))
		{
			break;
		}
		if(m12 != 0.0f)
		{
			float u = (m22 - m11) * 0.5f / m12;
			float u2 = u * u;
			float u2p1 = u2 + 1.0f;
			float t = (u2p1 != u2) ?
					((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - absT(u)) :
					0.5f / u;
			float c = 1.0f / sqrt(t*t + 1.0f);
			float s = c * t;
			m11 -= t * m12;
			m22 += t * m12;
			m12 = 0.0f;

			float tmp = c * m13 - s * m23;
			m23 = s * m13 + c * m23;
			m13 = tmp;

			for(int i = 0; i < 3; ++i)
			{
				float tmp = c * r[0][i] - s * r[1][i];
				r[1][i] = s * r[0][i] + c * r[1][i];
				r[0][i] = tmp;
			}
		}

		if(m13 != 0.0f)
		{
			float u = (m33 - m11) * 0.5f / m13;
			float u2 = u * u;
			float u2p1 = u2 + 1.0f;
			float t = (u2p1 != u2) ?
					((u < 0.0f) ? -1.0f : 1.0f)*(sqrt(u2p1) - absT(u))
					: 0.5f / u;
			float c = 1.0f / sqrt(t * t + 1.0f);
			float s = c * t;

			m11 -= t * m13;
			m33 += t * m13;
			m13 = 0.0f;

			float tmp = c * m12 - s * m23;
			m23 = s * m12 + c * m23;
			m12 = tmp;

			for(int i = 0; i < 3; ++i)
			{
				float tmp = c * r[0][i] - s * r[2][i];
				r[2][i] = s * r[0][i] + c * r[2][i];
				r[0][i] = tmp;
			}
		}

		if(m23 != 0.0f)
		{
			float u = (m33 - m22) * 0.5f / m23;
			float u2 = u * u;
			float u2p1 = u2 + 1.0f;
			float t = (u2p1 != u2) ?
					((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - absT(u)) :
					0.5f / u;
			float c = 1.0f / sqrt(t * t + 1.0f);
			float s = c * t;

			m22 -= t * m23;
			m33 += t * m23;
			m23 = 0.0f;

			for(int i = 0; i < 3; ++i)
			{
				float tmp = c * r[1][i] - s * r[2][i];
				r[2][i] = s * r[1][i] + c * r[2][i];
				r[1][i] = tmp;
			}
		}
	}

	eigenVals[0] = m11;
	eigenVals[1] = m22;
	eigenVals[2] = m33;

	return r;
}
}

#endif /* LJUTILMATRIX_H_ */

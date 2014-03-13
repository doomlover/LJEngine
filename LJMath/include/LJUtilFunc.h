#ifndef LJUTILFUNC_H_
#define LJUTILFUNC_H_

namespace ljm {

/* NON-MEMBER OPERATORS */
/* s + v2 */
template<typename T>
LJVector2t<T> operator*(T s, const LJVector2t<T>& v)
{
	return LJVector2t<T>(s*v.x, s*v.y);
}
/* s + v3 */
template<typename T>
LJVector3t<T> operator*(T s, const LJVector3t<T>& v)
{
	return LJVector3t<T>(s*v.x, s*v.y, s*v.z);
}
/* s + v4 */
template<typename T>
LJVector4t<T> operator*(T s, const LJVector4t<T>& v)
{
	return LJVector4t<T>(s*v.x, s*v.y, s*v.z, s*v.w);
}
/* LENGTH */
template<typename T>
T length(const LJVector2t<T>& v)
{
	T quad = v.x*v.x +
			v.y*v.y;
	return sqrt(quad);
}

template<typename T>
T length(const LJVector3t<T>& v)
{
	T quad = v.x*v.x +
			v.y*v.y +
			v.z*v.z;
	return sqrt(quad);
}

template<typename T>
T length(const LJVector4t<T>& v)
{
	T quad = v.x*v.x +
			v.y*v.y +
			v.z*v.z +
			v.w*v.w;
	return sqrt(quad);
}
/* DOT PRODUCT */
template<typename T>
T dot(const LJVector2t<T>& v1, const LJVector2t<T>& v2)
{
	T ret = v1.x*v2.x +
			v1.y*v2.y;
	return ret;
}

template<typename T>
T dot(const LJVector3t<T>& v1, const LJVector3t<T>& v2)
{
	T ret = v1.x*v2.x +
			v1.y*v2.y +
			v1.z*v2.z;
	return ret;
}

template<typename T>
T dot(const LJVector4t<T>& v1, const LJVector4t<T>& v2)
{
	T ret = v1.x*v2.x +
			v1.y*v2.y +
			v1.z*v2.z +
			v1.w*v2.w;
	return ret;
}
/* CROSS PRODUCT */
template<typename T>
LJVector3t<T> cross(const LJVector3t<T>& v1, const LJVector3t<T>& v2)
{
	return LJVector3t<T>(
	v1.y*v2.z-v1.z*v2.y,
	v1.z*v2.x-v1.x*v2.z,
	v1.x*v2.y-v1.y*v2.x
	);
}
/* NORMALIZE */
template<typename T>
LJVector2t<T> normalize(const LJVector2t<T>& v)
{
	T inverse_length = T(1)/sqrt(v.x*v.x + v.y*v.y);
	return v*inverse_length;
}
template<typename T>
LJVector3t<T> normalize(const LJVector3t<T>& v)
{
	T inverse_length = T(1)/sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return v*inverse_length;
}
template<typename T>
LJVector4t<T> normalize(const LJVector4t<T>& v)
{
	T inverse_length = T(1)/sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
	return v*inverse_length;
}

}
#endif /* LJUTILFUNC_H_ */

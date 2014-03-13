#ifndef LJVECTOR4_H_
#define LJVECTOR4_H_

#include <cstring>
#include <assert.h>

namespace ljm {

template<typename T>
class LJVector4t {
	typedef std::size_t sizeType;
public:
	T x, y, z, w;
	LJVector4t():x(T(0)),y(T(0)),z(T(0)),w(T(0)){}
	LJVector4t(T _x, T _y, T _z, T _w) :
			x(_x), y(_y), z(_z), w(_w) {
	}
	LJVector4t(const LJVector3t<T>& v, T _w);
	LJVector4t(const LJVector4t<T>& other);

	LJVector4t<T>& operator=(const LJVector4t<T>& other);

	LJVector4t<T> operator+(const LJVector4t<T>& other);
	LJVector4t<T>& operator+=(const LJVector4t<T>& other);

	LJVector4t<T> operator-(const LJVector4t<T>& v4);
	LJVector4t<T>& operator-=(const LJVector4t<T>& v4);

	LJVector4t<T> operator*(const LJVector4t<T>& v4);
	LJVector4t<T> operator*(T s);
	LJVector4t<T>& operator*=(const LJVector4t<T>& v4);

	LJVector4t<T> operator/(const LJVector4t<T>& v4);
	LJVector4t<T>& operator/=(const LJVector4t<T>& v4);
	LJVector4t<T>& operator/=(const T& s);
	LJVector4t<T> operator/(T s);

	T& operator[](sizeType i);
	const T& operator[](sizeType i) const;
};
//================================================//
// NON-MEMBER FUNCTIONS

template<typename T>
LJVector4t<T> operator*(const LJVector4t<T>& v, const T& s)
{
	return LJVector4t<T>(v.x*s, v.y*s, v.z*s, v.w*s);
}

template <typename T>
LJVector4t<T> operator-(const LJVector4t<T>& v)
{
	return LJVector4t<T>(-v.x, -v.y, -v.z, -v.w);
}

template <typename T>
bool operator!=(const LJVector4t<T>& v1, const LJVector4t<T>& v2)
{
	// if all are equal, then is false
	// else is true
	return !((v1.x==v2.x)&&(v1.y==v2.y)&&(v1.z==v2.z)&&(v1.w==v2.w));
}

// MEMBER FUNCTIONS
template<typename T>
LJVector4t<T>::LJVector4t(const LJVector3t<T>& v, T _w)
:x(v.x), y(v.y), z(v.z), w(_w)
{}
template<typename T>
LJVector4t<T>::LJVector4t(const LJVector4t<T>& other)
:x(other.x),y(other.y),z(other.z),w(other.w)
{}

template<typename T>
LJVector4t<T>& LJVector4t<T>::operator=(const LJVector4t<T>& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}
template<typename T>
LJVector4t<T> LJVector4t<T>::operator+(const LJVector4t<T>& other)
{

	return LJVector4t<T>(x+other.x, y+other.y,
			             z+other.z, w+other.w);
}
template<typename T>
LJVector4t<T>& LJVector4t<T>::operator+=(const LJVector4t<T>& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}
template<typename T>
LJVector4t<T> LJVector4t<T>::operator-(const LJVector4t<T>& v4)
{
	return LJVector4t(x-v4.x,
			          y-v4.y,
			          z-v4.z,
			          w-v4.w);
}
template<typename T>
LJVector4t<T>& LJVector4t<T>::operator-=(const LJVector4t<T>& v4) {
	x -= v4.x;
	y -= v4.y;
	z -= v4.z;
	w -= v4.w;
	return *this;
}
template<typename T>
LJVector4t<T> LJVector4t<T>::operator*(const LJVector4t<T>& v4)
{
	return LJVector4t<T>(x*v4.x,
			             y*v4.y,
			             z*v4.z,
			             w*v4.w);
}
template<typename T>
LJVector4t<T>& LJVector4t<T>::operator*=(const LJVector4t<T>& v4)
{
	x*=v4.x;
	y*=v4.y;
	z*=v4.z;
	w*=v4.w;
	return *this;
}
template<typename T>
LJVector4t<T> LJVector4t<T>::operator*(T s)
{
	return LJVector4t(x*s,y*s,z*s,w*s);
}
template<typename T>
LJVector4t<T> LJVector4t<T>::operator/(const LJVector4t<T>& v4)
{
	return LJVector4t<T>(x/v4.x,
			y/v4.y,
			z/v4.z,
			w/v4.w);
}
template<typename T>
LJVector4t<T>& LJVector4t<T>::operator/=(const LJVector4t<T>& v4)
{
	x/=v4.x;
	y/=v4.y;
	z/=v4.z;
	w/=v4.w;
	return *this;
}
template <typename T>
LJVector4t<T>& LJVector4t<T>::operator/=(const T& s)
{
	x/=s;
	y/=s;
	z/=s;
	w/=s;
	return *this;
}
template<typename T>
LJVector4t<T> LJVector4t<T>::operator/(T s)
{
	return LJVector4t<T>(x/s,y/s,z/s,w/s);
}
template<typename T>
T& LJVector4t<T>::operator[](sizeType i)
{
	assert(i < 4);
	return (&x)[i];
}
template<typename T>
const T& LJVector4t<T>::operator[](sizeType i) const
{
	assert(i < 4);
	return (&x)[i];
}


typedef LJVector4t<float> vec4f;
typedef LJVector4t<int> vec4i;
typedef LJVector4t<unsigned int> vec4u;
typedef vec4f LJVector4f;
typedef vec4i LJVector4i;
typedef vec4u LJVector4u;
}

#endif /* LJVECTOR4_H_ */

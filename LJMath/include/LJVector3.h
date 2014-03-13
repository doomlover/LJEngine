#ifndef LJVECTOR3_H_
#define LJVECTOR3_H_

#include <cstring>
#include <assert.h>
namespace ljm {

template<typename T>
class LJVector4t;

template<typename T>
class LJVector3t {
public:
	typedef std::size_t sizeType;
	T x, y, z;
	LJVector3t():x(T(0)),y(T(0)),z(T(0)){}
	LJVector3t(T _x, T _y, T _z) :
			x(_x), y(_y), z(_z) {
	}
	LJVector3t(const LJVector3t<T>& other);
	LJVector3t(const LJVector4t<T>& other);

	LJVector3t<T>& operator=(const LJVector3t<T>& other);
	LJVector3t<T>& operator=(const LJVector4t<T>& other);

	LJVector3t<T> operator+(const LJVector3t<T>& other);
	LJVector3t<T>& operator+=(const LJVector3t<T>& other);

	LJVector3t<T> operator-(const LJVector3t<T>& v);
	LJVector3t<T>& operator-=(const LJVector3t<T>& v);

	LJVector3t<T> operator*(const LJVector3t<T>& v);
	LJVector3t<T> operator*(T s);
	LJVector3t<T>& operator*=(const LJVector3t<T>& v);
	LJVector3t<T>& operator*=(const T& s);

	LJVector3t<T> operator/(const LJVector3t<T>& v);
	LJVector3t<T>& operator/=(const LJVector3t<T>& v);
	LJVector3t<T>& operator/=(const T& s);
	LJVector3t<T> operator/(T s);

	T& operator[](sizeType i);
	const T& operator[] (sizeType i) const;
};
// NON-MEMBER FUNCTIONS

template<typename T>
LJVector3t<T> operator*(const LJVector3t<T>& v, const T& s)
{
	return LJVector3t<T>(v.x*s, v.y*s, v.z*s);
}
template <typename T>
LJVector3t<T> operator-(const LJVector3t<T>& v)
{
	return LJVector3t<T>(-v.x, -v.y, -v.z);
}
template <typename T>
LJVector3t<T> operator-(const LJVector3t<T>& v1, const LJVector3t<T>& v2)
{
	return LJVector3t<T>(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}


template<typename T>
LJVector3t<T>::LJVector3t(const LJVector3t<T>& other)
:x(other.x),y(other.y),z(other.z)
{}
template<typename T>
LJVector3t<T>::LJVector3t(const LJVector4t<T>& other)
:x(other.x),y(other.y),z(other.z)
{}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator=(const LJVector3t<T>& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator=(const LJVector4t<T>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}
template<typename T>
LJVector3t<T> LJVector3t<T>::operator+(const LJVector3t<T>& other)
{

	return LJVector3t<T>(x+other.x, y+other.y,
			             z+other.z);
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator+=(const LJVector3t<T>& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
template<typename T>
LJVector3t<T> LJVector3t<T>::operator-(const LJVector3t<T>& v)
{
	return LJVector3t(x-v.x,
			          y-v.y,
			          z-v.z);
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator-=(const LJVector3t<T>& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
template<typename T>
LJVector3t<T> LJVector3t<T>::operator*(const LJVector3t<T>& v)
{
	return LJVector3t<T>(x*v.x,
			             y*v.y,
			             z*v.z);
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator*=(const LJVector3t<T>& v)
{
	x*=v.x;
	y*=v.y;
	z*=v.z;
	return *this;
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator*=(const T& s)
{
	x*=s;
	y*=s;
	z*=s;
	return *this;
}
template<typename T>
LJVector3t<T> LJVector3t<T>::operator*(T s)
{
	return LJVector3t(x*s,y*s,z*s);
}
template<typename T>
LJVector3t<T> LJVector3t<T>::operator/(const LJVector3t<T>& v)
{
	return LJVector3t<T>(x/v.x,
			y/v.y,
			z/v.z);
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator/=(const LJVector3t<T>& v)
{
	x/=v.x;
	y/=v.y;
	z/=v.z;
	return *this;
}
template<typename T>
LJVector3t<T>& LJVector3t<T>::operator/=(const T& s)
{
	x/=s;
	y/=s;
	z/=s;
	return *this;
}
template<typename T>
LJVector3t<T> LJVector3t<T>::operator/(T s)
{
	return LJVector3t<T>(x/s,y/s,z/s);
}
template<typename T>
T& LJVector3t<T>::operator[](sizeType i)
{
	assert(i < 3);
	return (&x)[i];
}
template<typename T>
const T& LJVector3t<T>::operator[] (sizeType i) const
{
	assert(i < 3);
	return (&x)[i];
}

typedef LJVector3t<float> LJVector3f;
typedef LJVector3t<int> LJVector3i;
typedef LJVector3t<unsigned int> LJVector3u;
typedef LJVector3f vec3f;
typedef LJVector3i vec3i;
typedef LJVector3u vec3u;

}

#endif /* LJVECTOR3_H_ */

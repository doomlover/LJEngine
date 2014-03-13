#ifndef LJVECTOR2_H_
#define LJVECTOR2_H_

#include <cstring>
#include <assert.h>

namespace ljm {

template<typename T>
class LJVector2t {
	typedef std::size_t sizeType;
public:
	T x, y;
	LJVector2t():x(T(0)),y(T(0)){}
	LJVector2t(T _x, T _y) :
			x(_x), y(_y) {
	}
	LJVector2t(const LJVector2t<T>& other);

	LJVector2t<T>& operator=(const LJVector2t<T>& other);

	LJVector2t<T> operator+(const LJVector2t<T>& other);
	LJVector2t<T>& operator+=(const LJVector2t<T>& other);

	LJVector2t<T> operator-(const LJVector2t<T>& v);
	LJVector2t<T>& operator-=(const LJVector2t<T>& v);

	LJVector2t<T> operator*(const LJVector2t<T>& v);
	LJVector2t<T> operator*(T s);
	LJVector2t<T>& operator*=(const LJVector2t<T>& v);

	LJVector2t<T> operator/(const LJVector2t<T>& v);
	LJVector2t<T>& operator/=(const LJVector2t<T>& v);
	LJVector2t<T> operator/(T s);

	T& operator[](sizeType i);
	const T& operator[] (sizeType i) const;
};

// NON-MEMBER FUNCTIONS
template<typename T>
LJVector2t<T> operator*(const LJVector2t<T>& v, const T& s)
{
	return LJVector2t<T>(v.x*s, v.y*s);
}
template <typename T>
LJVector2t<T> operator-(const LJVector2t<T>& v)
{
	return LJVector2t<T>(-v.x, -v.y);
}

template<typename T>
LJVector2t<T>::LJVector2t(const LJVector2t<T>& other)
:x(other.x),y(other.y)
{}

template<typename T>
LJVector2t<T>& LJVector2t<T>::operator=(const LJVector2t<T>& other) {
	x = other.x;
	y = other.y;
	return *this;
}
template<typename T>
LJVector2t<T> LJVector2t<T>::operator+(const LJVector2t<T>& other)
{
	return LJVector2t<T>(x+other.x, y+other.y);
}
template<typename T>
LJVector2t<T>& LJVector2t<T>::operator+=(const LJVector2t<T>& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
template<typename T>
LJVector2t<T> LJVector2t<T>::operator-(const LJVector2t<T>& v)
{
	return LJVector2t(x-v.x,
			          y-v.y);
}
template<typename T>
LJVector2t<T>& LJVector2t<T>::operator-=(const LJVector2t<T>& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}
template<typename T>
LJVector2t<T> LJVector2t<T>::operator*(const LJVector2t<T>& v)
{
	return LJVector2t<T>(x*v.x,
			             y*v.y);
}
template<typename T>
LJVector2t<T>& LJVector2t<T>::operator*=(const LJVector2t<T>& v)
{
	x*=v.x;
	y*=v.y;
	return *this;
}
template<typename T>
LJVector2t<T> LJVector2t<T>::operator*(T s)
{
	return LJVector2t(x*s,y*s);
}
template<typename T>
LJVector2t<T> LJVector2t<T>::operator/(const LJVector2t<T>& v)
{
	return LJVector2t<T>(x/v.x,
			y/v.y);
}
template<typename T>
LJVector2t<T>& LJVector2t<T>::operator/=(const LJVector2t<T>& v)
{
	x/=v.x;
	y/=v.y;
	return *this;
}
template<typename T>
LJVector2t<T> LJVector2t<T>::operator/(T s)
{
	return LJVector2t<T>(x/s,y/s);
}
template<typename T>
T& LJVector2t<T>::operator[](sizeType i)
{
	assert(i < 2);
	return (&x)[i];
}

template<typename T>
const T& LJVector2t<T>::operator[] (sizeType i) const
{
	assert(i < 2);
	return (&x)[i];
}

typedef LJVector2t<float> LJVector2f;
typedef LJVector2t<int> LJVector2i;
typedef LJVector2t<unsigned int> LJVector2u;
typedef LJVector2f vec2f;
typedef LJVector2i vec2i;
typedef LJVector2u vec2u;
}

#endif /* LJVECTOR2_H_ */

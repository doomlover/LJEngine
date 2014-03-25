#ifndef LJMAT33_H_
#define LJMAT33_H_
#include "LJUtilFunc.h"
#include <assert.h>
#include <iostream>
namespace ljm{

template<typename T>
class LJMat33
{
public:
	typedef LJVector3t<T> colType;
	typedef std::size_t sizeType;
	// 3 COLUMN, COLUMN MAJOR
	LJVector3t<T> colData[3];
	LJMat33();
	LJMat33(const LJMat33<T>& m);
	LJMat33(const LJVector3t<T>& v1,
			const colType& v2,
			const colType& v3);
	LJMat33(const T& x0, const T& x1, const T& x2,
			const T& y0, const T& y1, const T& y2,
			const T& z0, const T& z1, const T& z2);
	// OPERATORS
	colType& operator[](sizeType i);
	const colType& operator[](sizeType i) const;
	LJMat33<T>& operator=(const LJMat33<T>& m);
	LJMat33<T>& operator*=(const LJMat33<T>& m);
};
// Declaration
template<typename T>
LJMat33<T>  operator*(const LJMat33<T>& m1, const LJMat33<T>& m2);
template<typename  T>
typename LJMat33<T>::colType operator*(const LJMat33<T>& m, const typename LJMat33<T>::colType& v);
template<typename T>
void exchange_col(LJMat33<T>& m, typename LJMat33<T>::sizeType i, typename LJMat33<T>::sizeType j);
template<typename T>
LJMat33<T> transpose(const LJMat33<T>& m);
template<typename T>
bool inverse(const LJMat33<T>& m, LJMat33<T> *inv);


// CONSTRUCTORS
template<typename T>
LJMat33<T>::LJMat33()
{
	T _0(0);
	T _1(1);
	colData[0] = colType(_1, _0, _0);
	colData[1] = colType(_0, _1, _0);
	colData[2] = colType(_0, _0, _1);
}
template<typename T>
LJMat33<T>::LJMat33(const LJMat33<T>& m)
{
	colData[0] = m.colData[0];
	colData[1] = m.colData[1];
	colData[2] = m.colData[2];
}
template<typename T>
LJMat33<T>::LJMat33(const LJVector3t<T>& v1,
					const colType& v2,
					const colType& v3)
{
	colData[0] = v1;
	colData[1] = v2;
	colData[2] = v3;
}
template<typename T>
LJMat33<T>::LJMat33(const T& x0, const T& x1, const T& x2,
		const T& y0, const T& y1, const T& y2,
		const T& z0, const T& z1, const T& z2)
{
	colData[0] = colType(x0, x1, x2);
	colData[1] = colType(y0, y1, y2);
	colData[2] = colType(z0, z1, z2);
}
// OPERATORS
template<typename T>
typename LJMat33<T>::colType& LJMat33<T>::operator[](sizeType i)
{
	return colData[i];
}
template<typename T>
const typename LJMat33<T>::colType& LJMat33<T>::operator[](sizeType i) const
{
	return colData[i];
}
template<typename T>
LJMat33<T>& LJMat33<T>::operator=(const LJMat33<T>& m)
{
	colData[0] = m[0];
	colData[1] = m[1];
	colData[2] = m[2];
	return *this;
}


/*=======================================================================
 	 	 	 	 	 	 NON-MEMBER OPERATORS
=======================================================================*/
template<typename T>
LJMat33<T>  operator*(const LJMat33<T>& m1, const LJMat33<T>& m2)
{
	LJMat33<T> ret;
	ret[0][0] = m1[0][0]*m2[0][0] + m1[1][0]*m2[0][1] + m1[2][0]*m2[0][2];
	ret[0][1] = m1[0][1]*m2[0][0] + m1[1][1]*m2[0][1] + m1[2][1]*m2[0][2];
	ret[0][2] = m1[0][2]*m2[0][0] + m1[1][2]*m2[0][1] + m1[2][2]*m2[0][2];

	ret[1][0] = m1[0][0]*m2[1][0] + m1[1][0]*m2[1][1] + m1[2][0]*m2[1][2];
	ret[1][1] = m1[0][1]*m2[1][0] + m1[1][1]*m2[1][1] + m1[2][1]*m2[1][2];
	ret[1][2] = m1[0][2]*m2[1][0] + m1[1][2]*m2[1][1] + m1[2][2]*m2[1][2];

	ret[2][0] = m1[0][0]*m2[2][0] + m1[1][0]*m2[2][1] + m1[2][0]*m2[2][2];
	ret[2][1] = m1[0][1]*m2[2][0] + m1[1][1]*m2[2][1] + m1[2][1]*m2[2][2];
	ret[2][2] = m1[0][2]*m2[2][0] + m1[1][2]*m2[2][1] + m1[2][2]*m2[2][2];

	return ret;
}

template<typename T>
typename LJMat33<T>::colType operator*(const LJMat33<T>& m,
		              const typename LJMat33<T>::colType& v)
{
	return typename LJMat33<T>::colType(
			m[0][0]*v.x + m[1][0]*v.y + m[2][0]*v.z,
			m[0][1]*v.x + m[1][1]*v.y + m[2][1]*v.z,
			m[0][2]*v.x + m[1][2]*v.y + m[2][2]*v.z
			);
}

template<typename T>
void exchange_col(LJMat33<T>& m, typename LJMat33<T>::sizeType i, typename LJMat33<T>::sizeType j)
{
	assert((i < 3)&&(j < 3));
	typename LJMat33<T>::colType tmp = m[i];
	m[i] = m[j];
	m[j] = tmp;
}
template<typename T>
LJMat33<T> transpose(const LJMat33<T>& m)
{
	LJMat33<T> ret;
	ret[0] = typename LJMat33<T>::colType(m[0][0], m[1][0], m[2][0]);
	ret[1] = typename LJMat33<T>::colType(m[0][1], m[1][1], m[2][1]);
	ret[2] = typename LJMat33<T>::colType(m[0][2], m[1][2], m[2][2]);
	return ret;
}

template<typename T>
bool inverse(const LJMat33<T>& m, LJMat33<T> *inv)
{
	typedef typename LJMat33<T>::sizeType type;
	// Matrix E
	LJMat33<T> E;
	LJMat33<T> tranM = transpose(m);

	// ~
	for(type j = 0; j < 3; ++j)
	{
		type i;
		T M;
		// find largest abs M on col j
		{
			M = absT(tranM[j][j]);
			i = j;
			for(type k = j+1; k < 3; ++k)
			{
				if(absT(tranM[k][j]) > M) {
					M = absT(tranM[k][j]);
					i = k;
				}
			}
		}

		if(M == 0) {
			return false;
		}
		if(i != j) {
			exchange_col(tranM, i, j);

			exchange_col(E, i, j);
		}
		T mjj = tranM[j][j];
		tranM[j] /= mjj;
		E[j] /= mjj;

		for(type k = 0; k < 3; ++k)
		{
			if ( k != j) {
				T mkj = tranM[k][j];
				tranM[k] -= tranM[j]*mkj;
				E[k] -= E[j]*mkj;
			}
		}
	}
	*inv = transpose(E);
	return true;
}

typedef LJMat33<float> mat33f;
typedef LJMat33<int> mat33i;
typedef LJMat33<double> mat33d;
}


#endif /* LJMAT33_H_ */

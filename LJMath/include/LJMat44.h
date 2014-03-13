#ifndef LJMAT44_H_
#define LJMAT44_H_
#include <assert.h>
namespace ljm{

template<typename T>
class LJMat44
{

public:
	typedef LJVector4t<T> colType;
	typedef std::size_t sizeType;
	// 4 COLUMN, COLUMN MAJOR
	LJVector4t<T> colData[4];
	LJMat44();
	LJMat44(const LJMat44<T>& m);
	LJMat44(const LJMat33<T>& m);
	LJMat44(const colType& v1,
			const colType& v2,
			const colType& v3,
			const colType& v4);
	LJMat44(const T& x0, const T& x1, const T& x2, const T& x3,
			const T& y0, const T& y1, const T& y2, const T& y3,
			const T& z0, const T& z1, const T& z2, const T& z3,
			const T& w0, const T& w1, const T& w2, const T& w3);
	// OPERATORS
	colType& operator[](sizeType i);
	const colType& operator[](sizeType i) const;

	LJMat44<T>& operator=(const LJMat44<T>& m);
	LJMat44<T>& operator*=(const LJMat44<T>& m);
};

/* =========================================================== */
//                  NON-MEMBER Declaration
/* =========================================================== */
template<typename T>
LJMat44<T>  operator*(const LJMat44<T>& m1, const LJMat44<T>& m2);
template<typename T>
typename LJMat44<T>::colType operator*(const LJMat44<T>& m,
		              const typename LJMat44<T>::colType& v);
template<typename T>
bool operator!=(const LJMat44<T>& m1, const LJMat44<T>& m2);
/* =========================================================== */
//                      CONSTRUCTORS
/* =========================================================== */
template<typename T>
LJMat44<T>::LJMat44()
{
	T _0(0);
	T _1(1);
	colData[0] = colType(_1, _0, _0, _0);
	colData[1] = colType(_0, _1, _0, _0);
	colData[2] = colType(_0, _0, _1, _0);
	colData[3] = colType(_0, _0, _0, _1);
}
template<typename T>
LJMat44<T>::LJMat44(const LJMat44<T>& m)
{
	colData[0] = m.colData[0];
	colData[1] = m.colData[1];
	colData[2] = m.colData[2];
	colData[3] = m.colData[3];
}
template<typename T>
LJMat44<T>::LJMat44(const LJMat33<T>& m)
{
	colData[0] = colType(m[0], T(0));
	colData[1] = colType(m[1], T(0));
	colData[2] = colType(m[2], T(0));
	colData[3] = colType(T(0), T(0), T(0), T(1));
}
template<typename T>
LJMat44<T>::LJMat44(const colType& v1,
		const colType& v2,
		const colType& v3,
		const colType& v4)
{
	colData[0] = v1;
	colData[1] = v2;
	colData[2] = v3;
	colData[3] = v4;
}
template<typename T>
LJMat44<T>::LJMat44(const T& x0, const T& x1, const T& x2, const T& x3,
					const T& y0, const T& y1, const T& y2, const T& y3,
					const T& z0, const T& z1, const T& z2, const T& z3,
					const T& w0, const T& w1, const T& w2, const T& w3)
{
	colData[0] = colType(x0, x1, x2, x3);
	colData[1] = colType(y0, y1, y2, y3);
	colData[2] = colType(z0, z1, z2, z3);
	colData[3] = colType(w0, w1, w2, w3);
}
/* =========================================================== */
//                        OPERATORS
/* =========================================================== */

/* Return the column i */
template<typename T>
typename LJMat44<T>::colType& LJMat44<T>::operator[](sizeType i)
{
	assert(i < 4);
	return this->colData[i];
}
template<typename T>
const typename LJMat44<T>::colType& LJMat44<T>::operator[](sizeType i) const
{
	assert(i < 4);
	return this->colData[i];
}
template<typename T>
LJMat44<T>& LJMat44<T>::operator=(const LJMat44<T>& m)
{
	colData[0] = m[0];
	colData[1] = m[1];
	colData[2] = m[2];
	colData[3] = m[3];
	return *this;
}
/* =========================================================== */
//                  NON-MEMBER OPERATORS
/* =========================================================== */
template<typename T>
LJMat44<T>  operator*(const LJMat44<T>& m1, const LJMat44<T>& m2)
{
	LJMat44<T> ret;
	/*
	ret[0][0] = m1[0][0]*m2[0][0] + m1[1][0]*m2[0][1] + m1[2][0]*m2[0][2] + m1[3][0]*m2[0][3];
	ret[0][1] = m1[0][1]*m2[0][0] + m1[1][1]*m2[0][1] + m1[2][1]*m2[0][2] + m1[3][1]*m2[0][3];
	ret[0][2] = m1[0][2]*m2[0][0] + m1[1][2]*m2[0][1] + m1[2][2]*m2[0][2] + m1[3][2]*m2[0][3];
	ret[0][3] = m1[0][3]*m2[0][0] + m1[1][3]*m2[0][1] + m1[2][3]*m2[0][2] + m1[3][3]*m2[0][3];

	ret[1][0] = m1[0][0]*m2[1][0] + m1[1][0]*m2[1][1] + m1[2][0]*m2[1][2] + m1[3][0]*m2[1][3];
	ret[1][1] = m1[0][1]*m2[1][0] + m1[1][1]*m2[1][1] + m1[2][1]*m2[1][2] + m1[3][1]*m2[1][3];
	ret[1][2] = m1[0][2]*m2[1][0] + m1[1][2]*m2[1][1] + m1[2][2]*m2[1][2] + m1[3][2]*m2[1][3];
	ret[1][3] = m1[0][3]*m2[1][0] + m1[1][3]*m2[1][1] + m1[2][3]*m2[1][2] + m1[3][3]*m2[1][3];

	ret[2][0] = m1[0][0]*m2[2][0] + m1[1][0]*m2[2][1] + m1[2][0]*m2[2][2] + m1[3][0]*m2[2][3];
	ret[2][1] = m1[0][1]*m2[2][0] + m1[1][1]*m2[2][1] + m1[2][1]*m2[2][2] + m1[3][1]*m2[2][3];
	ret[2][2] = m1[0][2]*m2[2][0] + m1[1][2]*m2[2][1] + m1[2][2]*m2[2][2] + m1[3][2]*m2[2][3];
	ret[2][3] = m1[0][3]*m2[2][0] + m1[1][3]*m2[2][1] + m1[2][3]*m2[2][2] + m1[3][3]*m2[2][3];

	ret[3][0] = m1[0][0]*m2[3][0] + m1[1][0]*m2[3][1] + m1[2][0]*m2[3][2] + m1[3][0]*m2[3][3];
	ret[3][1] = m1[0][1]*m2[3][0] + m1[1][1]*m2[3][1] + m1[2][1]*m2[3][2] + m1[3][1]*m2[3][3];
	ret[3][2] = m1[0][2]*m2[3][0] + m1[1][2]*m2[3][1] + m1[2][2]*m2[3][2] + m1[3][2]*m2[3][3];
	ret[3][3] = m1[0][3]*m2[3][0] + m1[1][3]*m2[3][1] + m1[2][3]*m2[3][2] + m1[3][3]*m2[3][3];
*/
	const T m100 = m1[0][0];
	const T m101 = m1[0][1];
	const T m102 = m1[0][2];
	const T m103 = m1[0][3];
	const T m110 = m1[1][0];
	const T m111 = m1[1][1];
	const T m112 = m1[1][2];
	const T m113 = m1[1][3];
	const T m120 = m1[2][0];
	const T m121 = m1[2][1];
	const T m122 = m1[2][2];
	const T m123 = m1[2][3];
	const T m130 = m1[3][0];
	const T m131 = m1[3][1];
	const T m132 = m1[3][2];
	const T m133 = m1[3][3];

	const T m200 = m2[0][0];
	const T m201 = m2[0][1];
	const T m202 = m2[0][2];
	const T m203 = m2[0][3];
	const T m210 = m2[1][0];
	const T m211 = m2[1][1];
	const T m212 = m2[1][2];
	const T m213 = m2[1][3];
	const T m220 = m2[2][0];
	const T m221 = m2[2][1];
	const T m222 = m2[2][2];
	const T m223 = m2[2][3];
	const T m230 = m2[3][0];
	const T m231 = m2[3][1];
	const T m232 = m2[3][2];
	const T m233 = m2[3][3];

	ret[0][0] = m100*m200 + m110*m201 + m120*m202 + m130*m203;
	ret[0][1] = m101*m200 + m111*m201 + m121*m202 + m131*m203;
	ret[0][2] = m102*m200 + m112*m201 + m122*m202 + m132*m203;
	ret[0][3] = m103*m200 + m113*m201 + m123*m202 + m133*m203;

	ret[1][0] = m100*m210 + m110*m211 + m120*m212 + m130*m213;
	ret[1][1] = m101*m210 + m111*m211 + m121*m212 + m131*m213;
	ret[1][2] = m102*m210 + m112*m211 + m122*m212 + m132*m213;
	ret[1][3] = m103*m210 + m113*m211 + m123*m212 + m133*m213;

	ret[2][0] = m100*m220 + m110*m221 + m120*m222 + m130*m223;
	ret[2][1] = m101*m220 + m111*m221 + m121*m222 + m131*m223;
	ret[2][2] = m102*m220 + m112*m221 + m122*m222 + m132*m223;
	ret[2][3] = m103*m220 + m113*m221 + m123*m222 + m133*m223;

	ret[3][0] = m100*m230 + m110*m231 + m120*m232 + m130*m233;
	ret[3][1] = m101*m230 + m111*m231 + m121*m232 + m131*m233;
	ret[3][2] = m102*m230 + m112*m231 + m122*m232 + m132*m233;
	ret[3][3] = m103*m230 + m113*m231 + m123*m232 + m133*m233;

	return ret;
}

template<typename T>
typename LJMat44<T>::colType operator*(const LJMat44<T>& m,
		              const typename LJMat44<T>::colType& v)
{
	return typename LJMat44<T>::colType(
			m[0][0]*v.x + m[1][0]*v.y + m[2][0]*v.z + m[3][0]*v.w,
			m[0][1]*v.x + m[1][1]*v.y + m[2][1]*v.z + m[3][1]*v.w,
			m[0][2]*v.x + m[1][2]*v.y + m[2][2]*v.z + m[3][2]*v.w,
			m[0][3]*v.x + m[1][3]*v.y + m[2][3]*v.z + m[3][3]*v.w
			);
}
template<typename T>
bool operator!=(const LJMat44<T>& m1, const LJMat44<T>& m2)
{
	for(int i = 0; i < 4; ++i) {
		// if at least one column is not equal, then is true
		if(m1[i] != m2[i]) return true;
	}
	// all columns is equal, then is false
	return false;
}

template<typename T>
void exchange_col(LJMat44<T>& m, typename LJMat44<T>::sizeType i, typename LJMat44<T>::sizeType j)
{
	assert((i < 4)&&(j < 4));
	typename LJMat44<T>::colType tmp = m[i];
	m[i] = m[j];
	m[j] = tmp;
}
template<typename T>
LJMat44<T> transpose(const LJMat44<T>& m)
{
	LJMat44<T> ret;
	ret[0] = typename LJMat44<T>::colType(m[0][0], m[1][0], m[2][0], m[3][0]);
	ret[1] = typename LJMat44<T>::colType(m[0][1], m[1][1], m[2][1], m[3][1]);
	ret[2] = typename LJMat44<T>::colType(m[0][2], m[1][2], m[2][2], m[3][2]);
	ret[3] = typename LJMat44<T>::colType(m[0][3], m[1][3], m[2][3], m[3][3]);
	return ret;
}

template<typename T>
bool inverse(const LJMat44<T>& m, LJMat44<T> *inv)
{
	typedef typename LJMat44<T>::sizeType type;

	LJMat44<T> E;
	LJMat44<T> tranM = transpose(m);

	for(type j = 0; j < 4; ++j)
	{
		type i;
		T M;
		// find largest abs M on col j
		{
			M = absT(tranM[j][j]);
			i = j;
			for(type k = j+1; k < 4; ++k)
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

		for(type k = 0; k < 4; ++k)
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


typedef LJMat44<float> mat44f;
typedef LJMat44<int> mat44i;
typedef LJMat44<double> mat44d;

}


#endif /* LJMAT44_H_ */

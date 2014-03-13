#ifndef LJQUATERNION_H_
#define LJQUATERNION_H_

namespace ljm
{

/*
 * w, x, y, z order quaternion
 */
template <typename T>
class LJQuaternion
{
	typedef T valType;
public:
	valType w, x, y, z;
	LJQuaternion():w(1), x(0), y(0), z(0){}
	LJQuaternion(const valType& w, const LJVector3t<T>& v);
	LJQuaternion(const valType& w, const valType& x, const valType& y, const valType& z);
	/* Construct a quaternion from (X angle, Y angle, Z angle) */
	LJQuaternion(const LJVector3t<T>& angles);
	LJQuaternion(const LJMat33<T>& m);
	LJQuaternion(const LJMat44<T>& m);
};


/*===========================================
 *          MEMBER FUNCTIONS
 *=========================================== */
template <typename T>
LJQuaternion<T>::LJQuaternion(const valType& w, const LJVector3t<T>& v)
{
	this->w = w;
	x = v.x;
	y = v.y;
	z = v.z;
}
template <typename T>
LJQuaternion<T>::LJQuaternion(const valType& w, const valType& x, const valType& y, const valType& z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}
/*
 * Construct a quaternion from (X angle, Y angle, Z angle)
 * q1 : X rotation
 * q2 : Y rotation
 * q3 : Z rotation
 * apply rotation in X,Y,Z order
 * finally q = q3*q2*q1
 */
template <typename T>
LJQuaternion<T>::LJQuaternion(const LJVector3t<T>& angles)
{
	LJVector3t<T> tmp = angles*T(0.5f);
	T cosx, cosy, cosz;
	T sinx, siny, sinz;
	cosx = cos(tmp.x);
	cosy = cos(tmp.y);
	cosz = cos(tmp.z);
	sinx = sin(tmp.x);
	siny = sin(tmp.y);
	sinz = sin(tmp.z);
	w = cosz*cosy*cosx+sinz*siny*sinx;
	x = cosz*cosy*sinx-sinz*siny*cosx;
	y = cosz*siny*cosx+sinz*cosy*sinx;
	z = sinz*cosy*cosx-cosz*siny*sinx;
}
typedef LJQuaternion<float> quatf;

}


#endif /* LJQUATERNION_H_ */

/*
 * LJUtil.h
 *
 *  Created on: 2013��8��10��
 *      Author: Liu
 */

#ifndef LJUTIL_H_
#define LJUTIL_H_
#include "LJGeneralType.h"
#include <cstdio>
#ifdef _LJ_LINUX
#include <unistd.h>
#endif

#include <iostream>

#define LJFailed(hr) ((hr)!=LJ_OK)

inline void LJLog(const char* tag, const char* msg)
{
	std::cout << tag << ":" << msg << std::endl;
}

inline void  _LJExport LJSleep(DWORD ms)
{
#ifdef _LJ_WIN32
			Sleep((DWORD)ms);
#elif defined _LJ_LINUX
			usleep((DWORD)ms);
#endif
}

#ifndef LJPI
#define LJPI  3.1415926
#endif
inline double DegreeToRadian(double degree)
{
	return degree*LJPI/180.0;
}

inline double RadianToDegree(double radian)
{
	return radian*180.0/LJPI;
}

inline DWORD MakeOGLColor(UCHAR R, UCHAR G, UCHAR B, UCHAR A) {
	return (A << 24) | (R << 16) | (G << 8) | B;
}
#endif /* LJUTIL_H_ */

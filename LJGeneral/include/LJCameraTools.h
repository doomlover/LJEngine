#ifndef CAMERA_H
#define CAMERA_H
#include "LJGeneralHeaders.h"
/* HELPER FUNC */
LJMatrix4 _LJExport BuildViewMatrix(const LJVector3& v3Right, const LJVector3& v3Up, const LJVector3& v3Dir, const LJVector3& v3Pos);

LJMatrix4 _LJExport BuildViewMatrix(const LJVector3& pos, const LJVector3& center, const LJVector3& up);

void _LJExport BuildPersMatrix(float fFov, float fAspRatio, float fNear, float fFar, LJMatrix4& matPersers, LJMatrix4& matOrth);

void _LJExport BuildPersMatrix(float fL, float fR, float fT, float fB, float fN, float fF, LJMatrix4& matPers, LJMatrix4& matOrth);
#endif

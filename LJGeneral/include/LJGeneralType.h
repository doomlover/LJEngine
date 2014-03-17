#ifndef LJGENERALTYPE_H_
#define LJGENERALTYPE_H_

#include "LJPlatform.h"

#ifdef _LJ_WIN32
#include <Windows.h>
#pragma warning( disable: 4251 )
#else
#ifdef _LJ_LINUX
namespace ljrenderer
{
typedef unsigned char UCHAR;
typedef UCHAR BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef DWORD ULONG;
typedef ULONG HRESULT;
typedef void *PVOID;
typedef PVOID HANDLE;
typedef HANDLE HINSTANCE;
typedef HANDLE HWND;
typedef HINSTANCE HMODULE;
}
using namespace ljrenderer;
#endif
#endif

#include "LJMath.h"

typedef ljm::vec3f LJVector3;
typedef ljm::vec4f LJVector4;
typedef ljm::vec2f LJVector2;
typedef ljm::mat44f LJMatrix4;
typedef ljm::mat33f LJMatrix3;
typedef LJVector4 LJPlane;
typedef ljm::quatf LJQuat;
/*
 * Color
 * Value must be given in the range from 0.0 to 1.0
 */
class _LJExport LJCOLOR
{
public:
	union
	{
		struct
		{
			float fR;
			float fG;
			float fB;
			float fA;
		};
		float c[4];
	};
	LJCOLOR() :
			fR(0.f), fG(0.f), fB(0.f), fA(0.f)
	{
	}
	LJCOLOR(float r, float g, float b, float a) :
			fR(r), fG(g), fB(b), fA(a)
	{
	}
};

typedef enum LJDIMENSIONMODE_TYPE
{
	LJ_DM_PERSPECTIVE, LJ_DM_ORTHOGONAL, LJ_WEQS // world coordinates equal to screen coordinates
} LJDIMENSIONMODE;

typedef struct LJVIEWPORT_TYPE
{
	DWORD x; // upper left
	DWORD y; // upper top
	DWORD width;
	DWORD height;
	LJVIEWPORT_TYPE():x(0), y(0), width(640), height(480){}
	LJVIEWPORT_TYPE(DWORD x_, DWORD y_, DWORD w_, DWORD h_):x(x_), y(y_), width(w_), height(h_){}
} LJVIEWPORT;

const HRESULT LJ_OK = 0x0;
const HRESULT LJ_FAIL = 0x1;
const HRESULT LJ_CANCELED = 0x2;
const HRESULT LJ_OUTOFMEMORY = 0x3;
const HRESULT LJ_INVALIDID = 0x4;
const HRESULT LJ_INVALID_TEXTURE_FORMAT = 0x5;
const HRESULT LJ_INVALID_PARAM = 0x6;

const UINT LJ_MAX_RENDER_BUFFERS = 8;
const UINT LJ_MAX_MATERIAL_TEXTURES = 16;
const int LJ_MAX_TEXTURE_ID = 65536;
const UINT LJ_MAX_RENDER_PASSES = 4;
const int LJ_MAX_TEXTURES = 16;
const UINT LJ_MAX_ID = 65536;

#endif /* LJGENERALTYPE_H_ */

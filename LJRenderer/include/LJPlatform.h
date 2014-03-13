#ifndef LJPLATFORM_H
#define LJPLATFORM_H

#define LJ_PLATFORM_WIN32 1
#define LJ_PLATFORM_LINUX 2

#if defined(_LJ_WIN32)
#define LJ_PLATFORM LJ_PLATFORM_WIN32
#elif defined(_LJ_LINUX)
#define LJ_PLATFORM LJ_PLATFORM_LINUX
#endif

#if LJ_PLATFORM == LJ_PLATFORM_WIN32
#define _LJExport __declspec(dllexport)
#elif LJ_PLATFORM == LJ_PLATFORM_LINUX
#define _LJExport
#endif

#endif
#ifndef LJPROGRAM_H
#define LJPROGRAM_H
#include "LJGeneralHeaders.h"
/*
 * Shading Language program interface
 */
class _LJExport LJProgram
{
public:
	virtual ~LJProgram(void){}
	virtual void SetTechName(const char* name) = 0;
	virtual const char* GetTechName() const = 0;
	virtual void SetPassName(const char* name) = 0;
	virtual const char* GetPassName() const = 0;
};

#endif

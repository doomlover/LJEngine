#ifndef LJSHADER_H
#define LJSHADER_H

#include "LJGeneralHeaders.h"
#include <string>

/*
 * Shader interface
 */
class _LJExport LJShader
{
public:
	typedef enum _LJSHADERTYPE{
		LJ_VERTEX_SHADER = 0,
		LJ_FRAGMENT_SHADER = 1,
	} LJSHADERTYPE;

	virtual ~LJShader(void){}
	virtual void SetCode(const char* code, LJSHADERTYPE type) = 0;
	virtual std::string GetCode() const = 0;
};//~LJShader

#endif

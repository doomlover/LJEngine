#ifndef LJGLSLVERTERSHADER_H
#define LJGLSLVERTERSHADER_H

#include "LJShader.h"
#include <string>
using std::string;
class LJGLSLShader : public LJShader
{
public:
	static const UINT ShaderType[2];
	LJGLSLShader();
	LJGLSLShader(const char* code, LJSHADERTYPE type);
	~LJGLSLShader(void);

	void SetCode(const char* code, LJSHADERTYPE type);
	void Compile(void);
	int GetHandle() const;
	LJSHADERTYPE GetType() const;
	string GetCode() const;
	bool IsCompiled() const {return m_bCompiled;}

private:
	/* opengl shader handle */
	int m_uHandle;
	/* shader type */
	LJSHADERTYPE m_uType;
	/* shader program code */
	string m_strCode;
	/* whether compiled */
	bool m_bCompiled;

	void checkError();
	void genShader();
};

#endif

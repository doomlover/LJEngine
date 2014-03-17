#include <GL/glew.h>
#include "LJGLSLShader.h"
#include "LJUtil.h"
#include <vector>

const UINT LJGLSLShader::ShaderType[2] = {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};

LJGLSLShader::LJGLSLShader():
	m_uHandle(-1),
	m_bCompiled(false),
	m_uType(LJ_VERTEX_SHADER)
{
}

LJGLSLShader::LJGLSLShader(const char* code, LJSHADERTYPE type):
		m_uType(type), m_strCode(code)
{
	genShader();
}

LJGLSLShader::~LJGLSLShader(void)
{
	glDeleteShader(m_uHandle);
}

void LJGLSLShader::SetCode(const char* code, LJSHADERTYPE type)
{
	if(code)
	{
		m_uType = type;
		m_strCode.assign(code);
	}
	if(m_uHandle < 0)
	{
		genShader();
	}
	glShaderSource(m_uHandle, 1, &code, NULL);
}

void LJGLSLShader::Compile(void)
{
	glCompileShader(m_uHandle);
	checkError();
	m_bCompiled = true;
}

int LJGLSLShader::GetHandle() const
{
	return m_uHandle;
}

LJGLSLShader::LJSHADERTYPE LJGLSLShader::GetType() const
{
	return m_uType;
}

string LJGLSLShader::GetCode() const
{
	return m_strCode;
}

/*
 * PRIVATE FUNCTIONS
 */
void LJGLSLShader::checkError()
{
	GLint ret = GL_FALSE;
	int infoLogLength;
	glGetShaderiv(m_uHandle, GL_COMPILE_STATUS, &ret);
	glGetShaderiv(m_uHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 1) {
		std::vector<char> vertexShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(m_uHandle, infoLogLength, NULL,
			&vertexShaderErrorMessage[0]);
		LJLog("LJGLSLShader", &vertexShaderErrorMessage[0]);
	}
}

void LJGLSLShader::genShader()
{
	m_uHandle = glCreateShader(ShaderType[m_uType]);
}

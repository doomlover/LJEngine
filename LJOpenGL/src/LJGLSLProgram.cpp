/*
 * LJGLSLProgram.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: liu
 */

#include <GL/glew.h>
#include "LJGLSLProgram.h"
#include "LJUtil.h"
#include <vector>

LJGLSLProgram::LJGLSLProgram()
:m_vsHandle(-1),
 m_fsHandle(-1),
 m_bNeedLink(true),
 m_nNumPasses(0)
{
	m_uHandle = glCreateProgram();
}

LJGLSLProgram::~LJGLSLProgram(void) {
	glDeleteProgram(m_uHandle);
	DeleteAllShaders();
}

void LJGLSLProgram::SetTechName(const char* name)
{
	if(name)
	{
		m_strTechName.assign(name);
	}
}

const char* LJGLSLProgram::GetTechName() const
{
	return m_strTechName.c_str();
}

void LJGLSLProgram::SetPassName(const char* name)
{
	if(name)
	{
		m_strPassName.assign(name);
	}
}

const char* LJGLSLProgram::GetPassName() const 
{
	return m_strPassName.c_str();
}

bool LJGLSLProgram::HasShader(const char* name) const
{
	SHADERMAP::const_iterator it = m_ShaderMap.find(string(name));
	return (it != m_ShaderMap.end());
}

void LJGLSLProgram::AddShaders(const char* chPassName, LJGLSLShader *vs, LJGLSLShader *fs)
{

	m_ShaderMap[string(chPassName)] = m_nNumPasses;
	m_vShaders.push_back(vs);
	m_fShaders.push_back(fs);
	++m_nNumPasses;
}

void LJGLSLProgram::GetShaders(const char* chPassName, LJGLSLShader **vs, LJGLSLShader **fs)
{
	SHADERMAP::const_iterator it = m_ShaderMap.find(string(chPassName));
	if(it != m_ShaderMap.end())
	{
		*vs = m_vShaders[it->second];
		*fs = m_fShaders[it->second];
	}
	else
	{
		*vs = *fs = NULL;
	}
}

HRESULT LJGLSLProgram::Use(void)
{
	glUseProgram(m_uHandle);
	return LJ_OK;
}

void LJGLSLProgram::Link(void)
{
	glLinkProgram(m_uHandle);
	checkError();
	m_bNeedLink = false;
}

bool LJGLSLProgram::IsNeedLink()
{
	return m_bNeedLink;
}

void LJGLSLProgram::AttachShader(LJGLSLShader& shader)
{
	if(!shader.IsCompiled())
	{
		shader.Compile();
	}
	int handle = shader.GetHandle();
	if(shader.GetType() == LJGLSLShader::LJ_VERTEX_SHADER)
	{
		m_vsHandle = handle;
	}
	else {
		m_fsHandle = handle;
	}
	glAttachShader(m_uHandle, handle);
}

void LJGLSLProgram::DetachFShader()
{
	if (m_fsHandle != -1)
	{
		glDetachShader(m_uHandle, m_fsHandle);
		// invalidate handle
		m_fsHandle = -1;
	}
	m_bNeedLink = true;
}

void LJGLSLProgram::DetachVShader()
{
	if (m_vsHandle != -1)
	{
		glDetachShader(m_uHandle, m_vsHandle);
		// invalidate handle
		m_vsHandle = -1;
	}
	m_bNeedLink = true;
}

void LJGLSLProgram::DetachAll()
{
	DetachVShader();
	DetachFShader();
}

void LJGLSLProgram::DeleteAllShaders()
{
	VSHADERS::iterator vs_it = m_vShaders.begin();
	while(vs_it != m_vShaders.end())
	{
		delete *vs_it;
		++vs_it;
	}
	m_vShaders.clear();
	FSHADERS::iterator fs_it = m_fShaders.begin();
	while(fs_it != m_fShaders.end())
	{
		delete *fs_it;
		++fs_it;
	}
	m_fShaders.clear();
	// reset number of passes to 0
	m_nNumPasses = 0;
	// clear shader map
	m_ShaderMap.clear();
}

void LJGLSLProgram::SetUniform(const char* name, UINT uVal)
{
	int location = getUniformLocation(name);
	if(location != -1)
		glUniform1ui(location, uVal);
}
void LJGLSLProgram::SetUniform(const char* name, float fVal)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniform1f(location, fVal);
}
void LJGLSLProgram::SetUniform(const char* name, float fVal0, float fVal1, float fVal2)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniform3f(location, fVal0, fVal1, fVal2);
}
void LJGLSLProgram::SetUniform(const char* name, int iVal)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniform1i(location, iVal);
}
void LJGLSLProgram::SetUniform(const char* name, bool bVal)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniform1i(location, bVal);
}
void LJGLSLProgram::SetUniform(const char* name, LJVector3& v3Val)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniform3fv(location, 1, &v3Val[0]);
}
void LJGLSLProgram::SetUniform(const char* name, LJVector4& v4Val)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniform4fv(location, 1, &v4Val[0]);
}
void LJGLSLProgram::SetUniform(const char* name, LJMatrix3& m3Val)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniformMatrix3fv(location, 1, GL_FALSE, &m3Val[0][0]);
}
void LJGLSLProgram::SetUniform(const char* name, LJMatrix4& m4Val)
{
	int location = getUniformLocation(name);
	if(location != -1)
	glUniformMatrix4fv(location, 1, GL_FALSE, &m4Val[0][0]);
}

void LJGLSLProgram::SetSubroutine(const char* name, LJGLSLShader::LJSHADERTYPE type)
{
	GLuint index = glGetSubroutineIndex(m_uHandle, LJGLSLShader::ShaderType[type],
		name);
	if(index != GL_INVALID_INDEX)
	{
		glUniformSubroutinesuiv(LJGLSLShader::ShaderType[type], 1, &index);
	}
}

int LJGLSLProgram::getAttribLocation(const char* chName)
{
	return glGetAttribLocation(m_uHandle, chName);
}


/*
 * PRIVATE FUNCTIONS
 */
void LJGLSLProgram::checkError()
{
	GLint ret;
	int infoLogLength;
	glGetProgramiv(m_uHandle, GL_LINK_STATUS, &ret);
	glGetProgramiv(m_uHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> programErrorMessage((infoLogLength > 1)? infoLogLength : 1);
	glGetProgramInfoLog(m_uHandle, infoLogLength, NULL, &programErrorMessage[0]);
	if(infoLogLength > 1)
	{
		LJLog("LJGLSLProgram", &programErrorMessage[0]);
	}
}

int LJGLSLProgram::getUniformLocation(const char* name)
{
	return glGetUniformLocation(m_uHandle, name);
}

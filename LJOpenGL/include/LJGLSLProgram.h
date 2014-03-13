#ifndef LJGLSLPROGRAM_H
#define LJGLSLPROGRAM_H

#include "LJGLSLShader.h"
#include "LJProgram.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;

class LJGLSLProgram : public LJProgram
{
public:
	LJGLSLProgram();
	~LJGLSLProgram(void);

	void SetTechName(const char* name);
	const char* GetTechName() const;
	void SetPassName(const char* name);
	const char* GetPassName() const;

	void Link(void);
	bool IsNeedLink();
	HRESULT Use(void);
	void AttachShader(LJGLSLShader& shader);
	void DetachFShader();
	void DetachVShader();
	void DetachAll();

	void SetUniform(const char* name, float fVal);
	void SetUniform(const char* name, float fVal0, float fVal1, float fVal2);
	void SetUniform(const char* name, int iVal);
	void SetUniform(const char* name, bool bVal);
	void SetUniform(const char* name, LJVector3& v3Val);
	void SetUniform(const char* name, LJVector4& v4Val);
	void SetUniform(const char* name, LJMatrix3& m3Val);
	void SetUniform(const char* name, LJMatrix4& m4Val);
	void SetSubroutine(const char* name, LJGLSLShader::LJSHADERTYPE type);
	void getAttribLocation(const char* chName, UINT* uLocation);
	// Whether already has the shader of the pass
	bool HasShader(const char* chPassName)const;
	// add shader
	void AddShaders(const char* chPassName, LJGLSLShader *vs, LJGLSLShader *fs);
	// get shader
	void GetShaders(const char* chPassName, LJGLSLShader **vs, LJGLSLShader **fs);
	// delete all shaders
	void DeleteAllShaders();
	// <shader name, shader index>
	typedef map<string, int> SHADERMAP;
	typedef vector<LJGLSLShader*> VSHADERS;
	typedef vector<LJGLSLShader*> FSHADERS;
private:
	/* GLSL program handle */
	UINT m_uHandle;
	/* Selected TEC name */
	string m_strTechName;
	/* VERT Shader in use */
	int m_vsHandle;
	/* FRAG Shader in use */
	int m_fsHandle;
	/* Need attach shader and link */
	bool m_bNeedLink;
	/* name of the pass currently in use */
	string m_strPassName;

	// shader map
	SHADERMAP m_ShaderMap;
	// vertex shader list
	VSHADERS m_vShaders;
	// fragment shader list
	FSHADERS m_fShaders;
	// number of passes
	int m_nNumPasses;

	void checkError();
	UINT getUniformLocation(const char* name);
};

#endif

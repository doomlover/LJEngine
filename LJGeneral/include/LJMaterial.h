#ifndef LJMATERIAL_H_
#define LJMATERIAL_H_

#include "LJGeneralHeaders.h"
#include "LJTechnique.h"
#include "LJTexture.h"

#include <cstdlib>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::string;

/*
 * Collection of effect parameters
 */
typedef enum LJMATPARAMTYPE
{	/* Build-in type */
	LJFLOAT,
	LJINT,
	LJBOOL,
	/* Vector */
	LJVECTOR3f,
	LJVECTOR4f,
	/* Matrix */
	LJMATRIX3f,
	LJMATRIX4f,
	/* Texture */
	LJTEXTURE,
	LJTEXTURE2D,
	//LJTEXTURE3D,
	LJTEXTURECUBE,
	/* SHADER PARAM */
	LJ_SHADER_SUBROUTINE,
	// do not use
	LJNUMMATPARAM,
} LJMatParamType;

class _LJExport LJMaterial
{
public:
	typedef vector<LJTechnique> LJTechniques;
	typedef vector<LJTexture> Textures;
	typedef map<string, UINT> TexIdMap;
	/*
	 * Use to hold the type and the memory address of a value.
	 * Only provide the reading methods
	 */
	class _LJExport LJMatParam
	{
		friend class LJMaterial;
		LJMatParamType m_Type;
		void *m_pVal;
		string *m_Name;
		int size;
	public:
		LJMatParam();
		~LJMatParam(void);
		LJMatParam(const LJMatParam& p);
		LJMatParam(const char* name, LJMatParamType type, const void* val, int size);
		LJMatParam& operator=(const LJMatParam& p);

		const LJMatParamType Type() const {return m_Type;}
		const void* Value() const {return m_pVal;}
		const string& Name() const {return *m_Name;}
	};
	typedef map<string,LJMatParam> LJMatParams;

	LJMaterial();
	LJMaterial(const LJMaterial& mat);
	~LJMaterial(void);
	LJMaterial& operator=(const LJMaterial& mat);
	/*
	 * set general type parameters
	 * new memory will be allocated to store the copy of the value.
	 * The new memory will be held by LJMatParam.
	 */
	template<typename T>
	void SetParam(const char* name, LJMatParamType type, const T& val);
	/*
	 * set texture type parameters
	 */
	void SetParam(const char* name, UINT texID);
	/*
	 * Add a technique
	 */
	void AddTechnique(const LJTechnique& tech);
	/*
	 * Get params
	 */
	const LJMatParams* GetParams() const;
	LJMatParams* GetParams();
	/*
	 * Return the parameter which has the specific name.
	 */
	const LJMatParam* GetParam(const char* name) const;
	LJMatParam* GetParam(const char* name);
	/*
	 * Return all techniques.
	 */
	const LJTechniques* GetTechniques() const {return m_Techniques;}
	LJTechniques* GetTechniques() {return m_Techniques;}
	/* 
	Set current technique in use 
	*/
	void SetCurrentTech(const string& name);
	/* 
	Get current in use technique 
	*/
	const LJTechnique* GetCurrentTech()const;
	LJTechnique* GetCurrentTech();
	/* 
	Get name of current tech 
	*/
	const char* GetTechName() const;
	/* 
	Get the texture at the index 
	*/
	UINT GetTexture(UINT index);
	/* 
	Get the texture with the specified name 
	*/
	UINT GetTexture(const char* name) const;
	UINT GetTexture(const char* name);
	/* 
	Get the number of textures which material has 
	*/
	int GetNumOfTextures() const {return m_nNumTextures;}
private:
	/* map of parameters */
	LJMatParams *m_pParams;
	/* list of techniques */
	LJTechniques *m_Techniques;
	/* number of textures */
	UINT m_nNumTextures;
	/* name of the current technique in use */
	string *m_strSelectedTech;
	/* list of texture ids */
	UINT m_nTextures[LJ_MAX_MATERIAL_TEXTURES];
	/* Map of texture id */
	TexIdMap *m_pTexIdMap;
	/* copy */
	void copy(const LJMaterial& mat);
	/* initialize */
	void init();
	/* finding current technique helper */
	LJTechnique* InterGetCurrentTech() const;
	/* helper of finding a named texture */
	UINT InterGetTexture(const char* name) const;
};

/*
 * template function for non-texture parameters
*/
template<typename T>
void LJMaterial::SetParam(const char* name, LJMatParamType type, const T& val)
{
	if(!name)
	{
		throw "LJMaterial : SetParam, Invalid name";
	}

	if (type == LJTEXTURE)
	{
		throw "LJMaterial : SetParam, Use SetParam(name, tex)";
	}
	T *pVal;
	// make a copy of the value
	pVal = (T*) malloc(sizeof(T));
	if (!pVal)
	{
		throw "Bad memory allocation";
	}
	*pVal = val;
	// create new parameter
	LJMatParam Param;
	// set type, name and value
	Param.m_Type = type;
	Param.m_Name->assign(name);
	Param.m_pVal = pVal;
	Param.size = sizeof(T);
	// store in the material
	(*m_pParams)[*Param.m_Name] = Param;
}

#endif /* LJMATERIAL_H_ */

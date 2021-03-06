#include <LJMaterial.h>
#include <cstring>

void LJMaterial::init()
{
	m_strSelectedTech = new string("");
	m_Techniques = new LJTechniques();
	m_pParams = new LJMatParams();
	m_pTexIdMap = new TexIdMap();
	for(UINT i = 0; i < LJ_MAX_MATERIAL_TEXTURES; ++i)
	{
		m_nTextures[i] = LJ_MAX_ID;
	}
}
/*
 * Constructor
 */
LJMaterial::LJMaterial()
:m_nNumTextures(0)
{
	init();
}
/*
 * Copy constructor
 */
LJMaterial::LJMaterial(const LJMaterial& mat)
{
	init();
	copy(mat);
}
/*
 * Destroy
 */
LJMaterial::~LJMaterial(void)
{
	cout << "~LJMaterial" << endl;
	/* delete all parameters */
	if(m_pParams)
	{
		delete m_pParams;
	}
	/* delete all techniques */
	if(m_Techniques)
	{
		delete m_Techniques;
	}
	if(m_strSelectedTech)
	{
		delete m_strSelectedTech;
	}
	if(m_pTexIdMap)
	{
		delete m_pTexIdMap;
	}
}
/*
 * operator =
 */
LJMaterial& LJMaterial::operator=(const LJMaterial& mat)
{
	copy(mat);
	return *this;
}
/*
 * Add a technique
 */
void LJMaterial::AddTechnique(const LJTechnique& tech)
{
	m_Techniques->push_back(tech);
}
/*
 * Get parameter list
 */
const LJMaterial::LJMatParams* LJMaterial::GetParams() const
{
	return m_pParams;
}

LJMaterial::LJMatParams* LJMaterial::GetParams()
{
	return m_pParams;
}
/*
 * Find a parameter by name
 */
const LJMaterial::LJMatParam* LJMaterial::GetParam(const char* name) const
{
	if(name)
	{
		LJMatParams::const_iterator it = m_pParams->find(string(name));
		if(it != m_pParams->end())
		{
			return &(it->second);
		}
	}
	return NULL;
}
LJMaterial::LJMatParam* LJMaterial::GetParam(const char* name)
{
	if(name)
	{
		LJMatParams::iterator it = m_pParams->find(string(name));
		if(it != m_pParams->end())
		{
			return &(it->second);
		}
	}
	return NULL;
}
/*
 * Set the name of the technique going to be used
 */
void LJMaterial::SetCurrentTech(const string& name)
{
	 *m_strSelectedTech = name;
}
/*
 * Private helper of finding current technique
 */
LJTechnique* LJMaterial::InterGetCurrentTech() const
{
	if(!m_strSelectedTech)
		return NULL;

	LJTechniques::iterator it = m_Techniques->begin();
	while(it != m_Techniques->end())
	{
		if(strcmp((*it).GetName(), (const char*)m_strSelectedTech->c_str()) == 0)
		{
			return &(*it);
		}
		++it;
	}
	return NULL;
}
/*
 * Get current technique in use
 */
const LJTechnique* LJMaterial::GetCurrentTech() const
{
	return InterGetCurrentTech();
}
LJTechnique* LJMaterial::GetCurrentTech()
{
	return InterGetCurrentTech();
}
/*
 * Get current technique name
 */
const char* LJMaterial::GetTechName() const
{
	if(m_strSelectedTech)
	{
		return m_strSelectedTech->c_str();
	}
	return NULL;
}
/*
 * Set texture parameter
 */
void LJMaterial::SetParam(const char* name, UINT texID)
{
		if(!name || texID == LJ_MAX_ID) throw "INVALID PARAMETER";
		// can add a texture
		if (m_nNumTextures < LJ_MAX_MATERIAL_TEXTURES)
		{
			// set id map
			(*m_pTexIdMap)[string(name)] = texID;
			// set texture unit indexed id
			m_nTextures[m_nNumTextures] = texID;
			// increase the number of textures
			m_nNumTextures++;
			// create new parameter
			LJMatParam pParam;
			// set type, name and value
			LJMatParamType type = LJTEXTURE;
			pParam.m_Type = type;
			pParam.m_Name->assign(name);
			pParam.size = sizeof(int);
			// store the texture index as texture unit number in parameter
			pParam.m_pVal = malloc(pParam.size);
			if(!pParam.m_pVal)
			{
				throw "BAD MEMORY ALLOCATION";
			}
			*static_cast<int*>(pParam.m_pVal) = m_nNumTextures-1;
			// store in the material
			(*m_pParams)[*pParam.m_Name] = pParam;
		}
		else {
			throw "LJMaterial::SetParam, WARNING : NO MORE TEXTURES CAN BE ADDED";
		}
}
/*
 * Get the id of texture at index
 */
UINT LJMaterial::GetTexture(UINT index)
{
	if(index < LJ_MAX_MATERIAL_TEXTURES)
	{
		return m_nTextures[index];
	}
	return LJ_MAX_ID;
}
/*
 * Get the texture with the specified name
 */
UINT LJMaterial::GetTexture(const char* name) const
{

	return InterGetTexture(name);
}
UINT LJMaterial::GetTexture(const char* name)
{
	return InterGetTexture(name);
}
UINT LJMaterial::InterGetTexture(const char* name) const
{
	if(name)
	{
		TexIdMap::const_iterator it = m_pTexIdMap->find(string(name));
		if(it != m_pTexIdMap->end())
		{
			return it->second;
		}
		return LJ_MAX_ID;
	}
	return LJ_MAX_ID;
}
/*
 * PRIVATE FUNCTION
 * copy mat
 */
void LJMaterial::copy(const LJMaterial& mat)
{
	// copy parameters
	*m_pParams = *mat.GetParams();
	// copy techniques
	*m_Techniques = *mat.GetTechniques();
	// copy number of textures
	m_nNumTextures = mat.GetNumOfTextures();
	// copy selected technique
	m_strSelectedTech->assign(mat.GetTechName());
	// copy texture ids
	memcpy(m_nTextures, mat.m_nTextures, LJ_MAX_MATERIAL_TEXTURES*sizeof(UINT));
	// copy id map
	*m_pTexIdMap = *mat.m_pTexIdMap;
}

/*******************************************************
 *                   LJMatParam
 ********************************************************/
LJMaterial::LJMatParam::LJMatParam()
:m_Type(LJNUMMATPARAM),m_pVal(NULL),size(0)
{
	m_Name = new string("");
}

LJMaterial::LJMatParam::LJMatParam(const char* name, LJMatParamType type, const void* val, int size)
:m_Type(LJNUMMATPARAM),m_pVal(NULL),size(0)
{
	// name
	if(name)
	{
		m_Name = new string(name);
	}
	else {
		m_Name = new string("");
	}
	// type
	m_Type = type;
	// size
	this->size = size;
	// value
	if(size > 0)
	{
		m_pVal = malloc(size);
		if(!m_pVal)
			throw "Bad memory allocation";
		memcpy(m_pVal, val, size);
	}
}

LJMaterial::LJMatParam::LJMatParam(const LJMatParam& p)
{
	m_Name = new string("");
	m_Type = p.m_Type;
	size = p.size;
	*m_Name = *p.m_Name;
	if(p.m_pVal)
	{
		m_pVal = malloc(size);
		if(m_pVal) memcpy(m_pVal, p.m_pVal, size);
		else m_pVal = NULL;
	}
	else{
		m_pVal = NULL;
	}
}
LJMaterial::LJMatParam::~LJMatParam(void){
	if(m_pVal)
	{
		free(m_pVal);m_pVal = NULL;
	}
	if(m_Name)
	{
		delete m_Name;
	}
}
LJMaterial::LJMatParam& LJMaterial::LJMatParam::operator=(const LJMatParam& p)
{
	m_Type = p.m_Type;
	size = p.size;
	*m_Name = *p.m_Name;
	if(p.m_pVal)
	{
		m_pVal = malloc(size);
		if(m_pVal) memcpy(m_pVal, p.m_pVal, size);
		else m_pVal = NULL;
	}
	else{
		m_pVal = NULL;
	}
	return *this;
}

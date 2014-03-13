#include <LJUtil.h>
#include <LJTexture.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

LJTexture::LJTEXPARAMCONFS LJTexture::InitDefaultParams()
{
	LJTEXPARAMCONFS params;
	params.push_back( LJTEXPARAMCONF(LJ_TEXTURE_MIN_FILTER, LJ_LINEAR) );
	params.push_back( LJTEXPARAMCONF(LJ_TEXTURE_MAG_FILTER, LJ_LINEAR) );
	params.push_back( LJTEXPARAMCONF(LJ_TEXTURE_WRAP_S, LJ_REPEAT) );
	params.push_back( LJTEXPARAMCONF(LJ_TEXTURE_WRAP_T, LJ_REPEAT) );
	params.push_back( LJTEXPARAMCONF(LJ_TEXTURE_WRAP_R, LJ_REPEAT) );
	return params;
}

LJTexture::LJTEXPARAMCONFS LJTexture::m_DefaultParams = LJTexture::InitDefaultParams();

void LJTexture::init()
{
	m_fAlpha = 1.0f;
	m_pClrKeys = NULL;
	m_dwNum = 0;
	m_bAlpha = false;
	m_Target = LJ_TEXTURE_NO_TARGET;
	m_bUpdateParam = false;
	m_id = -1;
	m_bNeedUpdate = false;
	m_Params = new LJTEXPARAMCONFS();
	m_ImageList = new ImageList();
	m_pName = new string();
}
/*
 * Constructor
 */
LJTexture::LJTexture()
{
	init();
}
/*
 * Copy Constructor
 */
LJTexture::LJTexture(const LJTexture& tex)
{
	init();

	SetColorKeys(tex.m_pClrKeys, tex.m_dwNum);
	m_fAlpha=tex.m_fAlpha;
	m_bAlpha=tex.m_bAlpha;
	m_Target=tex.m_Target;
	*m_Params = *tex.m_Params;
	m_bUpdateParam = tex.m_bUpdateParam;
	m_bNeedUpdate = tex.m_bNeedUpdate;
	*m_ImageList = *tex.m_ImageList;
	*m_pName = *tex.m_pName;
}
/*
 * DESTRUCTOR
 */
LJTexture::~LJTexture(void)
{
	if(m_pClrKeys)
	{
		delete[] m_pClrKeys;
		m_pClrKeys = NULL;
	}
	if(m_Params)
	{
		delete m_Params;
	}
	if(m_ImageList)
	{
		delete m_ImageList;
	}
	if(m_pName)
	{
		delete m_pName;
	}
}

void LJTexture::SetParameter(LJTEXPNAME pname, LJTEXPARAM param)
{
	LJTEXPARAMCONF paramConf(pname, param);
	m_Params->push_back(paramConf);
	m_bUpdateParam = true;
}


const LJTexture::LJTEXPARAMCONFS& LJTexture::GetParams() const
{
	return *m_Params;
}

void LJTexture::SetTarget(LJTEXTARGET target)
{
	if(target == LJ_TEXTURE_NO_TARGET) {
		LJLog("LJTexture", "SetTarget : WARNING NO TARGET SET");
	}
	m_Target = target;
}
/*
 * Copy color keys into texture
 */
void LJTexture::SetColorKeys(const LJCOLOR* clrKeys, DWORD dwNum)
{
	if(dwNum <= 0 || clrKeys == NULL)
	{
		LJLog("LJTexture::SetColorKeys", "NO COLOR KEYS SEND IN");
		return ;
	}

	if(dwNum != m_dwNum)
	{
		m_dwNum = dwNum;
	}
	// Cache the old Keys
	LJCOLOR *pTmp = m_pClrKeys;
	// Memory for new Keys
	m_pClrKeys = new LJCOLOR[dwNum];
	// Delete the old if any
	if(pTmp != NULL)
	{
		delete[] pTmp;
		pTmp = NULL;
	}
	// Copy the data
	memcpy(m_pClrKeys, clrKeys, dwNum*sizeof(LJCOLOR));
	if(m_ImageList->size()>0)
	{
		if(!m_bNeedUpdate)
			m_bNeedUpdate = true;
	}
}

void LJTexture::SetAlpha(float fAlpha)
{
	m_fAlpha = fAlpha;
	if(fAlpha < 1.0 && m_ImageList->size() > 0)
	{
		if(!m_bNeedUpdate)
			m_bNeedUpdate = true;
	}
}

LJCOLOR* LJTexture::GetColorKeys(DWORD* dwNum)
{
	if(dwNum == NULL)
	{
		LJLog("LJTexture::GetColorKeys", "No place to return number of color keys. Return NULL");
		return NULL;
	}
	*dwNum = m_dwNum;
	return m_pClrKeys;
}

HRESULT LJTexture::AddImage(const char* img)
{
	if(!img) return LJ_FAIL;
	m_ImageList->push_back(string(img));
	if(!m_bNeedUpdate)
		m_bNeedUpdate = true;
	return LJ_OK;
}

const char* LJTexture::GetImage(int index) const
{
	ImageList::size_type ind = index;
	if(ind < 0 || ind >= m_ImageList->size()) return NULL;
	return (*m_ImageList)[ind].c_str();
}

void LJTexture::SetName(const char* name)
{
	if(name)
		m_pName->assign(name);
}

const char* LJTexture::GetName() const {
	return m_pName->c_str();
}

void LJTexture::SetDefaultParams()
{
	*m_Params = m_DefaultParams;
	m_bUpdateParam = true;
}

LJTexture& LJTexture::operator=(const LJTexture& tex)
{
	LJLog("LJTexture", "operator=");
	SetColorKeys(tex.m_pClrKeys, tex.m_dwNum);
	m_fAlpha = tex.m_fAlpha;
	m_bAlpha = tex.m_bAlpha;
	m_Target = tex.m_Target;
	*m_Params = *tex.m_Params;
	m_bUpdateParam = tex.m_bUpdateParam;
	*m_ImageList = *tex.m_ImageList;
	m_bNeedUpdate = tex.m_bNeedUpdate;
	*m_pName = *tex.m_pName;
	return *this;
}

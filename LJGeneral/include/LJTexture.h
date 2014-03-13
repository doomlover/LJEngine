#ifndef LJTEXTURE_H_
#define LJTEXTURE_H_

#include "LJGeneralHeaders.h"
#include "LJTextureManager.h"
#include <vector>
using std::vector;
#include <string>
using std::string;

typedef enum LJTEXTARGET_TYPE{
		LJ_TEXTURE_2D = 0,
		LJ_TEXTURE_3D,
		LJ_TEXTURE_CUBE_MAP,
		LJ_TEXTURE_NO_TARGET
} LJTEXTARGET;

/* NOTICE: ORDER SENSITIVE, DO NOT MODIFY UNTIL YOU KNOWE WHAT YOU ARE DOING */
typedef enum _LJTEXPNAME
{
	LJ_TEXTURE_COMPARE_FUNC,
	LJ_TEXTURE_COMPARE_MODE,
	LJ_TEXTURE_MIN_FILTER,
	LJ_TEXTURE_MAG_FILTER,
	LJ_TEXTURE_WRAP_S,
	LJ_TEXTURE_WRAP_T,
	LJ_TEXTURE_WRAP_R
} LJTEXPNAME;

typedef enum _LJTEXPARAM
{
	LJ_LINEAR = 0,
	LJ_NEAREST,
	LJ_NEAREST_MIPMAP_NEAREST,
	LJ_LINEAR_MIPMAP_NEAREST,
	LJ_NEAREST_MIPMAP_LINEAR,
	LJ_LINEAR_MIPMAP_LINEAR,
	LJ_COMPARE_REF_TO_TEXTURE,
	LJ_CLAMP_TO_EDGE,
	LJ_CLAMP_TO_BORDER,
	LJ_MIRRORED_REPEAT,
	LJ_REPEAT,
	LJ_MIRROR_CLAMP_TO_EDGE

} LJTEXPARAM;

class _LJExport LJTEXPARAMCONF
{
public:
	LJTEXPNAME pname;
	LJTEXPARAM param;
	LJTEXPARAMCONF(LJTEXPNAME pn, LJTEXPARAM pa):pname(pn),param(pa){}
};

typedef vector<string> ImageList;

class _LJExport LJTexture
{
public:
	typedef vector<LJTEXPARAMCONF> LJTEXPARAMCONFS;

	LJTexture();
	/*
	 * Copy Constructor
	 */
	LJTexture(const LJTexture& tex);
	~LJTexture(void);
	void SetParameter(LJTEXPNAME pname, LJTEXPARAM param);
	void SetAlpha(float fAlpha);
	void SetBlend(bool bBlend){m_bAlpha = bBlend;}
	void SetTarget(LJTEXTARGET target);
	void SetColorKeys(const LJCOLOR* clrKeys, DWORD dwNum);
	void SetUpdateParam(bool bUpdated){m_bUpdateParam = bUpdated;}

	bool IsUpdateParam()const {return m_bUpdateParam;}
	const LJTEXPARAMCONFS& GetParams() const;
	LJTEXTARGET GetTarget() const {return m_Target;}
	LJCOLOR* GetColorKeys(DWORD* dwNum);
	float GetAlpha() const { return m_fAlpha;}
	bool IsBlend() const {return m_bAlpha;}

	HRESULT AddImage(const char* img);
	const char* GetImage(int index) const;

	int GetId()const {return m_id;}
	void SetId(int id) {m_id = id;}

	bool IsNeedUpdate() const {return m_bNeedUpdate;}
	void SetNeedUpdate(bool up) {m_bNeedUpdate = up;}

	void SetName(const char* name);
	const char* GetName() const;

	void SetDefaultParams();

	LJTexture& operator=(const LJTexture& tex);

	static LJTEXPARAMCONFS m_DefaultParams;
protected :
	float m_fAlpha;					// Overall transparency
	LJCOLOR *m_pClrKeys;			// Color key array
	DWORD m_dwNum;					// Number of color keys
	bool m_bAlpha;					// Need alpha blending
	LJTEXTARGET m_Target; 			// Target texture
	LJTEXPARAMCONFS *m_Params;		// Texture parameters
	bool m_bUpdateParam;
	ImageList *m_ImageList;			// image file name list
	bool m_bNeedUpdate;
	int m_id;
	string *m_pName;

	void init();

	static LJTEXPARAMCONFS InitDefaultParams();
};


#endif /* LJTEXTURE_H_ */

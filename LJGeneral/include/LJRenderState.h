#ifndef LJRENDERSTATE_H_
#define LJRENDERSTATE_H_

#include "LJGeneralHeaders.h"
#include "LJMath.h"

class _LJExport LJRenderState
{
public:
	/*
	 *  Render States
	 */
	typedef enum _LJ_RENDER_STAGE_CAP
	{
		LJ_BLEND_CAP,		// 1, 0
		LJ_DEPTH_CAP,	// 1, 0
		LJ_DITHER_CAP,	// 1, 0
		LJ_SCISSOR_CAP,	// 1, 0
		LJ_STENCIL_CAP,	// 1, 0
		LJ_CULL_FACE_CAP
	} LJ_RENDER_STATE_CAP;

	typedef enum _LJ_CULL_FACE_MODE
	{
		LJ_FRONT,
		LJ_BACK,
		LJ_FRONT_BACK
	} LJ_CULL_FACE_MODE;

	typedef enum _LJ_FRONT_FACE_MODE
	{
		LJ_CW,
		LJ_CCW
	} LJ_FRONT_FACE_MODE;

	typedef enum _LJ_DEPTH_FUNC
	{
		LJ_NEVER,
		LJ_LESS,
		LJ_EQUAL,
		LJ_LEQUAL,
		LJ_GREATER,
		LJ_NOTEQUAL,
		LJ_GEQUAL,
		LJ_ALWAYS,
	} LJ_DEPTH_FUNC;

	typedef enum _LJ_BLEND_FUNC
	{
		LJ_ZERO,
		LJ_ONE,
		LJ_SRC_COLOR,
		LJ_ONE_MINUS_SRC_COLOR,
		LJ_DST_COLOR,
		LJ_ONE_MINUS_DST_COLOR,
		LJ_SRC_ALPHA,
		LJ_ONE_MINUS_SRC_ALPHA,
		LJ_DST_ALPHA,
		LJ_ONE_MINUS_DST_ALPHA,
		LJ_CONSTANT_COLOR,
		LJ_ONE_MINUS_CONSTANT_COLOR,
		LJ_CONSTANT_ALPHA,
		LJ_ONE_MINUS_CONSTANT_ALPHA,
	} LJ_BLEND_FUNC;

	typedef enum _LJ_BLEND_EQ
	{
		LJ_ADD,
		LJ_SUB,
		LJ_FUNC_REV_SUB,
		LJ_MIN,
		LJ_MAX
	} LJ_BLEND_EQ;

	typedef enum _LJ_POLYGON_MODE
	{
		LJ_POINT,
		LJ_LINE,
		LJ_FILL
	} LJ_POLYGON_MODE;

	// color mask type
	typedef struct _LJExport _COLOR_MASK
	{
		bool r, g, b, a;
		_COLOR_MASK():r(true),g(true),b(true),a(true){}
		_COLOR_MASK(bool r_, bool g_, bool b_, bool a_):
			r(r_),g(g_),b(b_),a(a_){}
	} COLORMASK;
	// depth range type
	typedef struct _LJExport _DEPTHRANGE
	{
		float x, y;	
		_DEPTHRANGE(float _x, float _y):x(_x),y(_y){}
	} DEPTHRANGE;
	// color type
	typedef LJCOLOR BLENDCOLOR;

	LJRenderState();
	~LJRenderState(void){}
	bool IsBlendEnabled()const {return m_bBlend;}
	bool IsDepthEnabled()const {return m_bDepth;}
	bool IsDitherEnabled()const {return m_bDither;}
	bool IsScissorEnabled()const {return m_bScissor;}
	bool IsCullFaceEnabled()const {return m_bCullFace;}
	bool IsStencilEnabled()const {return m_bStencil;}

	void SetBlend(bool flag) {m_bBlend = flag;}
	void SetDepth(bool flag) {m_bDepth = flag;}
	void SetDither(bool flag){m_bDither = flag;}
	void SetScissor(bool flag){m_bScissor = flag;}
	void SetCullFace(bool flag) {m_bCullFace = flag;}
	void SetStencil(bool flag) {m_bStencil = flag;}

	LJ_CULL_FACE_MODE GetCullFaceMode()const {return m_CullFaceMode;}
	LJ_FRONT_FACE_MODE GetFrontFaceMode()const {return m_FrontFaceMode;}
	LJ_DEPTH_FUNC GetDepthFunc()const {return m_DepthFunc;}
	LJ_BLEND_FUNC GetBlendFuncSrc()const {return m_BlendFuncSrc;}
	LJ_BLEND_FUNC GetBlendFuncDes()const {return m_BlendFuncDes;}
	LJ_POLYGON_MODE GetPolygonMode()const {return m_PolygonMode;}
	LJ_BLEND_EQ GetBlendEq()const {return m_BlendEq;}
	COLORMASK GetColorMask() const {return m_ColorMask;}
	DEPTHRANGE GetDepthRange() const {return m_DepthRange;}
	BLENDCOLOR GetBlendColor() const {return m_BlendColor;}
	bool GetDepthMask()const {return m_bDepthMask;}
	float GetLineWidth()const {return m_fLineWidth;}
	float GetPointSize()const {return m_fPointSize;}

	void SetCullFaceMode(LJ_CULL_FACE_MODE mode) {m_CullFaceMode = mode;}
	void SetFrontFaceMode(LJ_FRONT_FACE_MODE mode) {m_FrontFaceMode = mode;}
	void SetDepthFunc(LJ_DEPTH_FUNC func) {m_DepthFunc = func;}
	void SetBlendFuncSrc(LJ_BLEND_FUNC func) {m_BlendFuncSrc = func;}
	void SetBlendFuncDes(LJ_BLEND_FUNC func) {m_BlendFuncDes = func;}
	void SetPolygonMode(LJ_POLYGON_MODE mode) {m_PolygonMode = mode;}
	void SetBlendEq(LJ_BLEND_EQ eq) {m_BlendEq = eq	;}
	void SetColorMask(const COLORMASK& colorMask) {m_ColorMask = colorMask;}
	void SetDepthRange(const DEPTHRANGE& depthRange) {m_DepthRange = depthRange;}
	void SetBlendColor(const BLENDCOLOR& blendColor) {m_BlendColor = blendColor;}
	void SetDepthMask(bool mask) {m_bDepthMask = mask;}
	void SetLineWidth(float width) {m_fLineWidth = width;}
	void SetPointSize(float size) {m_fPointSize = size;}

private:
	// caps settings
	bool m_bBlend;
	bool m_bDepth;
	bool m_bDither;
	bool m_bScissor;
	bool m_bCullFace;
	bool m_bStencil;

	LJ_CULL_FACE_MODE m_CullFaceMode;
	LJ_FRONT_FACE_MODE m_FrontFaceMode;
	LJ_DEPTH_FUNC m_DepthFunc;
	LJ_BLEND_FUNC m_BlendFuncSrc;
	LJ_BLEND_FUNC m_BlendFuncDes;
	LJ_POLYGON_MODE m_PolygonMode;
	LJ_BLEND_EQ m_BlendEq;

	COLORMASK m_ColorMask;
	DEPTHRANGE m_DepthRange;
	BLENDCOLOR m_BlendColor;
	bool m_bDepthMask;
	float m_fLineWidth;
	float m_fPointSize;
};

#endif /* LJRENDERSTATE_H_ */

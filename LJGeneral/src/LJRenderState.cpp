#include "LJRenderState.h"
#include <cstdio>

LJRenderState::LJRenderState()
:m_bBlend(false),
 m_bDepth(false),
 m_bDither(true),
 m_bScissor(false),
 m_bCullFace(false),
 m_bStencil(false),
 m_CullFaceMode(LJ_BACK),
 m_FrontFaceMode(LJ_CCW),
 m_DepthFunc(LJ_LESS),
 m_BlendFuncSrc(LJ_ONE),
 m_BlendFuncDes(LJ_ZERO),
 m_PolygonMode(LJ_FILL),
 m_BlendEq(LJ_ADD),
 m_DepthRange(0.f, 1.f),
 m_bDepthMask(true),
 m_fLineWidth(1.0f),
 m_fPointSize(1.0f)
{
}

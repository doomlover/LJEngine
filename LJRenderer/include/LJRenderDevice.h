/*
 * LJRenderDevice.h
 *
 *  Created on: 2013.7.28
 *      Author: Liu
 */

#ifndef LJRENDERDEVICE_H_
#define LJRENDERDEVICE_H_


#include "LJGeneralHeaders.h"
#include "LJRenderManager.h"
#include "LJTextureManager.h"
#include "LJMaterialManager.h"
#include <cstdio>

class LJMesh;
class LJGeometry;
class LJRenderState;

#define MAX_3DHWND 8

	enum LJSTAGE_ENUM{
		LJ_STAGE_3D0 = 0,
		LJ_STAGE_3D1,
		LJ_STAGE_3D2,
		LJ_STAGE_3D3,
		LJ_STAGE_MAX
	};
	typedef LJSTAGE_ENUM LJSTAGE;

class LJRenderDevice
{
protected:

public:
	virtual ~LJRenderDevice(void){};

	virtual HRESULT Init(HWND, const HWND*, int, int, int, bool) = 0;
	virtual void Release(void) = 0;
	virtual bool IsRunning(void) = 0;

	virtual HRESULT UseWindow(UINT nHwnd) = 0;
	virtual HRESULT BeginRendering(bool bClearPixel,
								   bool bClearDepth,
								   bool bClearStencil) = 0;
	virtual void EndRendering(void) = 0;
	virtual HRESULT Clear(bool bClearPixel,
							bool bClearDepth,
							bool bClearStencil) = 0;
	virtual void SetClearColor(float fRed,
								float fGreen,
								float fBlue) = 0;
	virtual LJRenderManager* GetRenderManager(void) = 0;
	virtual LJMaterialManager* GetMaterialManager(void) const = 0;

	/* =========== Create View Matrix =========== */
	// Set camera setting with Right, Up, Dir, Pos
	virtual void SetCamera(const LJVector3& v3Right, const LJVector3& v3Up, const LJVector3& v3Dir, LJVector3 v3Pos) = 0;
	// Set camera setting with Pos, Lookat, Up
	virtual void SetCamera(const LJVector3& v3Pos, const LJVector3& v3Lookat, const LJVector3 v3Up) = 0;
	// Directly set
	virtual void SetCamera(LJMatrix4& viewMatrix) = 0;

	/* =========== Create projection stage =========== */
	// All stage use same Near clip plane and Far clip plane
	virtual void SetNearFarClip(float fNear, float fFar) = 0;
	// Set from feild of view
	virtual void InitStage(float fFov, float fAspRatio, LJSTAGE stage) = 0;
	// Set from Right, Left, Top, Bottom clip planes
	virtual void InitStage(float fL, float fR, float fT, float fB, LJSTAGE stage) = 0;
	// Directly set
	virtual void InitStage(LJMatrix4& persMatrix, LJMatrix4& orthMatrix, LJSTAGE stage) = 0;
	// Set stage viewport
	virtual void SetViewport(LJSTAGE stage, LJVIEWPORT& viewport) = 0;
	// Choose which stage is about to be used and the projection mode which is perspective or orthogonal.
	// If the projection mode is "World equals to Screen", the Stage parameter is ignored
	virtual HRESULT UseStage(LJDIMENSIONMODE mode, LJSTAGE nStage) = 0;

	/* Set Local-to-World Matrix */
	virtual void SetWorldMatrix(LJMatrix4& matWorld) = 0;

	// Extracting frustum planes
	virtual HRESULT ExtractFrustumPlanes(LJVector4*) = 0;
	// Translate screen coordinates to world space
	virtual void ScreenToWorld(const LJVector2& sPos, LJVector3& wPos) = 0;
	// Transform world coordinates to screen space
	virtual void WorldToScreen(const LJVector3& wPos, LJVector2& sPos) = 0;

	virtual void SetWindowSize(int nWidth, int nHeight) = 0;
	/* Draw a mesh */
	virtual HRESULT RenderMesh(LJMesh& mesh) = 0;
	/* Setup a texture */
	virtual HRESULT ApplyTexture(LJTexture& tex, int texUnit) = 0;
	/* Get World Matrix */
	virtual LJMatrix4 GetWorldMatrix() = 0;
	/* Get View Matrix 3D */
	virtual LJMatrix4 GetViewMatrix3D() = 0;
	/* Get View Matrix 2D */
	virtual LJMatrix4 GetViewMatrix2D() = 0;
	/* Get Projection Matrix */
	virtual LJMatrix4 GetProjectionMatrix(LJDIMENSIONMODE mode, LJSTAGE nStage) = 0;
	/* Setup Render State */
	virtual void ApplyRenderState(const LJRenderState& renderState) = 0;
	/* Setup material */
	virtual HRESULT ApplyMaterial(int nMaterial) = 0;
	/* render a geometry */
	virtual HRESULT RenderGeometry(LJGeometry& geo) = 0;
};
typedef LJRenderDevice *LPLJRENDERDEVICE;

extern "C"
{
	typedef HRESULT (*CREATERENDERDEVICE) (LJRenderDevice **pInterface);
	typedef HRESULT (*RELEASERENDERDEVICE) (LJRenderDevice **pInterface);
}

#endif /* LJRENDERDEVICE_H_ */

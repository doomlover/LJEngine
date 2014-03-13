/*
 * LJOpenGL.h
 *
 *  Created on: 2013.7.28
 *      Author: Liu
 */

#ifndef LJOPENGL_H_
#define LJOPENGL_H_

#include <GL/glew.h>
#include "LJRendererHeaders.h"
#include "LJRenderDevice.h"
#include "LJPass.h"
#include "LJMaterial.h"

class LJRenderManager;
class LJOGLTextureManager;
class LJOGLMaterialManager;
class LJInterSkinManager;
class LJInterTextureManager;
class LJGLSLProgram;
class LJProgramManager;
class LJImageManager;

class LJOpenGL : public LJRenderDevice
{
public:
	LJOpenGL(void);
	~LJOpenGL(void);

	HRESULT Init(HWND, const HWND*, int, int, int, bool);
	void Release(void);
	bool IsRunning(void){ return m_bRunning; }
	HRESULT BeginRendering(bool, bool, bool);
	HRESULT Clear(bool, bool, bool);
	void EndRendering(void);
	void SetClearColor(float, float, float);
	HRESULT UseWindow(UINT nHwnd);
	LJRenderManager* GetRenderManager(void);
	LJMaterialManager* GetMaterialManager(void)const;
	LJProgramManager* GetInterProgManager(void)const;

	// Set camera setting with Right, Up, Direction, Position
	void SetCamera(const LJVector3& v3Right, const LJVector3& v3Up, const LJVector3& v3Dir, LJVector3 v3Pos);
	// Set camera setting with Position, Look-at, Up
	void SetCamera(const LJVector3& v3Pos, const LJVector3& v3Lookat, const LJVector3 v3Up);
	// Directly set
	void SetCamera(LJMatrix4& viewMatrix);

	// All stage use same Near clip plane and Far clip plane
	void SetNearFarClip(float fNear, float fFar);
	// Set from field of view
	void InitStage(float fFov, float fAspRatio, LJSTAGE stage);
	// Set from Right, Left, Top, Bottom clip planes
	void InitStage(float fL, float fR, float fT, float fB, LJSTAGE stage);
	// Directly set
	void InitStage(LJMatrix4& persMatrix, LJMatrix4& orthMatrix, LJSTAGE stage);
	// Set stage View-Port
	void SetViewport(LJSTAGE stage, LJVIEWPORT& viewport);
	// Set mode and stage
	HRESULT UseStage(LJDIMENSIONMODE mode, LJSTAGE nStage);
	/* Set Local-to-World Matrix */
	void SetWorldMatrix(LJMatrix4& matWorld);
	// Extracting Frustum planes
	HRESULT ExtractFrustumPlanes(LJVector4*);
	// Translate screen coordinates to world space
	void ScreenToWorld(const LJVector2& sPos, LJVector3& wPos);
	// Transform world coordinates to screen space
	void WorldToScreen(const LJVector3& wPos, LJVector2& sPos);
	// set window size
	void SetWindowSize(int nWidth, int nHeight);
	/* Draw a mesh */
	HRESULT RenderMesh(LJMesh& mesh);
	/* Setup a texture */
	HRESULT ApplyTexture(LJTexture& tex, int texUnit);
	/* Get World Matrix */
	LJMatrix4 GetWorldMatrix();
	/* Get View Matrix 3D */
	LJMatrix4 GetViewMatrix3D();
	/* Get View Matrix 2D */
	LJMatrix4 GetViewMatrix2D();
	/* Get Projection Matrix */
	LJMatrix4 GetProjectionMatrix(LJDIMENSIONMODE mode, LJSTAGE nStage);
	/* Get View Projection Matrix */
	LJMatrix4 GetViewProjectionMatrix();
	/* Get World View Projection Matrix */
	LJMatrix4 GetWorldViewProjectionMatrix();
	/* bound GPU program */
	void BoundGpuProgram(LJGLSLProgram *program);
	/* Setup Render State */
	void ApplyRenderState(const LJRenderState& renderState);
	/* Setup material */
	HRESULT ApplyMaterial(int nMaterial);
	/* render a geometry */
	HRESULT RenderGeometry(LJGeometry& geo);

	static GLenum DEVICE_RENDER_STATE_VALUE[35];
	static GLenum GLPNAME[7];
	static GLint GLPARAM[12];
	static GLenum GLTYPE[7];
	LJVector3 m_CamPos;
private:
	HWND m_hWndMain;		// Main window
	HWND m_hWnd[MAX_3DHWND];// render windows
	UINT m_nNumhWnd;		// number of render-windows
	UINT m_nActivehWnd;		// active window
	DWORD m_dwWidth; 		// screen width
	DWORD m_dwHeight;		// screen height
	bool m_bWindowed; 		// windowed mode
	char m_chAdapter[256]; 	// graphics adapter name
	FILE *m_pLog;  			// log-file
	bool m_bRunning;
	bool m_bIsSceneRunning;
	bool m_bStencil;
	LJCOLOR m_ClearColor;
	bool m_bViewUpdate;
	bool m_bWorldUpdate;

	// Internal texture manager manages OpenGL texture objects
	LJInterTextureManager *m_pInterTexManager;
	// Internal Gpu Program manager manages GLSL program objects
	LJProgramManager *m_pInterProgManager;
	// render manager
	LJRenderManager *m_pVCManager;
	// material manager, create and manage materials
	LJOGLMaterialManager *m_pMatManager;
	// image manager, load and manage images
	LJImageManager *m_pImgManager;

	// NEAR and FAR Clip Planes
	float m_fNear;
	float m_fFar;

	LJDIMENSIONMODE m_Mode; 					// the current mode
	LJSTAGE m_nStage;							// the current stage
	LJVIEWPORT m_Vp;							// the current view-port

	LJVIEWPORT m_Vps[MAX_VIEWPORTS];			// view-ports for 3D
	LJMatrix4 m_MatView3D;						// view-matrix for 3D
	LJMatrix4 m_MatPers3D[MAX_VIEWPORTS];		// perspective-matrixes for 3D
	LJMatrix4 m_MatOrth3D[MAX_VIEWPORTS];		// orthogonal-matrixes for 3D

	// world equals to screen setting
	LJVIEWPORT m_Vp2D;							// the screen ViewPort
	LJMatrix4 m_MatView2D;						// view-matrix for 2D
	LJMatrix4 m_MatProj2D;						// orthogonal-matrix for 2D

	// current settings
	LJMatrix4 m_MatWorld;			// World Matrix
	LJMatrix4 m_MatWorldView;		// World View Matrix
	LJMatrix4 m_MatViewProj;		// View Projection Matrix
	LJMatrix4 m_MatWorldViewProj;	// World View Projection Matrix
	LJMatrix3 m_MatNormal;			// Normal matrix

	LJGLSLProgram *m_pBoundGpuProgram; // the current gpu program

	// startup
	HRESULT Go(void);
	// log information
	void Log(char *, ...);
	// calculate view-projection matrix
	void updateViewProjMatrix();
	// calculate world-view-projection matrix
	void updateWorldViewProjMatrix();
	// startup initialize
	HRESULT OneTimeInit(void);
	// update shader parameters
	HRESULT UpdateShaderParams(const LJMaterial::LJMatParams *pParams);
	// calculate normal matrix
	void updateNormalMatrix();
	// error checker
	HRESULT getError(FILE *pLog);
};


#ifdef _LJ_WIN32
extern "C" {
	__declspec(dllexport) HRESULT CreateRenderDevice(LJRenderDevice **pInterface);
	__declspec(dllexport) HRESULT ReleaseRenderDevice(LJRenderDevice **pInterface);
}
#endif

#ifdef _LJ_LINUX
extern "C" {
	HRESULT CreateRenderDevice(LJRenderDevice **pInterface);
	HRESULT ReleaseRenderDevice(LJRenderDevice **pInterface);
}
#endif

#endif /* LJOPENGL_H_ */

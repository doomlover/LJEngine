/*
 * LJOpenGL.h
 *
 *  Created on: 2013.7.28
 *      Author: Liu
 */

#ifndef LJOPENGL_H_
#define LJOPENGL_H_

#include <GL/glew.h>
#include "LJRenderDevice.h"
#include "LJPass.h"
#include "LJMaterial.h"
#include "LJOGLFramebuffer.h"

class LJRenderManager;
class LJOGLTextureManager;
class LJOGLMaterialManager;
class LJInterSkinManager;
class LJInterTextureManager;
class LJGLSLProgram;
class LJProgramManager;
class LJImageManager;
class LJOGLTextureManager;

class LJOpenGL : public LJRenderDevice
{
public:
	static LJOpenGL* GetInstance();

	~LJOpenGL(void);

	HRESULT Init(HWND, const HWND*, int, int, int, bool, int winWidth, int winHeight);
	void Release(void);
	bool IsRunning(void){ return m_bRunning; }
	HRESULT BeginRendering(bool, bool, bool);
	HRESULT Clear(bool, bool, bool);
	void EndRendering(void);
	void SetClearColor(float, float, float);
	HRESULT UseWindow(UINT nHwnd);

	LJRenderManager* GetRenderManager(void);

	LJMaterialManager* GetMaterialManager(void)const;

	LJTextureManager* GetTextureManager();

	LJProgramManager* GetInterProgManager(void)const;

	// Set camera setting with Right, Up, Direction, Position
	void SetCamera(const LJVector3& v3Right, const LJVector3& v3Up, const LJVector3& v3Dir, LJVector3 v3Pos);
	// Set camera setting with Position, Look-at, Up
	void SetCamera(const LJVector3& v3Pos, const LJVector3& v3Lookat, const LJVector3 v3Up);
	// Directly set
	void SetCamera(const LJMatrix4& viewMatrix);
	// set projection, both perspective matrix and orthogonal matrix are calculated. Use SetMode to choose mode
	void SetPerspective(float fFov, float fAspect, float fNear, float fFar);
	// Set stage View-Port
	void SetViewport(LJVIEWPORT& viewport);
	// Set projection mode
	void SetMode(LJDIMENSIONMODE mode);
	/* Set Local-to-World Matrix */
	void SetWorldMatrix(LJMatrix4& matWorld);
	// Extracting Frustum planes
	HRESULT ExtractFrustumPlanes(LJVector4*);
	// Translate screen coordinates to world space
	void ScreenToWorld(const LJVector2& sPos, LJVector3& wPos);
	// Transform world coordinates to screen space
	void WorldToScreen(const LJVector3& wPos, LJVector2& sPos);
	/* Get World Matrix */
	LJMatrix4 GetWorldMatrix();
	/* Get View Matrix 3D */
	LJMatrix4 GetViewMatrix3D();
	/* Get View Matrix 2D */
	LJMatrix4 GetViewMatrix2D();
	/* Get Projection Matrix */
	LJMatrix4 GetProjectionMatrix(LJDIMENSIONMODE mode);
	/* Get View Projection Matrix */
	LJMatrix4 GetViewProjectionMatrix();
	/* Get World View Projection Matrix */
	LJMatrix4 GetWorldViewProjectionMatrix();
	/* bound GPU program */
	void BoundGpuProgram(LJGLSLProgram *program);
	/* Setup framebuffer */
	void SetFramebuffer(LJFramebuffer& fb, UINT renderPassIndex);
	/* Setup Render State */
	void ApplyRenderState(const LJRenderState& renderState);
	/* Setup a texture */
	HRESULT ApplyTexture(LJTexture& tex, int texUnit);
	/* Setup material */
	HRESULT ApplyMaterial(int nMaterial);
	/* Setup render texture for off-screen rendering */
	void ApplyRenderTexture(LJRenderTexture& tex, UINT attachPoint);
	/* Setup render texture for depth rendering */
	bool ApplyDepthTexture(LJRenderTexture& depth, UINT unit);
	/* render a geometry */
	HRESULT RenderGeometry(LJGeometry& geo);
	/* Draw a mesh */
	HRESULT RenderMesh(LJMesh& mesh);

	static GLenum DEVICE_RENDER_STATE_VALUE[35];
	static GLenum GLPNAME[7];
	static GLint GLPARAM[12];
	static GLenum GLTYPE[7];
	static GLenum GLFORMAT[5];
	LJVector3 m_CamPos;
private:
	HWND m_hWndMain;		// Main window
	HWND m_hWnd[MAX_3DHWND];// render windows
	UINT m_nNumhWnd;		// number of render-windows
	UINT m_nActivehWnd;		// active window
	bool m_bWindowed; 		// windowed mode
	char m_chAdapter[256]; 	// graphics adapter name
	FILE *m_pLog;  			// log-file
	bool m_bRunning;
	//bool m_bIsSceneRunning;
	bool m_bStencil;
	LJCOLOR m_ClearColor;
	bool m_bViewUpdate;
	bool m_bWorldUpdate;

	// LJTexture Manager
	LJOGLTextureManager *m_pTexManager;
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

	DWORD m_dwWidth; 		// screen width
	DWORD m_dwHeight;		// screen height
	// NEAR and FAR Clip Planes
	float m_fNear;
	float m_fFar;

	LJOGLFramebuffer *m_pOGLFB;		// current pass framebuffer
	LJOGLFramebuffer m_OGLFBs[LJ_MAX_RENDER_PASSES];

	LJDIMENSIONMODE m_Mode; 					// the current mode
	//LJSTAGE m_nStage;							// the current stage
	LJVIEWPORT m_Vp;							// the current view-port

	LJMatrix4 m_MatView3D;						// view-matrix for 3D
	LJMatrix4 m_MatPers3D;		// perspective-matrixes for 3D
	LJMatrix4 m_MatOrth3D;		// orthogonal-matrixes for 3D

	// world equals to screen setting
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
	// update matrixes
	void updateMatrixes();
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
	// generate a OpenGL texture object for a LJTexture
	UINT GenOGLTexture(LJTexture& tex);

	LJOpenGL(void);

	LJOpenGL(const LJOpenGL& device);
};

extern "C" {
	_LJExport HRESULT CreateRenderDevice(LJRenderDevice **pInterface);
	_LJExport HRESULT ReleaseRenderDevice(LJRenderDevice **pInterface);
}

#endif /* LJOPENGL_H_ */

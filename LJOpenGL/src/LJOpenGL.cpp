/*
 * LJOpenGL.cpp
 *
 *  Created on: 2013.07.29
 *      Author: Liu
 */

#include <GL/glew.h>
#include "LJOpenGL.h"
#include "LJUtil.h"
#include "LJOGLRenderManager.h"
#include "LJOGLMaterialManager.h"
#include "LJInterTextureManager.h"
#include "LJMesh.h"
#include "LJPass.h"
#include "LJRenderState.h"
#include "LJProgramManager.h"
#include "LJImageManager.h"
#include "LJGeometry.h"
#include "LJOGLTexture.h"
#include "LJOGLTextureManager.h"
#include <iostream>
#include <cstring>
#include <string>

/*
 * Globe Device Pointer
 */
LJOpenGL *g_LJOpenGL = NULL;
/*
 * OpenGL Error Checker
 */
HRESULT LJOpenGL::getError(FILE *pLog) {
	HRESULT ret = LJ_OK;
	ret = glGetError();
	if (ret == GL_NO_ERROR)
		return LJ_OK;
	else {
		fprintf(pLog, "glGetError : %d", ret);
		return LJ_FAIL;
	}
}
/*
 * OpenGL Texture Parameter Name
 */
GLenum LJOpenGL::GLPNAME[7] =
{
	GL_TEXTURE_COMPARE_FUNC,
	GL_TEXTURE_COMPARE_MODE,
	GL_TEXTURE_MIN_FILTER,
	GL_TEXTURE_MAG_FILTER,
	GL_TEXTURE_WRAP_S,
	GL_TEXTURE_WRAP_T,
	GL_TEXTURE_WRAP_R
};
/*
 * OpenGL Texture Parameter
 */
GLint LJOpenGL::GLPARAM[12] =
{
	GL_LINEAR,
	GL_NEAREST,
	GL_NEAREST_MIPMAP_NEAREST,
	GL_LINEAR_MIPMAP_NEAREST,
	GL_NEAREST_MIPMAP_LINEAR,
	GL_LINEAR_MIPMAP_LINEAR,
	GL_COMPARE_REF_TO_TEXTURE,
	GL_CLAMP_TO_EDGE,
	GL_CLAMP_TO_BORDER,
	GL_MIRRORED_REPEAT,
	GL_REPEAT,
	GL_MIRROR_CLAMP_TO_EDGE
};
/*
 * OpenGL Type Token
 */
GLenum LJOpenGL::GLTYPE[7] =
{
	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT,
	GL_FLOAT,
};
/*
 * OpenGL Format Token
 */
GLenum LJOpenGL::GLFORMAT[5] =
{
	GL_RGB,
	GL_BGR,
	GL_RGBA,
	GL_BGRA,
	GL_DEPTH_COMPONENT
};
/*
 * OpenGL Render State Token (FUNC, MODE)
 */
GLenum LJOpenGL::DEVICE_RENDER_STATE_VALUE[35] =
{
		GL_FRONT,
		GL_BACK,
		GL_FRONT_AND_BACK,

		GL_CW,
		GL_CCW,

		GL_FUNC_ADD,
		GL_FUNC_SUBTRACT,
		GL_FUNC_REVERSE_SUBTRACT,
		GL_MIN,
		GL_MAX,

		GL_ZERO,
		GL_ONE,
		GL_SRC_COLOR,
		GL_ONE_MINUS_SRC_COLOR,
		GL_DST_COLOR,
		GL_ONE_MINUS_DST_COLOR,
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA,
		GL_DST_ALPHA,
		GL_ONE_MINUS_DST_ALPHA,
		GL_CONSTANT_COLOR,
		GL_ONE_MINUS_CONSTANT_COLOR,
		GL_CONSTANT_ALPHA,
		GL_ONE_MINUS_CONSTANT_ALPHA,

		GL_NEVER,
		GL_LESS,
		GL_EQUAL,
		GL_LEQUAL,
		GL_GREATER,
		GL_NOTEQUAL,
		GL_GEQUAL,
		GL_ALWAYS,

		GL_POINT,
		GL_LINE,
		GL_FILL
};

LJOpenGL::LJOpenGL(void) 
{
	LJLog("LJOpenGL", "constructor");
	m_pLog = NULL;
	m_bRunning = false;
	m_bIsSceneRunning = false;
	m_nActivehWnd = 0;
	m_bStencil = false;
	g_LJOpenGL = this;
	m_bViewUpdate = false;
	m_bWorldUpdate = false;
	m_pInterTexManager = NULL;
	m_pInterProgManager = NULL;
	m_pMatManager = NULL;
	m_pVCManager = NULL;
	m_pImgManager = NULL;
	m_pTexManager = NULL;
	m_Mode = LJ_DM_ORTHOGONAL;

	m_dwWidth = 0;
	m_dwHeight = 0;

	m_bWindowed = true;
	m_nNumhWnd = 0;
	m_hWndMain = NULL;

	m_fNear = 0.01f;
	m_fFar = 1000.f;

	m_pOGLFB = NULL;

	m_pBoundGpuProgram = NULL;
}

LJOpenGL::~LJOpenGL() {
	LJLog("LJOpenGL", "destruction");
	Release();
}

void LJOpenGL::Release() {
	LJLog("LJOpenGL", "Release");
	if (m_pLog) {
		fclose(m_pLog);
	}
	if(m_pTexManager)
	{
		delete m_pTexManager;
	}
	if(m_pVCManager) {
		delete m_pVCManager;
		m_pVCManager = NULL;
	}
	if(m_pImgManager)
	{
		delete m_pImgManager;
		m_pImgManager = NULL;
	}
	if(m_pInterTexManager)
	{
		delete m_pInterTexManager;
		m_pInterTexManager = NULL;
	}
	if(m_pInterProgManager)
	{
		delete m_pInterProgManager;
		m_pInterProgManager = NULL;
	}
	if(m_pMatManager)
	{
		delete m_pMatManager;
		m_pMatManager = NULL;
	}
	// delete openGL framebuffer and renderbuffer
	for(UINT i = 0; i < LJ_MAX_RENDER_PASSES; ++i)
	{
		UINT id = m_OGLFBs[i].m_OGLFBHandle;
		if(id != LJ_MAX_ID)
		{
			glDeleteFramebuffers(1, &id);
		}
		id = m_OGLFBs[i].m_OGLRBHandle;
		if(id != LJ_MAX_ID)
		{
			glDeleteRenderbuffers(1, &id);
		}
	}
}

HRESULT LJOpenGL::Init(HWND hWnd, const HWND* hWnd3D, int nNumhWnd,
		int nMinDepth, int nMinStencil, bool bSaveLog, int winWidth, int winHeight) {
	LJLog("LJOpenGL", "Init");
#ifdef _LJ_WIN32
	fopen_s(&m_pLog, "log_renderdevice.txt", "w");
#elif defined _LJ_LINUX
	m_pLog = fopen("log_renderdevice.txt", "w");
#endif
	if (m_pLog == NULL)
		return LJ_FAIL;

	if (m_nNumhWnd > 0 && hWnd3D != NULL) {
		if (m_nNumhWnd > MAX_3DHWND) {
			m_nNumhWnd = MAX_3DHWND;
		}
		memcpy(&m_hWnd[0], hWnd3D, sizeof(HWND) * m_nNumhWnd);
	} else {
		m_hWnd[0] = hWnd;
		m_nNumhWnd = 0;
	}
	m_hWndMain = hWnd;


	if (nMinStencil > 0)
		m_bStencil = true;
	/*
	 * Initialize GLEW
	 */
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(m_pLog, "Error: %s\n", glewGetErrorString(err));
		return LJ_FAIL;
	} else {
		LJLog("LJOpenGL", "GLEW INIT");
	}
	m_dwWidth = winWidth;
	m_dwHeight = winHeight;
	return Go();
}

HRESULT LJOpenGL::Go(void) {
	HRESULT ret = LJ_OK;
/*  // not ready
	// full-screen mode
	if (!m_bWindowed) {

	}
	// windowed mode
	else {

	}
*/
	m_bRunning = true;
	m_bIsSceneRunning = false;

	OneTimeInit();

	return ret;
}

HRESULT LJOpenGL::BeginRendering(bool bColor, bool bDepth, bool bStencil)
{
	HRESULT ret = LJ_FAIL;
	// Use default OpenGL framebuffer
	if(m_pOGLFB->m_Fb != NULL)
	{
		LJFramebuffer *fb = m_pOGLFB->m_Fb;
		LJRenderTexture *depthBuffer = fb->GetDepthTexture();
		// off screen rendering must specify depth buffer
		if(depthBuffer == NULL) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else {
			LJTexture *depthTex = depthBuffer->GetTexture(NULL);
			UINT nRenderTexes = fb->GetNumberRenderTextures();
			// If there is no render texture or depth texture
			if(nRenderTexes == 0 && depthTex == NULL)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
			else { // do rendering to texture
				// Generate OpenGL framebuffer object
				if(m_pOGLFB->m_OGLFBHandle == LJ_MAX_ID)
				{
					glGenFramebuffers(1, &m_pOGLFB->m_OGLFBHandle);
				}
				glBindFramebuffer(GL_FRAMEBUFFER, m_pOGLFB->m_OGLFBHandle);
				if(m_pOGLFB->m_Fb->IsUpdated())
				{
					//printf("Framebuffer update\n");
					vector<GLenum> drawBuffers;
					for(UINT i = 0; i < nRenderTexes; ++i)
					{
						ApplyRenderTexture(*fb->GetRenderTexture(i), i);
						ret = glGetError();
						drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
					}
					if(ApplyDepthTexture(*depthBuffer, nRenderTexes))
					{
						drawBuffers.push_back(GL_DEPTH_ATTACHMENT);
					}
					glDrawBuffers(drawBuffers.size(), drawBuffers.data());
					if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
						return LJ_FAIL;
					m_pOGLFB->m_Fb->SetUpdated(false);
				}
			}
		}
	}//~if(m_pOGLFB->m_Fb != NULL)
	else {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	glViewport(m_Vp.x, m_Vp.y, m_Vp.width, m_Vp.height);
	DWORD dw = 0;
	if (bColor || bDepth || bStencil) {
		if (bColor)
			dw |= GL_COLOR_BUFFER_BIT;
		if (bDepth)
			dw |= GL_DEPTH_BUFFER_BIT;
		if (bStencil && m_bStencil)
			dw |= GL_STENCIL_BUFFER_BIT;

		glClearColor(m_ClearColor.fR, m_ClearColor.fG, m_ClearColor.fB,
				m_ClearColor.fA);
		glClear(dw);
	}

	m_bIsSceneRunning = true;

	ret = glGetError();
	if (ret == GL_NO_ERROR)
		return LJ_OK;
	else {
		fprintf(m_pLog, "glGetError : %u\n", (GLuint) ret);
		return LJ_FAIL;
	}
}

UINT LJOpenGL::GenOGLTexture(LJTexture& tex)
{
	int texID = tex.GetId();
	if(texID == -1)
	{
		UINT newId;
		glGenTextures(1, &newId);
		texID = newId;
		tex.SetId(texID);
		m_pInterTexManager->SetTexObj(texID);
	}
	else
	{
		if(m_pInterTexManager->GetTexObj(texID) == -1)
		{
			UINT newId;
			glGenTextures(1, &newId);
			texID = newId;
			tex.SetId(texID);
			m_pInterTexManager->SetTexObj(texID);
		}
	}
	return texID;
}

void LJOpenGL::ApplyRenderTexture(LJRenderTexture& renderTex, UINT attachPoint)
{
	// Get texture size
	UINT w, h;
	renderTex.GetSize(&w, &h);
	// Get format
	TextureFormat fmt = renderTex.GetFormat();
	// Get texture
	LJTexture *tex = renderTex.GetTexture(NULL);

	if(!tex)
		throw "Off screen rendering must has at least one texture";
	// Generate OGL texture
	UINT texID = GenOGLTexture(*tex);
	glActiveTexture(GL_TEXTURE0+attachPoint);
	GLenum target = GL_TEXTURE_2D;

	switch(tex->GetTarget())
	{
	case LJ_TEXTURE_2D:
	{
		target = GL_TEXTURE_2D;
		glBindTexture(GL_TEXTURE_2D, texID);
		if(tex->IsNeedUpdate())
		{
			//printf("ApplyRenderTexture : glTexImage2D\n");
			glTexImage2D(target, 0,
					GLFORMAT[fmt],
					w, h, 0,
					GLFORMAT[fmt],
					GL_UNSIGNED_BYTE,
					0);
			tex->SetNeedUpdate(false);
		}
	}
		break;
	case LJ_TEXTURE_3D:
	{
		target = GL_TEXTURE_3D;
		throw "not support 3D texture";
	}
		break;
	default:
		// should not goes here
		break;
	}//~switch
	// set texture parameters
	if(tex->IsUpdateParam())
	{
		LJTexture::LJTEXPARAMCONFS::const_iterator it = tex->GetParams().begin();
		LJTexture::LJTEXPARAMCONFS::const_iterator it_end = tex->GetParams().end();
		while(it != it_end)
		{
			glTexParameteri(target, GLPNAME[it->first], GLPARAM[it->second]);
			++it;
		}
		tex->SetUpdateParam(false);
	}
	glFramebufferTexture(GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0+attachPoint,
			texID, 0);
}

bool LJOpenGL::ApplyDepthTexture(LJRenderTexture& depth, UINT unit)
{
	if(m_pOGLFB->m_OGLRBHandle == LJ_MAX_ID)
	{
		glGenRenderbuffers(1, &m_pOGLFB->m_OGLRBHandle);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, m_pOGLFB->m_OGLRBHandle);

	UINT w, h;
	depth.GetSize(&w, &h);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
			w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER, m_pOGLFB->m_OGLRBHandle);
	// Optional. If there is a depth texture can be rendered
	LJTexture *tex = depth.GetTexture(NULL);
	if(tex)
	{
		// Generate OGL texture id
		UINT texID = GenOGLTexture(*tex);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24,
				w, h, 0,
				GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				texID, 0);
		return true;
	}
	return false;
}

/* Setup framebuffer */
void LJOpenGL::SetFramebuffer(LJFramebuffer& fb, UINT renderPassIndex)
{
	m_OGLFBs[renderPassIndex].m_Fb = &fb;
	m_pOGLFB = &m_OGLFBs[renderPassIndex];
}

HRESULT LJOpenGL::Clear(bool bColor, bool bDepth, bool bStencil) {
	LJLog("LJOpenGL", "Clear");
	HRESULT ret = LJ_FAIL;

	DWORD dw = 0;
	if (bColor || bDepth || bStencil) {
		if (bColor)
			dw |= GL_COLOR_BUFFER_BIT;
		if (bDepth)
			dw |= GL_DEPTH_BUFFER_BIT;
		if (bStencil && m_bStencil)
			dw |= GL_STENCIL_BUFFER_BIT;

		glClearColor(m_ClearColor.fR, m_ClearColor.fG, m_ClearColor.fB,
				m_ClearColor.fA);
		glClear(dw);
	}

	if (m_bIsSceneRunning) {
		// m_pDevice->BeginScene();
	}

	ret = getError(m_pLog);
	return ret;
}

void LJOpenGL::EndRendering(void) {
	//m_pDevice->EndScene();
	m_bIsSceneRunning = false;
}

void LJOpenGL::SetClearColor(float fRed, float fGreen, float fBlue) {
	LJLog("LJOpenGL", "SetClearColor");
	m_ClearColor.fR = fRed;
	m_ClearColor.fG = fGreen;
	m_ClearColor.fB = fBlue;
	m_ClearColor.fA = 1.0f;
}

HRESULT LJOpenGL::UseWindow(UINT nHwnd) {
	LJLog("LJOpenGL", "UseWindow not implemented");
	HRESULT ret = LJ_FAIL;
	return ret;
}

LJRenderManager* LJOpenGL::GetRenderManager(void) {
	return m_pVCManager;
}

/*
 * Set View Matrix with Right, Up, Direction, Position
 */
void LJOpenGL::SetCamera(const LJVector3& v3Right, const LJVector3& v3Up, const LJVector3& v3Dir, LJVector3 v3Pos)
{
	m_MatView3D[0][0] = v3Right.x;
	m_MatView3D[1][0] = v3Right.y;
	m_MatView3D[2][0] = v3Right.z;

	m_MatView3D[0][1] = v3Up.x;
	m_MatView3D[1][1] = v3Up.y;
	m_MatView3D[2][1] = v3Up.z;

	m_MatView3D[0][2] = v3Dir.x;
	m_MatView3D[1][2] = v3Dir.y;
	m_MatView3D[2][2] = v3Dir.z;

	m_MatView3D[3][0] = -dot(v3Right, v3Pos);
	m_MatView3D[3][1] = -dot(v3Up, v3Pos);
	m_MatView3D[3][2] = -dot(v3Dir, v3Pos);

	m_bViewUpdate = true;
}
/*
 * Set View Matrix with camera position, look-at and up-direction
 */
void LJOpenGL::SetCamera(const LJVector3& v3Pos, const LJVector3& v3Lookat, const LJVector3 v3Up)
{
	LJVector3 dir = ljm::normalize(v3Pos - v3Lookat);
	LJVector3 up = ljm::normalize(v3Up);
	LJVector3 right = ljm::normalize(ljm::cross(up, dir));
	up = ljm::cross(dir, right);
	SetCamera(right, up, dir, v3Pos);
}
/*
 * Directly set View Matrix
 */
void LJOpenGL::SetCamera(LJMatrix4& viewMatrix)
{
	m_MatView3D = viewMatrix;
	m_bViewUpdate = true;
}

// set projection, both perspective matrix and orthogonal matrix are calculated. Use SetMode to choose mode
void LJOpenGL::SetPerspective(float fFov, float fAspect, float fNear, float fFar)
{
	float r, l, t, b;
	r = static_cast<float>(m_fNear*static_cast<float>(tan(DegreeToRadian(fFov/2.0))));
	l = -r;
	t = r/fAspect;
	b = -t;
	/*
	 * Calculate Projection Matrix
	 */
	float raddl = r+l;
	float rsubl = r-l;
	float tsubb = t - b;
	float taddb = t + b;
	float faddn = m_fFar + m_fNear;
	float fsubn = m_fFar - m_fNear;
	/*
	 * Perspective Matrix
	 */
	m_MatPers3D[0] = LJVector4(2*m_fNear/rsubl, 0, 0, 0);
	m_MatPers3D[1] = LJVector4(0, 2*m_fNear/tsubb, 0, 0);
	m_MatPers3D[2] = LJVector4(raddl/rsubl, taddb/tsubb, -faddn/fsubn, -1.f);
	m_MatPers3D[3] = LJVector4(0, 0, -2*m_fNear*m_fFar/fsubn, 0);

	/*
	 * Orthogonal Matrix
	 */
	m_MatOrth3D[0] = LJVector4(2.0f/rsubl, 0, 0, 0);
	m_MatOrth3D[1] = LJVector4(0, 2.0f/tsubb, 0, 0);
	m_MatOrth3D[2] = LJVector4(0, 0, -2.0f/fsubn, 0);
	m_MatOrth3D[3] = LJVector4(-raddl/rsubl, -taddb/tsubb, -faddn/fsubn, 1.f);
}
// Set mode and stage
void LJOpenGL::SetMode(LJDIMENSIONMODE mode)
{
	m_Mode = mode;
}
// Set 3D View-port for @stage
void LJOpenGL::SetViewport(LJVIEWPORT& viewport)
{
	m_Vp = viewport;
}
/* Set Local-to-World Matrix */
void LJOpenGL::SetWorldMatrix(LJMatrix4& matWorld)
{
		m_MatWorld = matWorld;
		m_bWorldUpdate = true;
}
HRESULT LJOpenGL::ExtractFrustumPlanes(LJPlane* pPlanes) {
	HRESULT hr = LJ_FAIL;
	if(pPlanes != NULL) {
		LJLog("LJOPENGL::ExtractFrustumPlanes", "WARNING : NOT IMPLEMENTED");
		// WARNING : NOT IMPL
	}
	return hr;
}

// not implemented
void LJOpenGL::ScreenToWorld(const LJVector2& v2Screen, LJVector3& v3World) {
	//LJLog("LJOpenGL", "ScreenToWorld : not implemented");
	//DWORD w, h;
	//LJMatrix4 inverseViewMat;
	//// SCREEN TO NDC
	//switch(m_Mode)
	//{
	//case LJ_WEQS:
	//	w = m_dwWidth;
	//	h = m_dwHeight;
	//	//inverseViewMat = ljm::inverse(m_MatView2D);
	//	break;
	//default:
	//	w = m_Vps[m_nStage].width;
	//	h = m_Vps[m_nStage].height;
	//	//inverseViewMat = ljm::inverse(m_MatView3D);
	//}
	//float NDCx = v2Screen.x/w*2.f-1.f;
	//float NDCy = v2Screen.y/h*2.f-1.f;
	//// Looking for the corresponding point on the Near plane, so Pz = m_fNear
	//// NDC TO CC (clip coordinate)
	//float CCx = NDCx*(-m_fNear);
	//float CCy = NDCy*(-m_fNear);
	//// CC TO EYE (view or camera space coordinate)
	//float ECx, ECy;
	//switch(m_Mode) {
	//case LJ_DM_PERSPECTIVE:
	//	ECx = (CCx + m_MatPers3D[m_nStage][2][0]*(-m_fNear))/m_MatPers3D[m_nStage][0][0];
	//	ECy = (CCy + m_MatPers3D[m_nStage][2][1]*(-m_fNear))/m_MatPers3D[m_nStage][1][1];
	//	break;
	//case LJ_DM_ORTHOGONAL:
	//	ECx = (CCx + m_MatOrth3D[m_nStage][2][0]*(-m_fNear))/m_MatPers3D[m_nStage][0][0];
	//	ECy = (CCy + m_MatOrth3D[m_nStage][2][1]*(-m_fNear))/m_MatPers3D[m_nStage][1][1];
	//	break;
	//case LJ_WEQS:
	//	ECx = (CCx - m_MatProj2D[3][0])/m_MatProj2D[0][0];
	//	ECy = (CCy - m_MatProj2D[3][1])/m_MatProj2D[1][1];
	//	break;
	//default:
	//	break;
	//}
	// EC TO W
}

void LJOpenGL::WorldToScreen(const LJVector3& v3World, LJVector2& v2Screen) {

	// to the clip space
	LJVector4 v4Clip = m_MatViewProj * LJVector4(v3World, 1.0f);
	// to the normalized device space
	v4Clip = v4Clip/v4Clip.w;
	// get viewport's dimension
	DWORD width = m_Vp.width;
	DWORD height = m_Vp.height;
	// normalized device space to screen space
	v2Screen.x = (v4Clip.x + 1.0f)/2.0f*width;
	v2Screen.y = (v4Clip.y + 1.0f)/2.0f*height;
}

LJTextureManager* LJOpenGL::GetTextureManager()
{
	return m_pTexManager;
}

LJMaterialManager* LJOpenGL::GetMaterialManager(void)
const
{
	return m_pMatManager;
}

LJProgramManager* LJOpenGL::GetInterProgManager(void)
const 
{
	return m_pInterProgManager;
}

GLenum get_buffer_target(LJVertexBuffer::TARGET target)
{
	switch(target)
	{
	case LJVertexBuffer::LJ_ARRAY_BUFFER:
		return GL_ARRAY_BUFFER;
	case LJVertexBuffer::LJ_ELEMENT_ARRAY_BUFFER:
		return GL_ELEMENT_ARRAY_BUFFER;
	default:
		// won't be here
		return GL_ARRAY_BUFFER;
	}
}

GLenum get_buffer_usage(LJVertexBuffer::USAGE usage)
{
	switch(usage)
	{
	case LJVertexBuffer::LJ_STATIC_DRAW:
		return GL_STATIC_DRAW;
	default:
		return GL_STATIC_DRAW;
	}
}

GLenum get_mode(LJMesh::MODE mode)
{
	switch(mode)
	{
	case LJMesh::LJ_TRIANGLES:
		return GL_TRIANGLES;
	default:
		return GL_TRIANGLES;
		/* TODO : throw exception */
	}
}

HRESULT LJOpenGL::RenderMesh(LJMesh& mesh)
{
	HRESULT hr = LJ_OK;
	
	const LJMesh::VERTEXBUFFERS *pBufs = mesh.GetBuffers();
	LJMesh::VERTEXBUFFERS::const_iterator it = pBufs->begin();
	while(it != pBufs->end())
	{
		int oglBufObj = (*it)->GetID();
		if(oglBufObj == -1)
		{
			// generating a new OpenGL buffer object
			GLuint id;
			glGenBuffers(1, &id);
			(*it)->SetID(id);
		}
		GLuint target = get_buffer_target((*it)->GetTarget());
		// bind buffer
		glBindBuffer(target, (*it)->GetID());
		// if vertex buffer is updated, upload ogl buffer data
		if((*it)->IsNeedUpdate())
		{
			glBufferData(target, (*it)->GetSize()*(*it)->GetTypeSize(),
				(GLvoid*)(*it)->GetData(), get_buffer_usage((*it)->GetUsage()));
		}
		// get attribute location
		int location = m_pBoundGpuProgram->getAttribLocation((*it)->GetAttribName().c_str());
		// enable shader attribute
		if(location != -1)
		{
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, (*it)->GetComponent(),
				GLTYPE[(*it)->GetType()], (*it)->GetNormalized(),
				(*it)->GetStride(), (GLvoid*)0);
		}
		++it;
	}
	LJVertexBuffer *pIndexBuffer = mesh.GetIndexBuffer();
	if(pIndexBuffer)
	{
		int id = pIndexBuffer->GetID();
		if(id == -1)
		{
			GLuint _id;
			glGenBuffers(1, &_id);
			pIndexBuffer->SetID(_id);
			id = _id;
		}
		GLuint target = get_buffer_target(pIndexBuffer->GetTarget());
		glBindBuffer(target, id);
		if(pIndexBuffer->IsNeedUpdate())
		{
			glBufferData(target,
					pIndexBuffer->GetSize()*pIndexBuffer->GetTypeSize(),
					pIndexBuffer->GetData(),
					get_buffer_usage(pIndexBuffer->GetUsage())
					);
		}
		glDrawElements(get_mode(mesh.GetMode()), pIndexBuffer->GetSize(),
				GLTYPE[pIndexBuffer->GetType()],
				(GLvoid*)0);
	}
	else
	{
		int size = (*mesh.GetBuffers())[0]->GetSize();
		glDrawArrays(get_mode(mesh.GetMode()), 0, size);
	}
	return hr;
}

HRESULT LJOpenGL::ApplyTexture(LJTexture& tex, int texUnit)
{
	HRESULT hr = LJ_OK;

	UINT id = GenOGLTexture(tex);
	// active opengl tex unit
	glActiveTexture(GL_TEXTURE0+texUnit);

	GLenum target = GL_TEXTURE_2D;

	switch (tex.GetTarget())
	{
	case LJ_TEXTURE_2D:
	{
		target = GL_TEXTURE_2D;

		glBindTexture(target, id);

		if (tex.IsNeedUpdate())
		{
			LJImage& img = m_pImgManager->CreateImage(tex.GetImage(0));
			LJOGLTexture OGLTex(&tex, &img);
			OGLTex.Update();
			//printf("ApplyTexture : glTexImage2D");
			glTexImage2D(target, 0, img.GetInterFormat(), img.GetWidth(),
					img.GetHeight(), 0, img.GetFormat(), GL_UNSIGNED_BYTE,
					(GLvoid*) img.GetBits());
			tex.SetNeedUpdate(false);
		}
	}
		break;
	case LJ_TEXTURE_3D:
		break;
	case LJ_TEXTURE_CUBE_MAP:
	{
		target = GL_TEXTURE_CUBE_MAP;

		glBindTexture(target, id);

		if (tex.IsNeedUpdate())
		{
			GLuint targets[] =
			{
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
			for (int i = 0; i < 6; ++i)
			{
				LJImage& img = m_pImgManager->CreateImage(tex.GetImage(i));
				LJOGLTexture OGLTex(&tex, &img);
				OGLTex.Update();

				glTexImage2D(targets[i], 0, img.GetInterFormat(),
						img.GetWidth(), img.GetHeight(), 0, img.GetFormat(),
						GL_UNSIGNED_BYTE, (GLvoid*) img.GetBits());
			}
			tex.SetNeedUpdate(false);
		}
	}
		break;
	default:
		LJLog("LJOpenGL", "ERROR, ApplyTexture, texture target not supported");
		return LJ_FAIL;
	}
	// set texture parameters
	if(tex.IsUpdateParam())
	{
		LJTexture::LJTEXPARAMCONFS::const_iterator it = tex.GetParams().begin();
		LJTexture::LJTEXPARAMCONFS::const_iterator it_end = tex.GetParams().end();
		while(it != it_end)
		{
			glTexParameteri(target, GLPNAME[it->first], GLPARAM[it->second]);
			++it;
		}
		tex.SetUpdateParam(false);
	}

	return hr;
}

LJMatrix4 LJOpenGL::GetWorldMatrix()
{
	if(m_bWorldUpdate)
	{
		// update MVP & MV & NM
		updateWorldViewProjMatrix();
		m_bWorldUpdate = false;
	}
	return m_MatWorld;
}

LJMatrix4 LJOpenGL::GetViewMatrix3D()
{
	if(m_bViewUpdate)
	{
		// update VP
		updateViewProjMatrix();
		// update MVP & MV & NM
		updateWorldViewProjMatrix();
		m_bViewUpdate = false;
		m_bWorldUpdate = false;
	}
	return m_MatView3D;
}

LJMatrix4 LJOpenGL::GetViewMatrix2D()
{
	return m_MatView2D;
}

LJMatrix4 LJOpenGL::GetProjectionMatrix(LJDIMENSIONMODE mode)
{
	switch(mode)
	{
	case LJ_WEQS:
		return m_MatProj2D;
	case LJ_DM_ORTHOGONAL:
		return m_MatOrth3D;
	default:
		return m_MatPers3D;
	}
}

LJMatrix4 LJOpenGL::GetViewProjectionMatrix()
{
	return m_MatViewProj;
}

LJMatrix4 LJOpenGL::GetWorldViewProjectionMatrix()
{
	return m_MatWorldViewProj;
}


void LJOpenGL::BoundGpuProgram(LJGLSLProgram *program)
{
	m_pBoundGpuProgram = program;
}

void LJOpenGL::ApplyRenderState(const LJRenderState& renderState)
{
	if(renderState.IsBlendEnabled())
	{
		glEnable(GL_BLEND);
	}
	else {
		glDisable(GL_BLEND);
	}
	if(renderState.IsCullFaceEnabled())
	{
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
	if(renderState.IsDepthEnabled())
	{
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}
	if(renderState.IsDitherEnabled())
	{
		glEnable(GL_DITHER);
	}
	else {
		glDisable(GL_DITHER);
	}
	if(renderState.IsScissorEnabled())
	{
		glEnable(GL_SCISSOR_TEST);
	}
	else {
		glDisable(GL_SCISSOR_TEST);
	}
	if(renderState.IsStencilEnabled())
	{
		glEnable(GL_STENCIL_TEST);
	}
	else {
		glDisable(GL_STENCIL_TEST);
	}

	glCullFace(DEVICE_RENDER_STATE_VALUE[renderState.GetCullFaceMode()]);
	glFrontFace(DEVICE_RENDER_STATE_VALUE[renderState.GetFrontFaceMode()]);
	glDepthFunc(DEVICE_RENDER_STATE_VALUE[renderState.GetDepthFunc()]);
	glBlendFunc(DEVICE_RENDER_STATE_VALUE[renderState.GetBlendFuncSrc()],
			DEVICE_RENDER_STATE_VALUE[renderState.GetBlendFuncDes()]);
	glPolygonMode(GL_FRONT_AND_BACK, DEVICE_RENDER_STATE_VALUE[renderState.GetPolygonMode()]);
	LJRenderState::COLORMASK colorMask = renderState.GetColorMask();
	glColorMask(colorMask.r, colorMask.g, colorMask.b, colorMask.a);
	LJRenderState::DEPTHRANGE depthRange = renderState.GetDepthRange();
	glDepthRange(depthRange.x, depthRange.y);
	LJRenderState::BLENDCOLOR blendColor = renderState.GetBlendColor();
	glBlendColor(blendColor.fR,blendColor.fG, blendColor.fB, blendColor.fA);
	glDepthMask((GLboolean)renderState.GetDepthMask());
	glLineWidth((GLfloat)renderState.GetLineWidth());
	glPointSize((GLfloat)renderState.GetPointSize());
}

HRESULT LJOpenGL::ApplyMaterial(int nMaterial)
{
	LJGLSLProgram *m_pGpuProgram = NULL;

	// get material
	LJMaterial *material = m_pMatManager->GetMaterial(nMaterial);
	if(!material) return LJ_FAIL;

	// Setup texture content
	int nTextures = material->GetNumOfTextures();
	for(int i = 0; i < nTextures; ++i)
	{
		// i as the OpenGL texture unit
		LJTexture *tex = m_pTexManager->GetTexture(material->GetTexture(i));
		ApplyTexture(*tex, i);
	}
	// get technique
	LJTechnique *tech = material->GetCurrentTech();

	// now we have a program with the technique name
	const char* curPassName = tech->GetCurrentPass();
	LJPass *pass = tech->GetPass(curPassName);

	// the technique has no pass, can't continue to render
	if(!pass) return LJ_FAIL;

	ApplyRenderState(pass->GetRenderState());

	// try to find a program with the same material
	m_pGpuProgram = static_cast<LJGLSLProgram*>(m_pInterProgManager->GetProgram(nMaterial));
	// not found
	if(!m_pGpuProgram)
	{
		// create new one
		m_pGpuProgram = new LJGLSLProgram();
		// add to program manager with the name
		m_pInterProgManager->AddProgram(nMaterial, m_pGpuProgram);
	}

	// if need to switch pass
	if(m_pGpuProgram->GetPassName() != string(curPassName))
	{
		// remember the new current pass in program
		m_pGpuProgram->SetPassName(curPassName);
		// Detach all the old shaders. This will cause program need to relink
		m_pGpuProgram->DetachAll();
	}// else, program use same pass, continue.

	if(m_pGpuProgram->IsNeedLink())
	{
		// if program does not cache the shader
		LJGLSLShader *vs = NULL, *fs = NULL;
		m_pGpuProgram->GetShaders(curPassName, &vs, &fs);
		if(vs == NULL || fs == NULL)
		{
			// create shader with shader code of the pass
			vs = new LJGLSLShader();
			vs->SetCode(pass->GetVertCode(),
							LJGLSLShader::LJ_VERTEX_SHADER);
			fs = new LJGLSLShader();
			fs->SetCode(pass->GetFragCode(),
						LJGLSLShader::LJ_FRAGMENT_SHADER);
			// cache the new shaders to program
			m_pGpuProgram->AddShaders(curPassName, vs, fs);
		}	
		m_pGpuProgram->AttachShader(*vs);
		m_pGpuProgram->AttachShader(*fs);
		m_pGpuProgram->Link();
	}
	
	// set the GPU program as current program
	if(m_pBoundGpuProgram != m_pGpuProgram)
	{
		BoundGpuProgram(m_pGpuProgram);
		// use program
		m_pGpuProgram->Use();
	}
	
	// send all material parameters to shader
	LJMaterial::LJMatParams *params = material->GetParams();
	UpdateShaderParams(params);
	return LJ_OK;
}

HRESULT LJOpenGL::RenderGeometry(LJGeometry& geo)
{
	HRESULT hr = LJ_OK;
	LJMaterial::LJMatParams *additionalParams = geo.GetAdditionalMatParams();
	if (additionalParams)
	{
		if (LJFailed(UpdateShaderParams(additionalParams)))
		{
			hr = LJ_FAIL;
		}
	}
	LJMatrix4 matWorld = geo.GetWorldMatrix();
	// set world matrix
	SetWorldMatrix(matWorld);

	updateViewProjMatrix();

	updateWorldViewProjMatrix();
	// set view matrix
	if (m_Mode == LJ_DM_PERSPECTIVE)
	{
		m_pBoundGpuProgram->SetUniform("ViewMatrix", m_MatView3D);
	}
	else
	{
		m_pBoundGpuProgram->SetUniform("ViewMatrix", m_MatView2D);
	}
	// set world matrix
	m_pBoundGpuProgram->SetUniform("WorldMatrix", matWorld);
	// set normal matrix
	m_pBoundGpuProgram->SetUniform("NormalMatrix", m_MatNormal);
	// set world view matirx
	m_pBoundGpuProgram->SetUniform("WorldViewMatrix", m_MatWorldView);
	// set view projection matrix
	m_pBoundGpuProgram->SetUniform("ViewProjectionMatrix", m_MatViewProj);
	// set world view projection matrix
	m_pBoundGpuProgram->SetUniform("WorldViewProjectionMatrix", m_MatWorldViewProj);
	// set camera position
	m_pBoundGpuProgram->SetUniform("CameraPosition", m_CamPos);
	// set window width
	m_pBoundGpuProgram->SetUniform("WindowWidth", static_cast<UINT>(m_dwWidth));
	// set window height 
	m_pBoundGpuProgram->SetUniform("WindowHeight", static_cast<UINT>(m_dwHeight));
	if (LJFailed(RenderMesh(*geo.GetMesh())))
	{
		hr = LJ_FAIL;
	}
	return hr;
}

/* ==========================================================
				       PRIVATE FUNCTIONS
   ========================================================== */
void LJOpenGL::updateViewProjMatrix()
{
	switch(m_Mode)
	{
	case LJ_WEQS:
		m_MatViewProj = m_MatProj2D * m_MatView2D;
		break;
	case LJ_DM_ORTHOGONAL:
		m_MatViewProj = m_MatOrth3D * m_MatView3D;
		break;
	case LJ_DM_PERSPECTIVE:
		m_MatViewProj = m_MatPers3D * m_MatView3D;
		break;
	default:
		// SHOULD NOT BE HERE
		LJLog("LJOpenGL : BAD PROJECTION MODE" , "SOMETHING WENT WRONG! CHECK YOUR CODE!");
		break;
	}
}

void LJOpenGL::updateWorldViewProjMatrix()
{
	switch(m_Mode)
	{
	case LJ_WEQS:
		m_MatWorldViewProj = m_MatProj2D * m_MatView2D * m_MatWorld;
		m_MatWorldView = m_MatView2D * m_MatWorld;
		break;
	case LJ_DM_ORTHOGONAL:
		m_MatWorldViewProj = m_MatOrth3D * m_MatView3D * m_MatWorld;
		m_MatWorldView = m_MatView3D * m_MatWorld;
		break;
	case LJ_DM_PERSPECTIVE:
		m_MatWorldViewProj = m_MatPers3D * m_MatView3D * m_MatWorld;
		m_MatWorldView = m_MatView3D * m_MatWorld;
		break;
	default:
		// SHOULD NOT BE HERE
		LJLog("LJOpenGL : BAD PROJECTION MODE" , "SOMETHING WENT WRONG! CHECK YOUR CODE!");
		break;
	}
	updateNormalMatrix();
}

void LJOpenGL::updateNormalMatrix()
{
	LJVector3 c0(m_MatWorldView[0]);
	LJVector3 c1(m_MatWorldView[1]);
	LJVector3 c2(m_MatWorldView[2]);
	LJMatrix3 worldView33(c0, c1, c2);
	LJMatrix3 normalMatrix;
	ljm::inverse(worldView33, &normalMatrix);
	m_MatNormal = ljm::transpose(normalMatrix);
}

HRESULT LJOpenGL::OneTimeInit(void)
{
	m_pTexManager = new LJOGLTextureManager();
	m_pInterTexManager = new LJInterTextureManager();
	m_pVCManager = new LJOGLRenderManager(this, m_pLog);
	m_pMatManager = new LJOGLMaterialManager();
	m_pInterProgManager = new LJProgramManager();
	m_pImgManager = new LJImageManager();
	m_Mode = LJ_DM_PERSPECTIVE;
	// no active stage
	m_nStage = LJ_STAGE_MAX;
	return LJ_OK;
}

HRESULT LJOpenGL::UpdateShaderParams(const LJMaterial::LJMatParams *params)
{
	LJMaterial::LJMatParams::const_iterator it_params = params->begin();
	LJMaterial::LJMatParams::const_iterator it_end = params->end();
	while(it_params != it_end)
	{
		const LJMaterial::LJMatParam *param = &it_params->second;
		LJMatParamType type = param->Type();
		char* name = const_cast<char*>(param->Name().c_str());
		void* val = const_cast<void*>(param->Value());
		switch(type)
		{
		case LJFLOAT:
			m_pBoundGpuProgram->SetUniform(name,*static_cast<float*>(val));
			break;
		case LJBOOL:
		case LJINT:
			m_pBoundGpuProgram->SetUniform(name, *static_cast<int*>(val));
			break;
		case LJVECTOR3f:
			m_pBoundGpuProgram->SetUniform(name, *static_cast<LJVector3*>(val));
			break;
		case LJVECTOR4f:
			m_pBoundGpuProgram->SetUniform(name, *static_cast<LJVector4*>(val));
			break;
		case LJMATRIX3f:
			m_pBoundGpuProgram->SetUniform(name, *static_cast<LJMatrix3*>(val));
			break;
		case LJMATRIX4f:
			m_pBoundGpuProgram->SetUniform(name, *static_cast<LJMatrix4*>(val));
			break;
		case LJTEXTURE:
		case LJTEXTURE2D:
		//case LJTEXTURE3D:
		case LJTEXTURECUBE:
			m_pBoundGpuProgram->SetUniform(name, *static_cast<int*>(val));
			break;
		case LJ_SHADER_SUBROUTINE:
			m_pBoundGpuProgram->SetSubroutine(name, *static_cast<LJGLSLShader::LJSHADERTYPE*>(val));
			break;
		default:
			LJLog("LJOpenGL", "WARNING : Parameter type not support");
			return LJ_FAIL;
		}
		++it_params;
	}
	return LJ_OK;
}

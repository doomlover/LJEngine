#include "LJFramebuffer.h"

void LJFramebuffer::init()
{
	m_pRenderTextures = new RenderTextures();
}

void LJFramebuffer::copy(const LJFramebuffer& fb)
{
	*m_pRenderTextures = *fb.m_pRenderTextures;
	if(fb.m_pDepthTex)
	{
		if(m_pDepthTex)
		{
			*m_pDepthTex = *fb.m_pDepthTex;
		}
		else {
			m_pDepthTex = new LJRenderTexture(*fb.m_pDepthTex);
		}
	}
	m_bRenderDepthTexture = fb.m_bRenderDepthTexture;
}

void LJFramebuffer::release()
{
	if(m_pRenderTextures)
	{
		delete m_pRenderTextures;
	}
	if(m_pDepthTex)
	{
		delete m_pDepthTex;
	}
}

LJFramebuffer::LJFramebuffer():
m_nNumRenderTextures(0), m_pRenderTextures(NULL),
m_pDepthTex(NULL), m_bRenderDepthTexture(false),
m_bUpdated(true)
{
	init();
}

LJFramebuffer::LJFramebuffer(const LJFramebuffer& fb)
{
	init();
	copy(fb);
}

LJFramebuffer::~LJFramebuffer(void)
{
	release();
}

LJFramebuffer& LJFramebuffer::operator=(const LJFramebuffer& fb)
{
	copy(fb);
	return *this;
}

int LJFramebuffer::AddRenderTexture(const LJRenderTexture& renderTex)
{
	if(m_nNumRenderTextures < LJ_MAX_RENDER_BUFFERS)
	{
		m_pRenderTextures->push_back(renderTex);
		++m_nNumRenderTextures;
		return m_nNumRenderTextures-1;
	}
	LJLog("ERROR", "Reach max number of render buffers");
	return -1;
}

LJRenderTexture* LJFramebuffer::InterGetRenderTexture(int attachPointer) const
{
	if((RenderTextures::size_type)attachPointer < m_pRenderTextures->size())
	{
		return &(*m_pRenderTextures)[attachPointer];
	}
	return NULL;
}

const LJRenderTexture* LJFramebuffer::GetRenderTexture(int attachPointer) const
{
	return InterGetRenderTexture(attachPointer);
}

LJRenderTexture* LJFramebuffer::GetRenderTexture(int attachPointer)
{
	return InterGetRenderTexture(attachPointer);
}

void LJFramebuffer::SetDepthTexture(const LJRenderTexture& depthTexture)
{
	if(m_pDepthTex)
	{
		*m_pDepthTex = depthTexture;
	}
	else
	{
		m_pDepthTex = new LJRenderTexture(depthTexture);
	}
}

UINT LJFramebuffer::GetNumberRenderTextures() const
{
	return m_nNumRenderTextures;
}

const LJRenderTexture* LJFramebuffer::GetDepthTexture() const
{
	return m_pDepthTex;
}

LJRenderTexture* LJFramebuffer::GetDepthTexture()
{
	return m_pDepthTex;
}

#ifndef LJFRAMEBUFFER_H
#define LJFRAMEBUFFER_H

#include "LJGeneralHeaders.h"
#include "LJRenderTexture.h"
#include <vector>
using std::vector;
/*
 * LJFramebuffer is a information collector
 * about how is off-screen rendering being set.
 */
class _LJExport LJFramebuffer
{
	typedef vector<LJRenderTexture> RenderTextures;

	UINT m_nNumRenderTextures;
	RenderTextures *m_pRenderTextures;
	LJRenderTexture *m_pDepthTex;
	bool m_bRenderDepthTexture;
	bool m_bUpdated;

	void init();
	void copy(const LJFramebuffer& fb);
	void release();
	LJRenderTexture* InterGetRenderTexture(int attP) const;
public:
	LJFramebuffer();

	LJFramebuffer(const LJFramebuffer& fb);

	~LJFramebuffer(void);

	LJFramebuffer& operator=(const LJFramebuffer& fb);
	/* add a render texture, return the index(attachPointer) to user */
	int AddRenderTexture(const LJRenderTexture& renderTex);
	/* get render texture with attachPointer(index) */
	const LJRenderTexture* GetRenderTexture(int attachPointer) const;

	LJRenderTexture* GetRenderTexture(int attachPointer);
	/* add a depth texture */
	void SetDepthTexture(const LJRenderTexture& depthTexture);

	UINT GetNumberRenderTextures() const;

	const LJRenderTexture* GetDepthTexture() const;

	LJRenderTexture* GetDepthTexture();

	void SetUpdated(bool up) { m_bUpdated = up; }
	bool IsUpdated() const { return m_bUpdated; }
};//~LJFramebuffer

#endif

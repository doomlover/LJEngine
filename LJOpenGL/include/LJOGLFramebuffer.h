/*
 * LJOGLFramebuffer.h
 *
 *  Created on: Mar 14, 2014
 *      Author: liu
 */

#ifndef LJOGLFRAMEBUFFER_H_
#define LJOGLFRAMEBUFFER_H_
#include <GL/glew.h>
#include "LJFramebuffer.h"
/*
 * OpenGL device framebuffer
 */
class LJOGLFramebuffer
{
	friend class LJOpenGL;
	LJFramebuffer *m_Fb;
	UINT m_OGLFBHandle;
	UINT m_OGLRBHandle;
	//bool m_bInitialized;
public:
	LJOGLFramebuffer():m_Fb(NULL), m_OGLFBHandle(LJ_MAX_ID), m_OGLRBHandle(LJ_MAX_ID){}
	~LJOGLFramebuffer(void)
	{
		if(m_OGLFBHandle != LJ_MAX_ID)
		{
			glDeleteFramebuffers(1, &m_OGLFBHandle);
		}
		if(m_OGLRBHandle != LJ_MAX_ID)
		{
			glDeleteRenderbuffers(1, &m_OGLRBHandle);
		}
	}
	void SetFramebuffer(LJFramebuffer* fb){m_Fb = fb;}
	LJFramebuffer* GetFramebuffer(){return m_Fb;}
};



#endif /* LJOGLFRAMEBUFFER_H_ */

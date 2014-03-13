#ifndef LJFRAMELISTENER_H
#define LJFRAMELISTENER_H

#include "LJGeneralHeaders.h"

class LJApplication;
/*
 * Frame listener interface
 */
class _LJExport LJFrameListener
{
public:
	virtual ~LJFrameListener(void){}
	virtual void FrameStarted(float tpf, LJApplication *app) = 0;
	virtual void FrameEnded(float tpf, LJApplication *app) = 0;
};//~FrameListener

#endif

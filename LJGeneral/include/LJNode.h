#ifndef LJNODE_H
#define LJNODE_H

#include "LJSpatial.h"
#include <list>
using std::list;
/*
 * Generic scene graph element type
 */
class _LJExport LJNode : public LJSpatial
{
public:
	typedef list<LJSpatial*> CHILDLIST;
	LJNode();
	virtual ~LJNode(void);
	int AttachChild(LJSpatial& child);
	HRESULT DetachChild(LJSpatial& child);
	CHILDLIST GetChildList();
	const CHILDLIST GetChildList()const;
	
private:
	CHILDLIST *m_pChildList;
};//~LJNode

#endif

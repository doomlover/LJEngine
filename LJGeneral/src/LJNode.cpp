#include "LJNode.h"
#include "LJGeometry.h"

LJNode::LJNode()
{
	m_pChildList = new CHILDLIST();
}
LJNode::~LJNode(void)
{
	LJLog("~LJNode", "");
	if(m_pChildList)
	{
		CHILDLIST::iterator it = m_pChildList->begin();
		while(it != m_pChildList->end())
		{
			delete *it;
			++it;
		}
		delete m_pChildList;
	}
}
int LJNode::AttachChild(LJSpatial& child)
{
	m_pChildList->push_back(&child);
	return m_pChildList->size();
}

HRESULT LJNode::DetachChild(LJSpatial& child)
{
	if(child.GetParent() != this)
		return LJ_FAIL;
	CHILDLIST::iterator it = m_pChildList->begin();
	while(it != m_pChildList->end())
	{
		if(&child == *it)
		{
			m_pChildList->erase(it);
			return LJ_OK;
		}
		++it;
	}
	return LJ_FAIL;
}

const LJNode::CHILDLIST LJNode::GetChildList()const
{
	return *m_pChildList;
}

LJNode::CHILDLIST LJNode::GetChildList()
{
	return *m_pChildList;
}

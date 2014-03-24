#ifndef LJBOUNDINGBOX_H
#define LJBOUNDINGBOX_H

#include "LJBoundingVolume.h"

class _LJExport LJBoundingBox : public LJBoundingVolume
{
	// center of box
	LJVector3 m_Center;
	// principal axes
	LJVector3 m_R;
	LJVector3 m_S;
	LJVector3 m_T;
	// extend along principal axes
	float m_ExtendR;
	float m_ExtendS;
	float m_ExtendT;
public:
	LJBoundingBox();

	~LJBoundingBox(void){};

	LJVector3 GetCenter() const;

	static LJBoundingBox CalculateBoundingBox(const LJVector3 *vertices, UINT num);
};

#endif

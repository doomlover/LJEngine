#include "LJBoundingBox.h"

LJBoundingBox::LJBoundingBox()
:m_ExtendR(0.f),
 m_ExtendS(0.f),
 m_ExtendT(0.f)
{}

LJVector3 LJBoundingBox::GetCenter() const
{
	return m_Center;
}

LJBoundingBox LJBoundingBox::CalculateBoundingBox(const LJVector3 *vertices, UINT num)
{
	// average position
	LJVector3 m;
	for(UINT i = 0; i < num; ++i)
	{
		m += vertices[i];
	}
	m /= num;

	// build the convariance matrix
	float c11, c22, c33, c12, c21, c13, c31, c23, c32;
	c11 = 0;
	c22 = 0;
	c33 = 0;
	c12 = c13 = c23 = 0;
	for(UINT i = 0; i < num; ++i)
	{
		float xm = vertices[i].x - m.x;
		c11 += xm * xm;

		float ym = vertices[i].y - m.y;
		c22 += ym * ym;

		float zm = vertices[i].z - m.z;
		c33 += zm * zm;

		float xmym = xm*ym;
		float xmzm = xm*zm;
		float ymzm = ym*zm;
		c12 += xmym;
		c13 += xmzm;
		c23 += ymzm;
	}
	c11 /= num;
	c22 /= num;
	c33 /= num;
	c12 /= num;
	c13 /= num;
	c23 /= num;
	c21 = c12;
	c31 = c13;
	c32 = c23;

	return LJBoundingBox();
}

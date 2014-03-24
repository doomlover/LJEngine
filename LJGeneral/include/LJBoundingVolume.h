#ifndef LJBOUNDINGVOLUME_H
#define LJBOUNDINGVOLUME_H

#include "LJGeneralType.h"

class _LJExport LJBoundingVolume 
{
public:
	typedef enum _Type
	{
		Box,
		Sphere,
		Ellipsoid,
		Cylinder
	} Type;

	virtual ~LJBoundingVolume(void){}

	// get the center of bounding volume
	virtual LJVector3 GetCenter() const = 0;
};

#endif
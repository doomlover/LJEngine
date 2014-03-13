#ifndef LJGEOMETRY_H
#define LJGEOMETRY_H

#include "LJGeneralHeaders.h"
#include "LJSpatial.h"
#include "LJMaterial.h"
#include <string>
using std::string;

class LJMesh;
/*
 * A LJGeometry is constructed by a material id and
 * a LJMesh
 */
class _LJExport LJGeometry : public LJSpatial
{
public:
	LJGeometry();

	virtual ~LJGeometry(void);

	void SetMesh(LJMesh *pMesh);

	void SetMaterial(int nMaterial);

	LJMesh* GetMesh();

	const LJMesh* GetMesh() const;

	int GetMaterial() const;

	void SetAdditionalMatParam(const LJMaterial::LJMatParam& param);

	LJMaterial::LJMatParams* GetAdditionalMatParams();

	const LJMaterial::LJMatParams* GetAdditionalMatParams()const;
private:
	LJMesh *m_pMesh;
	int m_nMaterial;
	LJMaterial::LJMatParams *m_pAdditionalMatParams;
};

#endif

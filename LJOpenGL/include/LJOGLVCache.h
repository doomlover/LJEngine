#ifndef LJOGLCACHE_H
#define LJOGLCACHE_H

#include "LJGeneralHeaders.h"
#include <cstdio>
#include <vector>
using std::vector;

/* Forward Declaration */
class LJOpenGL;
class LJMesh;
class LJGeometry;
/*
 * Geometry container indexed by material id
 * for internal usage of rendering.
 * This container caches the geometries
 * having the same material id.
 */
class LJOGLVCache
{
public:
	LJOGLVCache(LJOpenGL *pDevice, FILE *pLog);

	~LJOGLVCache(void);
	/* Return the material id used by this container */
	int GetMaterial() {return m_nMaterialID;}
	/* Set the material id used ty this container */
	void SetMaterial(int nMatID);
	/* flush all meshes of Geometries cached in this
	 * container. After flush, all cached geometries
	 * will be removed.
	 */
	HRESULT Flush()  {return Flush(true);}
	/* Parameter not used */
	HRESULT Flush(bool bUseShaders);
	/* Cache a new geometry */
	HRESULT Add(LJGeometry* pGeometry);
	/* Is empth ? */
	bool IsEmpty() const{ return m_pGeometrys->size() == 0; }
	/* geometry container type */
	typedef vector<LJGeometry*> GEOMETRYS;
private:
	int m_nMaterialID;			// material id
	LJOpenGL *m_pDevice;		// render device pointer
	GEOMETRYS *m_pGeometrys;	// geometries list
};

#endif

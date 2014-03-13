#ifndef LJSPATIAL_H
#define LJSPATIAL_H
#include "LJGeneralHeaders.h"
#include <string>
using std::string;
class LJNode;
/*
 * All rotation angles are specified by radian
 */
class _LJExport LJSpatial
{
public:
	LJSpatial();
	virtual ~LJSpatial(void);
	void SetLocalTranslation(float tx, float ty, float tz);
	void SetLocalRotation(float rx, float ry, float rz);
	void SetLocalRotation(const LJVector3& v, float angle);
	void SetLocalScale(float kx, float ky, float kz);
	void SetLocalScale(const LJVector3& v, float k);

	LJVector3 GetLocalTranslation() const {return *m_pTranslate;}
	LJQuat GetLocalRotation() const {return *m_pQuat;}
	LJMatrix3 GetLocalScale() const {return *m_pScaMatr;}

	/* Set non-local transformations based on transformations
	 * which are already applied.
	 * The result is affected by the order which these
	 * non-local transformations are applied in.
	 */
	void SetTranslation(float tx, float ty, float tz);
	void SetRotation(float rx, float ry, float rz);
	void SetRotation(const LJVector3& v, float angle);
	void SetScale(float kx, float ky, float kz);
	void SetScale(const LJVector3& v, float k);

	void UpdateLocalMatrix();
	LJMatrix4 GetWorldMatrix();

	void SetName(const char* chName);
	const char* GetName() const;
	const LJNode* GetParent() const;
	LJNode* GetParent();
	void SetParent(LJNode* parent);
private:
	// translation
	LJVector3 *m_pTranslate;
	// rotation
	LJQuat *m_pQuat;
	// scale
	LJMatrix3 *m_pScaMatr;
	// World Matrix
	LJMatrix4 *m_pWorldMatrix;
	// Local transform needs update
	bool m_bUpdateLocal;
	// name
	string *m_pName;
	// parent
	LJNode *m_pParent;
};//~LJSpatial

#endif

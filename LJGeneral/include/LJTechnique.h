#ifndef LJTECHNIQUE_H_
#define LJTECHNIQUE_H_

#include "LJGeneralHeaders.h"
#include "LJPass.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

class LJMaterial;
/*
 * A technique is a named wrapper for a collection of passes
 * and serves as the atomic unit for device validation. This
 * means that when the effect API checks for support on a
 * device, each pass within a technique is checked to see if
 * it can operate on the device. If any pass is not supported
 * by the device, the entire technique is considered unsupported
 * on the device. For this reason of validation, passes cannot
 * exist outside a technique. At runtime, techniques also provide
 * support for iterating through each contained pass and accessing
 * information about each pass.
 */

class _LJExport LJTechnique
{
public:
	typedef vector<LJPass> LJPasses;

	LJTechnique();
	LJTechnique(const LJTechnique& tech);
	~LJTechnique(void);
	LJTechnique& operator=(const LJTechnique& tech);
	/*
	 * Set the technique name.
	 */
	void SetName(const char* name) {if(name)m_pName->assign(name);}
	/*
	 * Add a user created pass
	 */
	void AddPass(const LJPass& pass);
	/*
	 * Set name of selected pass
	 */
	void SetCurrentPass(const char* name);
	/* Get TECH name */
	const char* GetName() const {return m_pName->c_str();}
	/* Get pass with the specific name */
	const LJPass* GetPass(const char* name) const;
	LJPass* GetPass(const char* name);
	/* Get pass list */
	const LJPasses* GetPasses() const {return m_pPasses;}
	LJPasses* GetPasses() {return m_pPasses;}
	/* Get current pass */
	const char* GetCurrentPass() const;
private:
	/* self-name */
	string *m_pName;
	/* pass list */
	LJPasses *m_pPasses;
	/* name of current pass in use */
	string *m_pStrSelectPass;
	/* copy */
	void copy(const LJTechnique& tech);
};



#endif /* LJTECHNIQUE_H_ */

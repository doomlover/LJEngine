#ifndef LJPASS_H_
#define LJPASS_H_

#include "LJGeneralHeaders.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class LJTechnique;
class LJRenderState;

/*
 * A pass represents the device state for a single
 * rendering pass of a shader. This includes the
 * associated vertex and pixel pipeline setup.
 * Each pass can have a unique name associated with
 * it and can be accessed by the application.
 * The pass serves as the atomic rendering unit.
 * It is ultimately the source of the device state,
 * and if an object is to be rendered, there must be
 * an active pass to indicate how it is to be rendered.
 */
class _LJExport LJPass
{
public:
	LJPass();
	LJPass(const LJPass& pass);
	~LJPass(void);

	void SetVertCode(const char* code)						{if(code)m_VertCode->assign(code);}
	void SetVertCodeFromFile(const char* file);
	void SetFragCode(const char* code)						{if(code)m_FragCode->assign(code);}
	void SetFragCodeFromFile(const char* file);
	void SetName(const char* name) {if(name){m_Name->assign(name);}}
	void SetRenderState(const LJRenderState& renderState);

	const char* GetVertCode() const {return m_VertCode->c_str();}
	const char* GetFragCode() const {return m_FragCode->c_str();}
	const char* GetName() const {return m_Name->c_str();}
	LJRenderState& GetRenderState();
	const LJRenderState& GetRenderState()const;

	LJPass& operator=(const LJPass& pass);
private:
	string* m_Name;
	string* m_VertCode;
	string* m_FragCode;
	LJRenderState *m_pRenderState;

	string readFileToString(const char* file);
};



#endif /* LJPASS_H_ */

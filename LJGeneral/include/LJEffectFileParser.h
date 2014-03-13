#ifndef EFFECTFILEPARSER_H_
#define EFFECTFILEPARSER_H_

#include "LJGeneralHeaders.h"
#include "LJStringUtil.h"
#include "LJTechnique.h"
#include "LJRenderState.h"
#include "LJMaterial.h"
#include <map>
using std::map;

class _LJExport LJEffectFileParser
{
	typedef map<string, LJMatParamType> TYPEMAP;
	typedef map<string, LJRenderState::LJ_DEPTH_FUNC> DEPFUNCMAP;
	typedef map<string, LJRenderState::LJ_BLEND_EQ> BLENDEQMAP;
	typedef map<string, LJRenderState::LJ_BLEND_FUNC> BLENDFUNCMAP;
	static TYPEMAP m_TypeMap;
	static DEPFUNCMAP m_DepthFuncMap;
	static BLENDEQMAP m_BlendEqMap;
	static BLENDFUNCMAP m_BlendFuncMap;
	static BLENDFUNCMAP InitBlendFunc();
	static DEPFUNCMAP InitDepthFuncMap();
	static TYPEMAP InitTypeMap();
	static BLENDEQMAP InitBlendEq();

	string *m_pFileName;
	int m_nWord;
	int m_nWords;
	WORDS *m_pWords;

	void init(const string& str);
	void release();
	void Read();
	void ParseParameters(LJMaterial& mat);
	void ParseParameter(LJMaterial& mat, LJMatParamType type);
	void ParseTechnique(LJMaterial& mat);
	void InterParseTech(LJTechnique& tech);
	void ParsePass(LJTechnique& tech);
	void InterParsePass(LJPass& pass);
	void ParseRenderState(LJPass& pass);
	string GetWord();
public:
	LJEffectFileParser(const string& str);
	~LJEffectFileParser(void);
	void Parse(LJMaterial& mat);
};//~LJEffectFileParser


#endif /* EFFECTFILEPARSER_H_ */

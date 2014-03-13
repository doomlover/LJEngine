#include "LJEffectFileParser.h"
#include "LJTechnique.h"
#include "LJRenderState.h"
#include "LJStringUtil.h"
#include <fstream>

LJEffectFileParser::TYPEMAP LJEffectFileParser::InitTypeMap()
{
	TYPEMAP map;
	map["Float"] = LJFLOAT;
	map["Int"] = LJINT;
	map["Bool"] = LJBOOL;
	map["Vector3"] = LJVECTOR3f;
	map["Vector4"] = LJVECTOR4f;
	map["Matrix3"] = LJMATRIX3f;
	map["Matrix4"] = LJMATRIX4f;
	map["Texture2D"] = LJTEXTURE2D;
	//map["Texture3D"] = LJTEXTURE3D; // not supported
	map["TextureCube"] = LJTEXTURECUBE;
	return map;
}

LJEffectFileParser::TYPEMAP LJEffectFileParser::m_TypeMap = LJEffectFileParser::InitTypeMap();

LJEffectFileParser::DEPFUNCMAP LJEffectFileParser::InitDepthFuncMap()
{
	DEPFUNCMAP map;
	map["N"] = LJRenderState::LJ_NEVER;
	map["L"] = LJRenderState::LJ_LESS;
	map["EQ"] = LJRenderState::LJ_EQUAL;
	map["LEQ"] = LJRenderState::LJ_LEQUAL;
	map["G"] = LJRenderState::LJ_GREATER;
	map["NEQ"] = LJRenderState::LJ_NOTEQUAL;
	map["GEQ"] = LJRenderState::LJ_GEQUAL;
	map["AL"] = LJRenderState::LJ_ALWAYS;
	return map;
}

LJEffectFileParser::DEPFUNCMAP LJEffectFileParser::m_DepthFuncMap = LJEffectFileParser::InitDepthFuncMap();

LJEffectFileParser::BLENDEQMAP LJEffectFileParser::InitBlendEq()
{
	BLENDEQMAP map;
	map["ADD"] = LJRenderState::LJ_ADD;
	map["SUB"] = LJRenderState::LJ_SUB;
	map["FUNCREVSUB"] = LJRenderState::LJ_FUNC_REV_SUB;
	map["MIN"] = LJRenderState::LJ_MIN;
	map["MAX"] = LJRenderState::LJ_MAX;
	return map;
}

LJEffectFileParser::BLENDEQMAP LJEffectFileParser::m_BlendEqMap = LJEffectFileParser::InitBlendEq();

LJEffectFileParser::BLENDFUNCMAP LJEffectFileParser::InitBlendFunc()
{
	BLENDFUNCMAP map;
	map["Z"] = LJRenderState::LJ_ZERO;
	map["ONE"] = LJRenderState::LJ_ONE;
	map["SRCCLR"] = LJRenderState::LJ_SRC_COLOR;
	map["OMSC"] = LJRenderState::LJ_ONE_MINUS_SRC_COLOR;
	map["DSTCLR"] = LJRenderState::LJ_DST_COLOR;
	map["OMDC"] = LJRenderState::LJ_ONE_MINUS_DST_COLOR;
	map["SRCALP"] = LJRenderState::LJ_SRC_ALPHA;
	map["OMSA"] = LJRenderState::LJ_ONE_MINUS_SRC_ALPHA;
	map["DSTALP"] = LJRenderState::LJ_DST_ALPHA;
	map["OMDA"] = LJRenderState::LJ_ONE_MINUS_DST_ALPHA;
	map["CCLR"] = LJRenderState::LJ_CONSTANT_COLOR;
	map["OMCC"] = LJRenderState::LJ_ONE_MINUS_CONSTANT_COLOR;
	map["CALP"] = LJRenderState::LJ_CONSTANT_ALPHA;
	map["OMCA"] = LJRenderState::LJ_ONE_MINUS_CONSTANT_ALPHA;
	return map;
}

LJEffectFileParser::BLENDFUNCMAP LJEffectFileParser::m_BlendFuncMap(LJEffectFileParser::InitBlendFunc());

void LJEffectFileParser::init(const string& str)
{
	m_pFileName = new string(str);
	m_pWords = new WORDS();
}

void LJEffectFileParser::release()
{
	if(m_pFileName)
	{
		delete m_pFileName;
	}
	if(m_pWords)
	{
		delete m_pWords;
	}
}

LJEffectFileParser::LJEffectFileParser(const string& str)
:m_pFileName(NULL),
 m_nWord(-1),
 m_nWords(0),
 m_pWords(NULL)
{
	init(str);
}

LJEffectFileParser::~LJEffectFileParser(void)
{
	release();
}

void LJEffectFileParser::Read()
{
	using std::ifstream;
	ifstream file(m_pFileName->c_str(), std::ios::in);
	if(!file.is_open())
	{
		throw "Can not open effect file";
	}
	// read file into words
	string word;
	while(file >> word)
	{
		m_pWords->push_back(word);
	}
	if((m_nWords = m_pWords->size()) > 0)
	{
		m_nWord = 0;
	}
	else
	{
		throw "Empty file";
	}
}

string LJEffectFileParser::GetWord()
{
	if(m_nWord < m_nWords)
	{
		return (*m_pWords)[m_nWord++];
	}
	else
		throw "No more words";
}

void LJEffectFileParser::Parse(LJMaterial& mat)
{
	Read();
	for(; m_nWord < m_nWords;)
	{
		string word = GetWord();
		if(word == "Technique")
		{
			ParseTechnique(mat);
		}
		else if(word == "Parameters")
		{
			ParseParameters(mat);
		}
	}
}

void LJEffectFileParser::ParseParameter(LJMaterial& mat, LJMatParamType type)
{
	LJMatParamType matType = type;
	string name = GetWord();
	switch(matType)
	{
	case LJFLOAT:
	{
		float val = LJStringUtil::StrToFloat(GetWord());
		mat.SetParam(name.c_str(), matType, val);
	}
		break;
	case LJINT:
	case LJBOOL:
	{
		int val = LJStringUtil::StrToInt(GetWord());
		mat.SetParam(name.c_str(), matType, val);
	}
		break;
	case LJVECTOR3f:
	{
		float x = LJStringUtil::StrToFloat(GetWord());
		float y = LJStringUtil::StrToFloat(GetWord());
		float z = LJStringUtil::StrToFloat(GetWord());
		mat.SetParam(name.c_str(), matType, LJVector3(x, y, z));
	}
		break;
	case LJVECTOR4f:
		{
			float x = LJStringUtil::StrToFloat(GetWord());
			float y = LJStringUtil::StrToFloat(GetWord());
			float z = LJStringUtil::StrToFloat(GetWord());
			float w = LJStringUtil::StrToFloat(GetWord());
		mat.SetParam(name.c_str(), matType, LJVector4(x, y, z, w));
		}
		break;
	case LJMATRIX3f:
		{
			float x0, x1, x2;
			float y0, y1, y2;
			float z0, z1, z2;
			x0 = LJStringUtil::StrToFloat(GetWord());
			x1 = LJStringUtil::StrToFloat(GetWord());
			x2 = LJStringUtil::StrToFloat(GetWord());
			y0 = LJStringUtil::StrToFloat(GetWord());
			y1 = LJStringUtil::StrToFloat(GetWord());
			y2 = LJStringUtil::StrToFloat(GetWord());
			z0 = LJStringUtil::StrToFloat(GetWord());
			z1 = LJStringUtil::StrToFloat(GetWord());
			z2 = LJStringUtil::StrToFloat(GetWord());
		mat.SetParam(name.c_str(), matType, LJMatrix3(x0, x1, x2, y0, y1, y2, z0, z1, z2));
		}
		break;
	case LJMATRIX4f:
		{
			float x0, x1, x2, x3;
			float y0, y1, y2, y3;
			float z0, z1, z2, z3;
			float w0, w1, w2, w3;
			x0 = LJStringUtil::StrToFloat(GetWord());
			x1 = LJStringUtil::StrToFloat(GetWord());
			x2 = LJStringUtil::StrToFloat(GetWord());
			x3 = LJStringUtil::StrToFloat(GetWord());
			y0 = LJStringUtil::StrToFloat(GetWord());
			y1 = LJStringUtil::StrToFloat(GetWord());
			y2 = LJStringUtil::StrToFloat(GetWord());
			y3 = LJStringUtil::StrToFloat(GetWord());
			z0 = LJStringUtil::StrToFloat(GetWord());
			z1 = LJStringUtil::StrToFloat(GetWord());
			z2 = LJStringUtil::StrToFloat(GetWord());
			z3 = LJStringUtil::StrToFloat(GetWord());
			w0 = LJStringUtil::StrToFloat(GetWord());
			w1 = LJStringUtil::StrToFloat(GetWord());
			w2 = LJStringUtil::StrToFloat(GetWord());
			w3 = LJStringUtil::StrToFloat(GetWord());
		mat.SetParam(name.c_str(), matType, LJMatrix4(x0, x1, x2, x3,
				                                      y0, y1, y2, y3,
				                                      z0, z1, z2, z3,
				                                      w0, w1, w2, w3));
		}
		break;
	case LJTEXTURE2D:
		{
			string val = GetWord();
		LJTexture tex2d;
		tex2d.SetName(name.c_str());
		tex2d.SetTarget(LJ_TEXTURE_2D);
		tex2d.AddImage(val.c_str());
		mat.SetParam(name.c_str(), tex2d);
		}
		break;
	//case LJTEXTURE3D:
	//	break;
	case LJTEXTURECUBE:
	{
		string posx = GetWord();
		string negx = GetWord();
		string posy = GetWord();
		string negy = GetWord();
		string posz = GetWord();
		string negz = GetWord();
		LJTexture texCube;
		texCube.SetName(name.c_str());
		texCube.SetTarget(LJ_TEXTURE_CUBE_MAP);
		texCube.AddImage(posx.c_str());
		texCube.AddImage(negx.c_str());
		texCube.AddImage(posy.c_str());
		texCube.AddImage(negy.c_str());
		texCube.AddImage(posz.c_str());
		texCube.AddImage(negz.c_str());
		texCube.SetParameter(LJ_TEXTURE_MAG_FILTER, LJ_LINEAR);
		texCube.SetParameter(LJ_TEXTURE_MIN_FILTER, LJ_LINEAR);
		texCube.SetParameter(LJ_TEXTURE_WRAP_S, LJ_CLAMP_TO_EDGE);
		texCube.SetParameter(LJ_TEXTURE_WRAP_T, LJ_CLAMP_TO_EDGE);
		texCube.SetParameter(LJ_TEXTURE_WRAP_R, LJ_CLAMP_TO_EDGE);
		mat.SetParam(name.c_str(), texCube);
	}
		break;
	default:
		throw "Invalid parameter type";
	}
}

void LJEffectFileParser::ParseParameters(LJMaterial& mat)
{
	string word = GetWord();
	if(word != "{")
		throw "Invalid format";
	for(; m_nWord < m_nWords;)
	{
		word = GetWord();
		if(word == "}")
			break;
		LJMatParamType type = m_TypeMap[word];
		ParseParameter(mat, type);
	}
}

void LJEffectFileParser::ParseTechnique(LJMaterial& mat)
{
	string word = GetWord();
	LJTechnique tec;
	if(word != ":" && word != "{")
	{
		tec.SetName(word.c_str());
	}
	else {
		throw "tech no name";
	}
	word = GetWord();
	if(word == ":")
	{
		string sel = GetWord();
		if(sel != "Selected")
			throw "Invalid format";
		mat.SetCurrentTech(string(tec.GetName()));
		// consume the "{"
		if(GetWord() != "{")
			throw "Invalid format";
	}
	else if (word != "{"){
		throw "Invalid format";
	}
	InterParseTech(tec);
	mat.AddTechnique(tec);
}

void LJEffectFileParser::InterParseTech(LJTechnique& tec)
{
	string word;
	for(; m_nWord < m_nWords;)
	{
		word = GetWord();
		if(word == "}")
			break;
		if(word == "Pass")
		{
			ParsePass(tec);
		}
	}
}

void LJEffectFileParser::ParsePass(LJTechnique& tech)
{
	string word = GetWord();
	LJPass pass;
	if(word != ":" && word != "{")
	{
		pass.SetName(word.c_str());
	}
	else {
		throw "pass no name";
	}
	word = GetWord();
	if(word == ":")
	{
		string sel = GetWord();
		if(sel != "Selected")
			throw "Invalid format";
		tech.SetCurrentPass(pass.GetName());
		if(GetWord() != "{") // consume the "{"
			throw "Invalid format";
	}
	else if (word != "{"){
		throw "Invalid format";
	}
	InterParsePass(pass);
	tech.AddPass(pass);
}

void LJEffectFileParser::InterParsePass(LJPass& pass)
{
	string word;
	for(;m_nWord < m_nWords;)
	{
		word = GetWord();
		if(word == "}")
			break;
		if(word == "vs") {
			if(GetWord() != "=")
				throw "Invalid format";
			pass.SetVertCodeFromFile(GetWord().c_str());
		}
		else if(word == "fs") {
			if(GetWord() != "=")
				throw "Invalid format";
			pass.SetFragCodeFromFile(GetWord().c_str());
		}
		else if(word == "gs") {
			if(GetWord() != "=")
				throw "Invalid format";
		}
		else if(word == "RenderState") {
			ParseRenderState(pass);
		}
		else {
			throw "Invalid format";
		}
	}
}

void LJEffectFileParser::ParseRenderState(LJPass& pass)
{
	string word = GetWord();
	if(word != "{") // consume "{"
		throw "Invalid format";
	LJRenderState rs;
	for(; m_nWord < m_nWords; )
	{
		word = GetWord();
		if(word == "}")
			break;
		if(word == "CullFace")
		{
			string val = GetWord();
			if(val == "1")
			{
				rs.SetCullFace(true);
			}
			else {
				rs.SetCullFace(false);
			}
		}
		else if(word == "Depth")
		{
			string val = GetWord();
			if(val == "1")
			{
				rs.SetDepth(true);
			}
			else {
				rs.SetDepth(false);
			}
		}
		else if(word == "Blend")
		{
			string val = GetWord();
			if(val == "1")
			{
				rs.SetBlend(true);
			}
			else {
				rs.SetBlend(false);
			}
		}
		else if(word == "Dither")
		{
			string val = GetWord();
			if(val == "1")
			{
				rs.SetDither(true);
			}
			else {
				rs.SetDither(false);
			}
		}
		else if(word == "Scissor")
		{
			string val = GetWord();
			if(val == "1")
			{
				rs.SetScissor(true);
			}
			else {
				rs.SetScissor(false);
			}
		}
		else if(word == "Stencil")
		{
			string val = GetWord();
			if(val == "1")
			{
				rs.SetStencil(true);
			}
			else {
				rs.SetStencil(false);
			}
		}
		else if(word == "CullMode")
		{
			string val = GetWord();
			if(val == "F")
			{
				rs.SetCullFaceMode(LJRenderState::LJ_FRONT);
			}
			else if(val == "B") {
				rs.SetCullFaceMode(LJRenderState::LJ_BACK);
			}
			else {
				rs.SetCullFaceMode(LJRenderState::LJ_FRONT_BACK);
			}
		}
		else if(word == "FrontFace")
		{
			string val = GetWord();
			if(val == "CW") {
				rs.SetFrontFaceMode(LJRenderState::LJ_CW);
			}
			else
			{
				rs.SetFrontFaceMode(LJRenderState::LJ_CCW);
			}
		}
		else if(word == "DepthFunc") {
			string val = GetWord();
			rs.SetDepthFunc(m_DepthFuncMap[val]);
		}
		else if(word == "BlendFuncSrc") {
			string val = GetWord();
			rs.SetBlendFuncSrc(m_BlendFuncMap[val]);
		}
		else if(word == "BlendFuncDes") {
			string val = GetWord();
			rs.SetBlendFuncDes(m_BlendFuncMap[val]);
		}
		else if(word == "BlendEq") {
			string val = GetWord();
			rs.SetBlendEq(m_BlendEqMap[val]);
		}
		else if(word == "PolygonMode") {
			string val = GetWord();
			if(val == "P") {
				rs.SetPolygonMode(LJRenderState::LJ_POINT);
			}
			else if(val == "L") {
				rs.SetPolygonMode(LJRenderState::LJ_LINE);
			}
			else {
				rs.SetPolygonMode(LJRenderState::LJ_FILL);
			}
		}
		else if(word == "ColorMask") {
			rs.SetColorMask(LJRenderState::COLORMASK(
					(GetWord()=="true"?true:false),
					(GetWord()=="true"?true:false),
					(GetWord()=="true"?true:false),
					(GetWord()=="true"?true:false)
					));
		}
		else if(word == "DepthRange") {
			rs.SetDepthRange(LJRenderState::DEPTHRANGE(
					LJStringUtil::StrToFloat(GetWord()),
					LJStringUtil::StrToFloat(GetWord())
					));
		}
		else if(word == "BlendColor") {
			rs.SetBlendColor(LJRenderState::BLENDCOLOR(
					LJStringUtil::StrToFloat(GetWord()),
					LJStringUtil::StrToFloat(GetWord()),
					LJStringUtil::StrToFloat(GetWord()),
					LJStringUtil::StrToFloat(GetWord())
					));
		}
		else if(word == "DepthMask") {
			rs.SetDepthMask((LJStringUtil::StrToInt(GetWord()) == 1) ? true : false);
		}
		else if(word == "LineWidth") {
			rs.SetLineWidth(LJStringUtil::StrToFloat(GetWord()));
		}
		else if(word == "PointSize") {
			rs.SetPointSize(LJStringUtil::StrToFloat(GetWord()));
		}
		else {
			throw "Invalid format";
		}
	}
	pass.SetRenderState(rs);
}

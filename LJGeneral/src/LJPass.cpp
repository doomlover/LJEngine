#include "LJPass.h"
#include "LJRenderState.h"

#include <fstream>

LJPass::LJPass()
{
	m_Name = new string();
	m_VertCode = new string();
	m_FragCode = new string();
	m_pRenderState = new LJRenderState();
}

LJPass::LJPass(const LJPass& pass)
{
	m_Name = new string(pass.GetName());
	m_VertCode = new string(pass.GetVertCode());
	m_FragCode = new string(pass.GetFragCode());
	m_pRenderState = new LJRenderState(pass.GetRenderState());
}

LJPass::~LJPass(void)
{

	if(m_Name)
	{
		delete m_Name;
	}

	if(m_VertCode)
	{
		delete m_VertCode;
	}

	if(m_FragCode)
	{
		delete m_FragCode;
	}
	if(m_pRenderState)
	{
		delete m_pRenderState;
	}
}

LJPass& LJPass::operator=(const LJPass& pass)
{
	m_Name->assign(pass.GetName());
	m_VertCode->assign(pass.GetVertCode());
	m_FragCode->assign(pass.GetFragCode());
	*m_pRenderState = pass.GetRenderState();
	return *this;
}

void LJPass::SetVertCodeFromFile(const char* file)
{
	*m_VertCode = readFileToString(file);
}

void LJPass::SetFragCodeFromFile(const char* file)
{
	*m_FragCode = readFileToString(file);
}

string LJPass::readFileToString(const char* file)
{
	using std::ifstream;
	string result;
	if(file)
	{
		result = "";
		ifstream is(file, std::ios::in);
		if(is.is_open())
		{
			string line = "";
			while(std::getline(is, line))
			{
				result += "\n" + line;
			}
			is.close();
		}
	}
	return result;
}

void LJPass::SetRenderState(const LJRenderState& renderState)
{
	 *m_pRenderState = renderState;
}

LJRenderState& LJPass::GetRenderState()
{
	return *m_pRenderState;
}

const LJRenderState& LJPass::GetRenderState() const
{
	return *m_pRenderState;
}

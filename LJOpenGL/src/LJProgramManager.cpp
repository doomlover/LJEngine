#include "LJProgramManager.h"

LJProgramManager::LJProgramManager()
{}
LJProgramManager::~LJProgramManager(void)
{
	m_ProgMap.clear();
	PROGLIST::iterator it = m_ProgList.begin();
	while(it != m_ProgList.end())
	{
		delete *it;
		++it;
	}
	m_ProgList.clear();
}

LJProgram* LJProgramManager::GetProgram(int nMataterial)
{
	PROGMAP::iterator it = m_ProgMap.find(nMataterial);
	if(it != m_ProgMap.end())
	{
		return m_ProgList[it->second];
	}
	else {
		return NULL;
	}
}
const LJProgram* LJProgramManager::GetProgram(int nMataterial)const
{
	PROGMAP::const_iterator it = m_ProgMap.find(nMataterial);
	if(it != m_ProgMap.end())
	{
		return m_ProgList[it->second];
	}
	else {
		return NULL;
	}
}

void LJProgramManager::AddProgram(int nMataterial, LJProgram *prog)
{
	if(GetProgram(nMataterial) == NULL)
	{
		m_ProgList.push_back(prog);
		m_ProgMap[nMataterial] = m_ProgList.size()-1;
	}
}

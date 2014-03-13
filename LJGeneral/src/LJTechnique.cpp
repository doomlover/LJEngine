#include <LJTechnique.h>

LJTechnique::LJTechnique()
:m_pStrSelectPass(NULL)
{
	m_pName = new string();
	m_pPasses = new LJPasses();
}

LJTechnique::LJTechnique(const LJTechnique& tech)
{
	m_pName = new string();
	m_pPasses = new LJPasses();
	copy(tech);
}

LJTechnique::~LJTechnique(void)
{
	if(m_pName)
	{
		delete m_pName;
	}
	if(m_pPasses)
	{
		delete m_pPasses;
	}
	if(m_pStrSelectPass) {
		delete m_pStrSelectPass;
	}
}

LJTechnique& LJTechnique::operator=(const LJTechnique& tech)
{
	copy(tech);
	return *this;
}

/*
 * Add a user created pass
 */
void LJTechnique::AddPass(const LJPass& pass)
{
	m_pPasses->push_back(pass);
}

void LJTechnique::SetCurrentPass(const char* name)
{
	if(name)
	{
		if(!m_pStrSelectPass)
		{
			m_pStrSelectPass = new string(name);
		}
		else
		{
			m_pStrSelectPass->assign(name);
		}
	}
}

const LJPass* LJTechnique::GetPass(const char* name) const
{
	if(!name)
		return NULL;
	LJPasses::const_iterator it = m_pPasses->begin();
	while(it != m_pPasses->end())
	{
		if(strcmp((*it).GetName(), name) == 0)
		{
			return &(*it);
		}
		++it;
	}
	return NULL;
}

LJPass* LJTechnique::GetPass(const char* name)
{
	if(!name)
		return NULL;
	LJPasses::iterator it = m_pPasses->begin();
	while(it != m_pPasses->end())
	{
		if(strcmp((*it).GetName(), name) == 0)
		{
			return &(*it);
		}
		++it;
	}
	return NULL;
}

const char* LJTechnique::GetCurrentPass() const
{
	if(m_pStrSelectPass)
		return m_pStrSelectPass->c_str();
	return NULL;
}

void LJTechnique::copy(const LJTechnique& tech)
{
	const char* chName = tech.GetName();
	if(chName)
	{
		m_pName->assign(tech.GetName());
	}
	const char* chPass = tech.GetCurrentPass();
	if(chPass)
	{
		m_pStrSelectPass = new string(chPass);
	}
	else
	{
		m_pStrSelectPass = NULL;
	}
	const LJPasses *passes = tech.GetPasses();
	if(passes)
	{
		LJPasses::const_iterator it = passes->begin();
		while(it != passes->end())
		{
			m_pPasses->push_back(*it);
			++it;
		}
	}
}

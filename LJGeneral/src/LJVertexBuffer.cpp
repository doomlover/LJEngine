#include "LJVertexBuffer.h"
#include "LJVertexBufferData.h"
#include <cstdio>

LJVertexBuffer::LJVertexBuffer()
	:m_pData(NULL),
	m_BufType(NOTYPE),
	m_Target(LJ_NOTARGET),
	m_Usage(LJ_NOUSAGE),
	m_bNeedUpdate(false),
	m_id(-1),
	m_nStride(0),
	m_bNormalized(false)
{
	m_pAttribName = new string();
}

LJVertexBuffer::~LJVertexBuffer(void)
{
	if(m_pData)
	{
		delete m_pData;
	}
	if(m_pAttribName)
	{
		delete m_pAttribName;
	}
}

const void* LJVertexBuffer::GetData() const
{
	return m_pData->GetData();
}

int LJVertexBuffer::GetSize() const
{
	return m_pData->GetSize();
}

LJVertexBuffer::DATATYPE LJVertexBuffer::GetType() const
{
	return m_pData->GetType();
}

int LJVertexBuffer::GetTypeSize() const
{
	return m_pData->GetTypeSize();
}

int LJVertexBuffer::GetComponent() const
{
	return m_pData->GetComponent();
}

LJVertexBuffer::BUFFERTYPE LJVertexBuffer::GetBufferType() const
{
	return m_BufType;
}

LJVertexBuffer::TARGET LJVertexBuffer::GetTarget() const
{
	return m_Target;
}

LJVertexBuffer::USAGE LJVertexBuffer::GetUsage() const
{
	return m_Usage;
}

string LJVertexBuffer::GetAttribName() const
{
	return *m_pAttribName;
}

int LJVertexBuffer::GetStride() const
{
	return m_nStride;
}

bool LJVertexBuffer::GetNormalized() const
{
	return m_bNormalized;
}

bool LJVertexBuffer::IsNeedUpdate() const
{
	return m_bNeedUpdate;
}

void LJVertexBuffer::SetNeedUpdate(bool up)
{
	m_bNeedUpdate = up;
}

int LJVertexBuffer::GetID() const
{
	int ret = m_id;
	return ret;
}

void LJVertexBuffer::SetAttribName(const char* chName)
{
	if(chName)
	{
		m_pAttribName->assign(chName);
	}
}

void LJVertexBuffer::SetID(int id)
{
	m_id = id;
}

void LJVertexBuffer::SetData(const void *pData, int nComponent, int nSize,
		DATATYPE dataType, BUFFERTYPE bufType, const char* chName, TARGET target, USAGE usage)
{
	if(m_pData == NULL)
	{
		m_pData = new LJVertexBufferData();
	}
	m_pData->SetData(pData, nComponent, nSize, dataType);
	m_BufType = bufType;
	if(m_BufType == ATTRIBUTE)
	{
		m_pAttribName->assign(chName);
	}
	else
	{
		m_pAttribName->assign("");
	}
	m_Target = target;
	m_Usage = usage;
	m_bNeedUpdate = true;
}

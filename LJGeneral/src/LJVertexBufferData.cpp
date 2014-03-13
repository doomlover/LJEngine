#include "LJVertexBufferData.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

LJVertexBufferData::LJVertexBufferData()
	:m_pData(NULL),
	 m_nSize(0),
	 m_Type(LJVertexBuffer::Float),
	 m_nTypeSize(sizeof(float)),
	 m_nComponent(0)
{}

LJVertexBufferData::~LJVertexBufferData(void)
{
	if(m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}
}

const void* LJVertexBufferData::GetData() const
{
	return m_pData;
}

int LJVertexBufferData::GetSize() const
{
	return m_nSize;
}

LJVertexBuffer::VERTEXBUFFERDATATYPE LJVertexBufferData::GetType() const
{
	return m_Type;
}

int LJVertexBufferData::GetTypeSize() const
{
	return m_nTypeSize;
}

int LJVertexBufferData::GetComponent() const
{
	return m_nComponent;
}

void LJVertexBufferData::SetData(const void *pData, int nComponent,int nSize, LJVertexBuffer::VERTEXBUFFERDATATYPE type)
{
	if(pData != NULL && nSize > 0)
	{
		short typeSize = get_type_size(type);
		int n = nSize * typeSize;
		if(m_pData)
		{
			m_pData = realloc(m_pData, n);
		}
		else
		{
			m_pData = malloc(n);
		}
		if(m_pData)
		{
			memcpy(m_pData, pData, n);
			m_nSize = nSize;
			m_Type = type;
			m_nTypeSize = typeSize;
			m_nComponent = nComponent;
		}
	}
}

/*****************************
		PRIVATE FUNCTIONS
******************************/
int LJVertexBufferData::get_type_size(LJVertexBuffer::VERTEXBUFFERDATATYPE type)
{
	switch(type)
	{
	case LJVertexBuffer::Float:
		return sizeof(float);
	case LJVertexBuffer::Int:
		return sizeof(int);
	case LJVertexBuffer::Short:
		return sizeof(short);
	case LJVertexBuffer::Byte:
		return sizeof(char);
	case LJVertexBuffer::UnsignedInt:
		return sizeof(unsigned int);
	case LJVertexBuffer::UnsignedShort:
		return sizeof(unsigned short);
	case LJVertexBuffer::UnsignedByte:
		return sizeof(unsigned char);
	default:
		return 0;
	}
}

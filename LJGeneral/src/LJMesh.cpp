#include "LJMesh.h"
#include <cstdio>

LJMesh::LJMesh()
	:m_pIndexBuffer(NULL),
	 m_Mode(LJ_TRIANGLES)
{
	m_pVertexBuffers = new VERTEXBUFFERS();
	m_pVBMap = new VERTEXBUFFERMAP();
}

LJMesh::~LJMesh(void)
{
	printf("~LJMesh\n");
	if(m_pVertexBuffers)
	{
		VERTEXBUFFERS::iterator it = m_pVertexBuffers->begin();
		while(it != m_pVertexBuffers->end())
		{
			delete *it;
			++it;
		}
	}
	if(m_pIndexBuffer)
	{
		delete m_pIndexBuffer;
	}
	if(m_pVBMap)
	{
		delete m_pVBMap;
	}
}

void LJMesh::SetBuffer(void *pData, 
					   int nComponent, 
					   int nSize, 
					   LJVertexBuffer::DATATYPE dataType, 
					   const char* chName, 
					   LJVertexBuffer::TARGET target, 
					   LJVertexBuffer::USAGE usage)
{
	string name(chName);
	VERTEXBUFFERMAP::iterator it = m_pVBMap->find(name);
	// not found
	if(it == m_pVBMap->end())
	{
		LJVertexBuffer *newVBuf = new LJVertexBuffer();
		newVBuf->SetData(pData, nComponent, nSize, dataType,
				LJVertexBuffer::ATTRIBUTE, chName, target, usage);
		m_pVertexBuffers->push_back(newVBuf);
		(*m_pVBMap)[name] = newVBuf;
	}
	else
	{
		it->second->SetData(pData, nComponent, nSize, dataType,
				LJVertexBuffer::ATTRIBUTE, chName, target, usage);
	}
}

void LJMesh::SetIndexBuffer(void *pData,
		int nSize,
		LJVertexBuffer::DATATYPE dataType,
		LJVertexBuffer::TARGET target,
		LJVertexBuffer::USAGE usage)
{
	LJVertexBuffer *tmp = new LJVertexBuffer();
	tmp->SetData(pData, 1, nSize, dataType, LJVertexBuffer::INDEX,
			NULL, target, usage);
	if(m_pIndexBuffer)
	{
		delete m_pIndexBuffer;
	}
	m_pIndexBuffer = tmp;
}

void LJMesh::SetMode(MODE mode)
{
	m_Mode = mode;
}

LJMesh::VERTEXBUFFERS* LJMesh::GetBuffers()
{
	return m_pVertexBuffers;
}

const LJMesh::VERTEXBUFFERS* LJMesh::GetBuffers() const
{
	return m_pVertexBuffers;
}

LJVertexBuffer* LJMesh::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

const LJVertexBuffer* LJMesh::GetIndexBuffer() const
{
	return m_pIndexBuffer;
}

LJMesh::MODE LJMesh::GetMode() const
{
	return m_Mode;
}

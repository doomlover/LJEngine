#ifndef LJVERTEXBUFFERDATA_H
#define LJVERTEXBUFFERDATA_H
#include "LJVertexBuffer.h"
#include <vector>
using std::vector;
/*
 * implemented by std::vector
*/
class LJVertexBufferData
{
public:
	LJVertexBufferData();
	~LJVertexBufferData(void);
	const void* GetData() const;
	int GetSize() const;
	LJVertexBuffer::VERTEXBUFFERDATATYPE GetType() const;
	int GetTypeSize() const;
	int GetComponent() const;
	void SetData(const void* pData, int nComponnet, int nSize,
		LJVertexBuffer::VERTEXBUFFERDATATYPE type);

private:
	void* m_pData;
	int m_nSize;
	LJVertexBuffer::VERTEXBUFFERDATATYPE m_Type;
	int m_nTypeSize;
	int m_nComponent;

	int get_type_size(LJVertexBuffer::VERTEXBUFFERDATATYPE type);
};//~LJVertexBufferData

#endif
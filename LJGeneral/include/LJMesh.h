#ifndef LJMESHA_H
#define LJMESHA_H

#include "LJGeneralHeaders.h"
#include "LJVertexBuffer.h"
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <string>
using std::string;
/*
 * Vertex Data Container
 */
class _LJExport LJMesh
{
public:
	typedef vector<LJVertexBuffer*> VERTEXBUFFERS;
	typedef map<string, LJVertexBuffer*> VERTEXBUFFERMAP;
	typedef enum _MODE
	{
		LJ_TRIANGLES,
	} MODE;

	LJMesh();
	~LJMesh(void);
	/*
	 * pData : pointer to data
	 * nComponent : number of elements of the dataType consisting a vertex
	 * nSize : total number of elements
	 * dataType : the data type the elements use
	 * chName : the attribute name in shader
	 * target : target buffer
	 * usage : buffer usage
	 */
	void SetBuffer(void *pData, 
					   int nComponent, 
					   int nSize, 
					   LJVertexBuffer::DATATYPE dataType, 
					   const char *chName, 
					   LJVertexBuffer::TARGET target, 
					   LJVertexBuffer::USAGE usage);
	void SetIndexBuffer(void *pData,
			int nSize,
			LJVertexBuffer::DATATYPE dataType,
			LJVertexBuffer::TARGET target,
			LJVertexBuffer::USAGE usage
			);
	void SetMode(MODE mode);

	VERTEXBUFFERS* GetBuffers();
	const VERTEXBUFFERS* GetBuffers() const;
	LJVertexBuffer* GetIndexBuffer();
	MODE GetMode() const;
	const LJVertexBuffer* GetIndexBuffer() const;
	
private:
	VERTEXBUFFERS *m_pVertexBuffers;
	LJVertexBuffer *m_pIndexBuffer;
	VERTEXBUFFERMAP *m_pVBMap;
	MODE m_Mode;
};//~LJMesh

#endif

#ifndef LJVERTEXBUFFER_H
#define LJVERTEXBUFFER_H

#include "LJGeneralHeaders.h"
#include <string>
using std::string;

class LJVertexBufferData;

/*
* WARNING : the data held by LJVertexBuffer could be redundant
*/
class _LJExport LJVertexBuffer
{
public:
	typedef enum _VERTEXBUFFERDATATYPE
	{
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Int,
		UnsignedInt,
		Float
	} VERTEXBUFFERDATATYPE;
	typedef VERTEXBUFFERDATATYPE DATATYPE;

	typedef enum _USAGE
	{
			LJ_STREAM_DRAW,
			LJ_STREAM_READ,
			LJ_STREAM_COPY,
			LJ_STATIC_DRAW,
			LJ_STATIC_READ,
			LJ_STATIC_COPY,
			LJ_DYNAMIC_DRAW,
			LJ_DYNAMIC_READ,
			LJ_DYNAMIC_COPY,

			LJ_NOUSAGE
	} USAGE;
	typedef enum _TARGET
	{
		LJ_ARRAY_BUFFER,
		LJ_ELEMENT_ARRAY_BUFFER,

		LJ_NOTARGET
	} TARGET;
	typedef enum _BUFFERTYPE
	{
		ATTRIBUTE,
		INDEX,
		NOTYPE
	} BUFFERTYPE;

	LJVertexBuffer();
	~LJVertexBuffer(void);
	const void* GetData() const;
	int GetSize() const;
	DATATYPE GetType() const;
	int GetTypeSize() const;
	int GetComponent() const;
	BUFFERTYPE GetBufferType() const;
	TARGET GetTarget() const;
	USAGE GetUsage() const;
	string GetAttribName() const;
	int GetStride() const;
	bool GetNormalized() const;
	bool IsNeedUpdate() const;
	int GetID() const;
	void SetAttribName(const char* chName);
	void SetID(int id);
	void SetData(const void *pData, int nComponent, int nSize,
		DATATYPE dataType, BUFFERTYPE bufType, const char* chName,
		TARGET target, USAGE usage);
private:
	LJVertexBufferData *m_pData;
	BUFFERTYPE m_BufType;
	TARGET m_Target;
	USAGE m_Usage;
	bool m_bNeedUpdate;
	// storing the handle of a buffer object of graphic device 
	int m_id;		
	string *m_pAttribName;
	int m_nStride;
	bool m_bNormalized;
};// ~LJVertexBuffer

#endif
